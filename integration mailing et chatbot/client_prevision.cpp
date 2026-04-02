#include "client_prevision.h"
#include "client_achat.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QFont>
#include <QtMath>
#include <algorithm>

ClientPrevision::ClientPrevision(QObject *parent) : QObject(parent)
{
    m_achatService = new ClientAchat(this);
    qDebug() << "Service Prévisions (v2 - Algorithme avancé) initialisé";
}

ClientPrevision::~ClientPrevision()
{
    qDebug() << "Service Prévisions détruit";
}

// ============================================================
//  UTILITAIRES
// ============================================================

QColor ClientPrevision::getCouleurVert(int index, int total)
{
    // Dégradé du vert foncé (#1b5e20) au vert clair (#a5d6a7)
    int r1 = 27,  g1 = 94,  b1 = 32;   // foncé
    int r2 = 165, g2 = 214, b2 = 167;  // clair
    double t = (total <= 1) ? 0.0 : (double)index / (total - 1);
    return QColor(
        r1 + (int)((r2 - r1) * t),
        g1 + (int)((g2 - g1) * t),
        b1 + (int)((b2 - b1) * t)
        );
}

QString ClientPrevision::niveauConfianceTexte(double confiance)
{
    if (confiance >= 0.75) return "Élevé ✅";
    if (confiance >= 0.40) return "Moyen ⚠️";
    return "Faible ❌";
}

// ============================================================
//  RÉCUPÉRATION DES DONNÉES HISTORIQUES
// ============================================================

QVector<double> ClientPrevision::getHistoriqueQuantites(int idClient, const QString &produit)
{
    QVector<double> quantites;
    QSqlQuery query;

    if (produit.isEmpty()) {
        query.prepare("SELECT quantite FROM achats "
                      "WHERE id_client = :id ORDER BY date_achat ASC");
        query.bindValue(":id", idClient);
    } else {
        query.prepare("SELECT quantite FROM achats "
                      "WHERE id_client = :id AND produit = :produit ORDER BY date_achat ASC");
        query.bindValue(":id", idClient);
        query.bindValue(":produit", produit);
    }

    if (query.exec())
        while (query.next())
            quantites.append(query.value(0).toDouble());

    return quantites;
}

QVector<DonneeHistorique> ClientPrevision::getHistoriqueDetaille(int idClient, const QString &produit)
{
    QVector<DonneeHistorique> donnees;
    QSqlQuery query;

    if (produit.isEmpty()) {
        query.prepare("SELECT date_achat, quantite FROM achats "
                      "WHERE id_client = :id ORDER BY date_achat ASC");
        query.bindValue(":id", idClient);
    } else {
        query.prepare("SELECT date_achat, quantite FROM achats "
                      "WHERE id_client = :id AND produit = :produit ORDER BY date_achat ASC");
        query.bindValue(":id", idClient);
        query.bindValue(":produit", produit);
    }

    if (query.exec()) {
        while (query.next()) {
            DonneeHistorique d;
            d.date     = query.value(0).toDate();
            d.quantite = query.value(1).toDouble();
            d.mois     = d.date.month();
            d.annee    = d.date.year();
            donnees.append(d);
        }
    }
    return donnees;
}

// ============================================================
//  ALGORITHMES DE PRÉVISION
// ============================================================

/**
 * Régression linéaire (moindres carrés) – retourne la pente (tendance/période).
 */
double ClientPrevision::calculerTendanceRegression(const QVector<double> &donnees)
{
    int n = donnees.size();
    if (n < 2) return 0.0;

    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (int i = 0; i < n; i++) {
        sumX  += i;
        sumY  += donnees[i];
        sumXY += i * donnees[i];
        sumX2 += i * i;
    }
    double denom = n * sumX2 - sumX * sumX;
    return (denom == 0) ? 0.0 : (n * sumXY - sumX * sumY) / denom;
}

/**
 * Moyenne mobile pondérée (poids croissants = données récentes plus influentes).
 */
double ClientPrevision::calculerMoyenneMobilePondef(const QVector<double> &donnees, int periode)
{
    if (donnees.isEmpty()) return 0.0;

    int taille = donnees.size();
    int debut  = qMax(0, taille - periode);
    double somme = 0, poidsTot = 0;

    for (int i = debut; i < taille; i++) {
        double poids = (i - debut + 1);   // poids = rang (1, 2, 3 …)
        somme    += donnees[i] * poids;
        poidsTot += poids;
    }
    return (poidsTot > 0) ? somme / poidsTot : 0.0;
}

/**
 * Facteur saisonnier : ratio moyen du mois cible par rapport à la moyenne annuelle.
 * Si pas assez de données, renvoie 1.0 (neutre).
 */
double ClientPrevision::calculerFacteurSaisonnier(int idClient, const QString &produit, int moisCible)
{
    QVector<DonneeHistorique> hist = getHistoriqueDetaille(idClient, produit);
    if (hist.size() < 6) return 1.0;   // Pas assez de données

    // Moyenne globale
    double total = 0;
    for (const auto &d : hist) total += d.quantite;
    double moyGlobale = total / hist.size();
    if (moyGlobale == 0) return 1.0;

    // Moyenne du mois cible
    double sommeMois = 0;
    int countMois = 0;
    for (const auto &d : hist) {
        if (d.mois == moisCible) {
            sommeMois += d.quantite;
            countMois++;
        }
    }
    if (countMois == 0) return 1.0;

    double moyMois = sommeMois / countMois;
    double facteur = moyMois / moyGlobale;

    // Limiter le facteur entre 0.5 et 2.0 pour éviter les extrêmes
    return qBound(0.5, facteur, 2.0);
}

/**
 * Niveau de confiance :
 *  - basé sur le nombre de points (12+ = max)
 *  - pénalisé si la variance est très forte
 */
double ClientPrevision::calculerConfiance(const QVector<double> &donnees)
{
    int n = donnees.size();
    if (n == 0) return 0.0;

    // Confiance quantité de données (sature à 12 points)
    double confianceN = qMin(1.0, (double)n / 12.0);

    if (n < 2) return confianceN * 0.5;

    // Coefficient de variation (σ / μ)
    double sum = 0;
    for (double v : donnees) sum += v;
    double moy = sum / n;
    if (moy == 0) return confianceN * 0.3;

    double variance = 0;
    for (double v : donnees) variance += (v - moy) * (v - moy);
    variance /= n;
    double cv = qSqrt(variance) / moy;   // 0 = très régulier, >1 = très variable

    // Pénalité de variabilité (CV > 1 → confiance réduite)
    double penaVariabilite = qBound(0.0, 1.0 - cv * 0.4, 1.0);

    return qBound(0.0, confianceN * 0.6 + penaVariabilite * 0.4, 1.0);
}

// ============================================================
//  PRÉVISION PRINCIPALE (combinaison des trois méthodes)
// ============================================================

double ClientPrevision::predireDemandeClient(int idClient, const QString &produit)
{
    QVector<double> historique = getHistoriqueQuantites(idClient, produit);
    if (historique.isEmpty()) return 0.0;

    // 1) Moyenne mobile pondérée (horizon court)
    double mmp = calculerMoyenneMobilePondef(historique, 4);

    // 2) Régression linéaire (tendance)
    double tendance    = calculerTendanceRegression(historique);
    double derniereVal = historique.last();
    double predRegression = qMax(0.0, derniereVal + tendance);

    // 3) Facteur saisonnier (mois prochain)
    int moisProchain = QDate::currentDate().addMonths(1).month();
    double fs = calculerFacteurSaisonnier(idClient, produit, moisProchain);

    // Fusion pondérée selon la quantité de données
    int n = historique.size();
    double wMMP, wReg;
    if (n < 4) {
        wMMP = 0.80; wReg = 0.20;   // peu de données → privilégier la moyenne
    } else if (n < 8) {
        wMMP = 0.55; wReg = 0.45;
    } else {
        wMMP = 0.40; wReg = 0.60;   // beaucoup de données → régression plus fiable
    }

    double prediction = (mmp * wMMP + predRegression * wReg) * fs;
    return qMax(0.0, prediction);
}

// ============================================================
//  AFFICHAGE TABLEAU DES PRÉVISIONS
// ============================================================

QVector<PrevisionData> ClientPrevision::getPrevisionsTousClients()
{
    QVector<PrevisionData> previsions;

    QSqlQuery query;
    query.exec("SELECT DISTINCT id_client, produit FROM achats");

    while (query.next()) {
        int     idClient = query.value(0).toInt();
        QString produit  = query.value(1).toString();

        // Nom du client
        QSqlQuery cq;
        cq.prepare("SELECT NOM, PRENOM FROM ZIT.CLIENT WHERE ID_CLIENT = :id");
        cq.bindValue(":id", idClient);
        QString nomClient;
        if (cq.exec() && cq.next())
            nomClient = cq.value(0).toString() + " " + cq.value(1).toString();

        QVector<double> hist = getHistoriqueQuantites(idClient, produit);
        double prediction = predireDemandeClient(idClient, produit);
        double confiance  = calculerConfiance(hist);
        double tendance   = calculerTendanceRegression(hist);

        int moisProchain = QDate::currentDate().addMonths(1).month();
        double fs = calculerFacteurSaisonnier(idClient, produit, moisProchain);

        PrevisionData pv;
        pv.idClient       = idClient;
        pv.nomClient      = nomClient;
        pv.produit        = produit;
        pv.quantitePredite = prediction;
        pv.confiance      = confiance;
        pv.niveauConfiance = niveauConfianceTexte(confiance);
        pv.tendance       = tendance;
        pv.saisonnalite   = fs;

        previsions.append(pv);
    }
    return previsions;
}

void ClientPrevision::afficherPrevisions(QTableWidget *table)
{
    table->setRowCount(0);
    table->setColumnCount(7);
    QStringList headers = {
        "ID Client", "Client", "Produit",
        "Prévision (kg)", "Tendance", "Saisonnalité", "Confiance"
    };
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(
        "QTableWidget { alternate-background-color: #f1f8e9; background: white; }"
        "QHeaderView::section { background-color: #388e3c; color: white; font-weight: bold; padding: 6px; }"
        );

    QVector<PrevisionData> previsions = getPrevisionsTousClients();

    int row = 0;
    for (const PrevisionData &pv : previsions) {
        if (pv.quantitePredite <= 0) continue;

        table->insertRow(row);

        auto makeItem = [&](const QString &txt, Qt::Alignment align = Qt::AlignCenter) {
            QTableWidgetItem *item = new QTableWidgetItem(txt);
            item->setTextAlignment(align);
            return item;
        };

        table->setItem(row, 0, makeItem(QString::number(pv.idClient)));
        table->setItem(row, 1, makeItem(pv.nomClient));
        table->setItem(row, 2, makeItem(pv.produit));
        table->setItem(row, 3, makeItem(QString::number(pv.quantitePredite, 'f', 2)));

        // Tendance avec flèche
        QString tendanceTxt = (pv.tendance > 0.5) ? "↑ " :
                                  (pv.tendance < -0.5) ? "↓ " : "→ ";
        tendanceTxt += QString::number(pv.tendance, 'f', 2);
        auto *tItem = makeItem(tendanceTxt);
        tItem->setForeground(pv.tendance > 0 ? QColor("#1b5e20") : QColor("#b71c1c"));
        table->setItem(row, 4, tItem);

        // Saisonnalité
        QString saisonTxt = (pv.saisonnalite > 1.1) ? "⬆ " :
                                (pv.saisonnalite < 0.9) ? "⬇ " : "— ";
        saisonTxt += QString::number(pv.saisonnalite, 'f', 2);
        table->setItem(row, 5, makeItem(saisonTxt));

        // Confiance avec couleur
        auto *cItem = makeItem(pv.niveauConfiance + QString(" (%1%)").arg((int)(pv.confiance * 100)));
        if (pv.confiance >= 0.75)       cItem->setForeground(QColor("#1b5e20"));
        else if (pv.confiance >= 0.40)  cItem->setForeground(QColor("#f57f17"));
        else                            cItem->setForeground(QColor("#b71c1c"));
        table->setItem(row, 6, cItem);

        row++;
    }
}

// ============================================================
//  GRAPHIQUE : ÉVOLUTION SUR 12 MOIS (historique + prévision)
// ============================================================

QChartView* ClientPrevision::creerGraphiqueEvolution12Mois(int idClient, const QString &produit)
{
    // --- Série historique ---
    QLineSeries *serieHist = new QLineSeries();
    serieHist->setName("Historique");
    QPen penHist(QColor("#2e7d32"));
    penHist.setWidth(3);
    serieHist->setPen(penHist);
    serieHist->setPointsVisible(true);

    QVector<DonneeHistorique> hist = getHistoriqueDetaille(idClient, produit);

    // Regrouper par mois (les 12 derniers mois)
    QDate aujourd = QDate::currentDate();
    QMap<QString, double> parMois;
    for (int i = 11; i >= 0; i--) {
        QDate d = aujourd.addMonths(-i);
        parMois[d.toString("MM/yyyy")] = 0.0;
    }
    for (const DonneeHistorique &d : hist) {
        QString cle = d.date.toString("MM/yyyy");
        if (parMois.contains(cle))
            parMois[cle] += d.quantite;
    }

    QStringList categories;
    int idx = 0;
    for (auto it = parMois.begin(); it != parMois.end(); ++it, ++idx) {
        serieHist->append(idx, it.value());
        categories << it.key();
    }

    // --- Série prévision (3 prochains mois) ---
    QLineSeries *seriePrev = new QLineSeries();
    seriePrev->setName("Prévision");
    QPen penPrev(QColor("#ff6f00"));
    penPrev.setWidth(2);
    penPrev.setStyle(Qt::DashLine);
    seriePrev->setPen(penPrev);
    seriePrev->setPointsVisible(true);

    // Dernier point historique = point de départ de la prévision
    double dernierY = (serieHist->count() > 0)
                          ? serieHist->at(serieHist->count() - 1).y()
                          : 0.0;
    seriePrev->append(idx - 1, dernierY);

    for (int m = 1; m <= 3; m++) {
        QDate futur = aujourd.addMonths(m);
        double pred = predireDemandeClient(idClient, produit);
        double fs   = calculerFacteurSaisonnier(idClient, produit, futur.month());
        seriePrev->append(idx - 1 + m, pred * fs);
        categories << futur.toString("MM/yyyy");
    }

    // --- Construction du graphique ---
    QChart *chart = new QChart();
    chart->addSeries(serieHist);
    chart->addSeries(seriePrev);
    chart->setTitle("Évolution & Prévision – " + (produit.isEmpty() ? "Tous produits" : produit));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setTitleFont(QFont("Arial", 13, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor("#1b5e20")));

    QCategoryAxis *axisX = new QCategoryAxis();
    for (int i = 0; i < categories.size(); i++)
        axisX->append(categories[i], i);
    axisX->setTitleText("Mois");
    axisX->setLabelsAngle(-35);
    chart->addAxis(axisX, Qt::AlignBottom);
    serieHist->attachAxis(axisX);
    seriePrev->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité (kg)");
    axisY->setLabelFormat("%.1f");
    chart->addAxis(axisY, Qt::AlignLeft);
    serieHist->attachAxis(axisY);
    seriePrev->attachAxis(axisY);

    // Légende
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(700, 420);
    return view;
}

// ============================================================
//  GRAPHIQUE : PRÉVISIONS GLOBALES (barres par client)
// ============================================================

QChartView* ClientPrevision::creerGraphiquePrevisionsGlobal()
{
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Prévision (kg)");

    QVector<PrevisionData> previsions = getPrevisionsTousClients();
    QStringList categories;
    int i = 0;

    for (const PrevisionData &pv : previsions) {
        if (pv.quantitePredite <= 0) continue;
        set->append(pv.quantitePredite);
        set->setColor(getCouleurVert(i, previsions.size()));
        categories << pv.nomClient;
        i++;
    }

    if (categories.isEmpty()) {
        set->append(0);
        categories << "Aucune donnée";
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Prévisions de demande – Tous clients");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setTitleFont(QFont("Arial", 13, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor("#1b5e20")));

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Clients");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité prévue (kg)");
    axisY->setLabelFormat("%.1f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(false);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(650, 400);
    return view;
}

// ============================================================
//  GRAPHIQUE : PRÉVISION D'UN CLIENT (courbe historique + proj.)
// ============================================================

QChartView* ClientPrevision::creerGraphiquePrevisionClient(int idClient, const QString &produit)
{
    return creerGraphiqueEvolution12Mois(idClient, produit);
}

// ============================================================
//  EXPORT PDF HISTORIQUE D'ACHAT
// ============================================================

void ClientPrevision::exporterHistoriquePDF(int idClient, const QString &cheminFichier)
{
    // Récupérer nom du client
    QSqlQuery cq;
    cq.prepare("SELECT NOM, PRENOM, TYPE_CLIENT, EMAIL, TELEPHONE FROM ZIT.CLIENT WHERE ID_CLIENT = :id");
    cq.bindValue(":id", idClient);
    QString nom = "Client", prenom = "", typeC = "", email = "", tel = "";
    if (cq.exec() && cq.next()) {
        nom    = cq.value(0).toString();
        prenom = cq.value(1).toString();
        typeC  = cq.value(2).toString();
        email  = cq.value(3).toString();
        tel    = cq.value(4).toString();
    }

    // Récupérer les achats
    QSqlQuery qa;
    qa.prepare("SELECT date_achat, produit, quantite, prix_unitaire "
               "FROM achats WHERE id_client = :id ORDER BY date_achat DESC");
    qa.bindValue(":id", idClient);

    // Construire le PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(cheminFichier);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Portrait);

    QPainter p;
    if (!p.begin(&printer)) {
        QMessageBox::critical(nullptr, "Erreur PDF", "Impossible de créer le fichier PDF.");
        return;
    }

    const int W  = printer.width();
    const int lM = 80, rM = 80;   // marges gauche/droite
    int y = 60;

    auto drawLine = [&]() {
        p.setPen(QPen(QColor("#388e3c"), 3));
        p.drawLine(lM, y, W - rM, y);
        y += 18;
    };

    // ---- EN-TÊTE ----
    p.fillRect(0, 0, W, 110, QColor("#1b5e20"));
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 22, QFont::Bold));
    p.drawText(lM, 55, "ZitTech – Historique d'achat");
    p.setFont(QFont("Arial", 11));
    p.drawText(lM, 82, "Généré le : " + QDate::currentDate().toString("dd/MM/yyyy"));
    y = 130;

    // ---- INFOS CLIENT ----
    p.setPen(QColor("#1b5e20"));
    p.setFont(QFont("Arial", 13, QFont::Bold));
    p.drawText(lM, y, "Informations Client");
    y += 8;
    drawLine();

    p.setFont(QFont("Arial", 11));
    p.setPen(Qt::black);
    auto infoRow = [&](const QString &label, const QString &val) {
        p.setFont(QFont("Arial", 11, QFont::Bold));
        p.drawText(lM, y, label);
        p.setFont(QFont("Arial", 11));
        p.drawText(lM + 220, y, val);
        y += 28;
    };
    infoRow("Nom / Prénom :", nom + " " + prenom);
    infoRow("Type client :", typeC);
    infoRow("Email :", email);
    infoRow("Téléphone :", tel);
    y += 10;

    // ---- TABLEAU DES ACHATS ----
    p.setPen(QColor("#1b5e20"));
    p.setFont(QFont("Arial", 13, QFont::Bold));
    p.drawText(lM, y, "Détail des achats");
    y += 8;
    drawLine();

    // En-têtes du tableau
    int colW[] = { 140, 200, 130, 160, 160 };
    QStringList cols = { "Date", "Produit", "Quantité (kg)", "Prix unit. (DT)", "Total (DT)" };
    p.fillRect(lM, y - 4, W - lM - rM, 28, QColor("#388e3c"));
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 10, QFont::Bold));
    int xh = lM;
    for (int c = 0; c < 5; c++) {
        p.drawText(xh + 4, y + 16, cols[c]);
        xh += colW[c];
    }
    y += 32;

    // Lignes de données
    double totalGlobal = 0;
    int rowNum = 0;
    if (qa.exec()) {
        while (qa.next()) {
            if (y > printer.height() - 120) {
                printer.newPage();
                y = 60;
            }
            QDate   date   = qa.value(0).toDate();
            QString produit2 = qa.value(1).toString();
            double  qte    = qa.value(2).toDouble();
            double  pu     = qa.value(3).toDouble();
            double  total  = qte * pu;
            totalGlobal   += total;

            if (rowNum % 2 == 0)
                p.fillRect(lM, y - 4, W - lM - rM, 24, QColor("#f1f8e9"));

            p.setPen(Qt::black);
            p.setFont(QFont("Arial", 10));
            int xd = lM;
            QStringList vals = {
                date.toString("dd/MM/yyyy"),
                produit2,
                QString::number(qte, 'f', 2),
                QString::number(pu, 'f', 2),
                QString::number(total, 'f', 2)
            };
            for (int c = 0; c < 5; c++) {
                p.drawText(xd + 4, y + 14, vals[c]);
                xd += colW[c];
            }
            y += 28;
            rowNum++;
        }
    }

    // Ligne total
    y += 6;
    p.fillRect(lM, y - 4, W - lM - rM, 30, QColor("#1b5e20"));
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 11, QFont::Bold));
    p.drawText(lM + 4, y + 16, "TOTAL GÉNÉRAL");
    p.drawText(lM + colW[0] + colW[1] + colW[2] + colW[3] + 4, y + 16,
               QString::number(totalGlobal, 'f', 2) + " DT");
    y += 46;

    // ---- PRÉVISION ----
    if (y < printer.height() - 160) {
        p.setPen(QColor("#1b5e20"));
        p.setFont(QFont("Arial", 13, QFont::Bold));
        p.drawText(lM, y, "Prévision mois prochain");
        y += 8;
        drawLine();

        double pred = predireDemandeClient(idClient, "");
        int moisP   = QDate::currentDate().addMonths(1).month();
        double fs   = calculerFacteurSaisonnier(idClient, "", moisP);

        QVector<double> hist = getHistoriqueQuantites(idClient, "");
        double conf = calculerConfiance(hist);

        p.setPen(Qt::black);
        p.setFont(QFont("Arial", 11));
        p.drawText(lM, y, QString("Quantité prévue : %1 kg").arg(pred, 0, 'f', 2));
        y += 28;
        p.drawText(lM, y, QString("Facteur saisonnier : %1").arg(fs, 0, 'f', 2));
        y += 28;
        p.drawText(lM, y, QString("Niveau de confiance : %1 (%2%)")
                              .arg(niveauConfianceTexte(conf))
                              .arg((int)(conf * 100)));
    }

    // ---- PIED DE PAGE ----
    p.fillRect(0, printer.height() - 50, W, 50, QColor("#e8f5e9"));
    p.setPen(QColor("#2e7d32"));
    p.setFont(QFont("Arial", 9));
    p.drawText(lM, printer.height() - 20,
               "ZitTech – Gestion de Production d'Huile d'Olive  |  Document confidentiel");

    p.end();
    QMessageBox::information(nullptr, "Export PDF",
                             "Historique exporté avec succès !\n" + cheminFichier);
}
