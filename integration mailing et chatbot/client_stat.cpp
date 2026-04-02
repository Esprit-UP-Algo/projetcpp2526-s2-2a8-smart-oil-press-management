#include "client_stat.h"
#include <QSqlQuery>
#include <QDebug>
#include <QPainter>
#include <QtMath>

ClientStat::ClientStat(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Statistiques (v2 - Style professionnel) initialisé";
}

ClientStat::~ClientStat()
{
    qDebug() << "Service Statistiques détruit";
}

// ============================================================
//  UTILITAIRES COULEURS
// ============================================================

/**
 * Génère une palette de verts dégradés du foncé au clair.
 * index : position dans la palette (0 = plus foncé)
 * total : nombre total de couleurs souhaité
 */
QColor ClientStat::getCouleurDegradeVert(int index, int total)
{
    // Dégradé : #1b5e20 (vert très foncé) → #a5d6a7 (vert très clair)
    struct { int r, g, b; } dark  = { 27,  94,  32  };
    struct { int r, g, b; } light = { 165, 214, 167 };

    double t = (total <= 1) ? 0.0 : (double)index / (double)(total - 1);
    return QColor(
        dark.r + (int)((light.r - dark.r) * t),
        dark.g + (int)((light.g - dark.g) * t),
        dark.b + (int)((light.b - dark.b) * t)
        );
}

// ============================================================
//  STATS LABELS
// ============================================================

void ClientStat::updateStats(QLabel *totalLabel,
                             QLabel *particuliersLabel,
                             QLabel *entreprisesLabel)
{
    QSqlQuery query;

    if (query.exec("SELECT COUNT(*) FROM ZIT.CLIENT"))
        if (query.next()) totalLabel->setText(query.value(0).toString());

    if (query.exec("SELECT COUNT(*) FROM ZIT.CLIENT WHERE TYPE_CLIENT = 'Particulier'"))
        if (query.next()) particuliersLabel->setText(query.value(0).toString());

    if (query.exec("SELECT COUNT(*) FROM ZIT.CLIENT WHERE TYPE_CLIENT = 'Entreprise'"))
        if (query.next()) entreprisesLabel->setText(query.value(0).toString());
}

// ============================================================
//  HELPERS PRIVÉS
// ============================================================

double ClientStat::getVolumeTotalAchats(int idClient)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(quantite) FROM achats WHERE id_client = :id");
    query.bindValue(":id", idClient);
    if (query.exec() && query.next())
        return query.value(0).toDouble();
    return 0.0;
}

QVector<double> ClientStat::getAchatsMensuels(int mois)
{
    QVector<double> achats;
    QSqlQuery query;
    // Compatible Oracle et SQLite (strftime pour SQLite)
    query.prepare(
        "SELECT SUM(quantite) FROM achats "
        "WHERE EXTRACT(MONTH FROM date_achat) = :mois "
        "GROUP BY EXTRACT(YEAR FROM date_achat)"
        );
    query.bindValue(":mois", mois);
    if (query.exec())
        while (query.next())
            achats.append(query.value(0).toDouble());
    return achats;
}

// ============================================================
//  STYLE COMMUN DES GRAPHIQUES
// ============================================================

static void applyChartStyle(QChart *chart, const QString &titre)
{
    chart->setTitle(titre);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(800);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setDropShadowEnabled(true);

    QFont titleFont("Arial", 13, QFont::Bold);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor("#1b5e20")));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));
}

static QChartView* wrapInView(QChart *chart, QSize minSize = QSize(520, 400))
{
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(minSize);
    return view;
}

// ============================================================
//  1) CAMEMBERT — Répartition par type client
// ============================================================

QChartView* ClientStat::creerGraphiqueTypeClient()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);   // Donut moderne

    QSqlQuery query;
    query.exec("SELECT TYPE_CLIENT, COUNT(*) FROM ZIT.CLIENT GROUP BY TYPE_CLIENT");

    QList<QPair<QString, int>> resultats;
    while (query.next())
        resultats.append({ query.value(0).toString(), query.value(1).toInt() });

    int total = 0;
    for (const auto &r : resultats) total += r.second;

    for (int i = 0; i < resultats.size(); i++) {
        QString label = resultats[i].first;
        int     count = resultats[i].second;
        double  pct   = (total > 0) ? (count * 100.0 / total) : 0;

        QPieSlice *slice = series->append(
            QString("%1\n%2 (%3%)").arg(label).arg(count).arg(pct, 0, 'f', 1),
            count
            );

        QColor couleur = getCouleurDegradeVert(i, qMax(resultats.size(), 2));
        slice->setBrush(couleur);
        slice->setLabelColor(QColor("#1b5e20"));
        slice->setLabelFont(QFont("Arial", 10, QFont::Bold));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);

        // Légère explosion du premier segment
        if (i == 0) slice->setExploded(true);
        slice->setExplodeDistanceFactor(0.06f);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Répartition des clients par type");
    chart->legend()->setVisible(false);   // les labels portent déjà l'info

    return wrapInView(chart, QSize(520, 420));
}

// ============================================================
//  2) BARRES — Volume d'achat par client
// ============================================================

QChartView* ClientStat::creerGraphiqueVolumeAchat()
{
    QBarSeries *series = new QBarSeries();

    QSqlQuery query;
    query.exec("SELECT ID_CLIENT, NOM, PRENOM FROM ZIT.CLIENT ORDER BY NOM");

    QList<QPair<QString, double>> clients;
    while (query.next()) {
        int    id     = query.value(0).toInt();
        double volume = getVolumeTotalAchats(id);
        if (volume > 0)
            clients.append({ query.value(1).toString() + "\n" + query.value(2).toString(), volume });
    }

    if (clients.isEmpty())
        clients.append({ "Aucun achat", 0.0 });

    QStringList categories;
    int i = 0;
    for (const auto &c : clients) {
        QBarSet *set = new QBarSet(c.first);
        *set << c.second;
        set->setColor(getCouleurDegradeVert(i, clients.size()));
        set->setBorderColor(QColor("#1b5e20"));
        set->setLabelFont(QFont("Arial", 9));
        series->append(set);
        categories << c.first;
        i++;
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value kg");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Volume d'achat total par client (kg)");
    chart->legend()->setVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Clients");
    axisX->setLabelsAngle(-20);
    axisX->setLabelsFont(QFont("Arial", 9));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité totale (kg)");
    axisY->setLabelFormat("%.0f");
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return wrapInView(chart, QSize(620, 420));
}

// ============================================================
//  3) COURBE — Évolution mensuelle des achats
// ============================================================

QChartView* ClientStat::creerGraphiqueEvolutionMensuelle()
{
    // Série principale
    QLineSeries *series = new QLineSeries();
    series->setName("Volume mensuel (kg)");
    QPen pen(QColor("#2e7d32"));
    pen.setWidth(3);
    series->setPen(pen);
    series->setPointsVisible(true);
    series->setPointLabelsVisible(false);

    // Série de remplissage (area)
    QLineSeries *lower = new QLineSeries();

    QStringList moisNoms = { "Jan", "Fév", "Mar", "Avr", "Mai", "Juin",
                            "Juil", "Aoû", "Sep", "Oct", "Nov", "Déc" };

    double maxVal = 0;
    for (int m = 1; m <= 12; m++) {
        QVector<double> achats = getAchatsMensuels(m);
        double total = 0;
        for (double v : achats) total += v;
        series->append(m, total);
        lower->append(m, 0);
        maxVal = qMax(maxVal, total);
    }

    QAreaSeries *area = new QAreaSeries(series, lower);
    QLinearGradient grad(QPointF(0, 0), QPointF(0, 1));
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);
    grad.setColorAt(0.0, QColor(46, 125, 50, 180));
    grad.setColorAt(1.0, QColor(200, 230, 201, 40));
    area->setBrush(grad);
    area->setPen(QPen(Qt::NoPen));
    area->setName("Volume mensuel (kg)");

    QChart *chart = new QChart();
    chart->addSeries(area);
    chart->addSeries(series);
    applyChartStyle(chart, "Évolution mensuelle du volume d'achat");

    QCategoryAxis *axisX = new QCategoryAxis();
    for (int i = 0; i < 12; i++)
        axisX->append(moisNoms[i], i + 1);
    axisX->setTitleText("Mois");
    axisX->setMin(1);
    axisX->setMax(12);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    area->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité (kg)");
    axisY->setLabelFormat("%.1f");
    axisY->setMin(0);
    axisY->setMax(maxVal * 1.2 + 1);
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    area->attachAxis(axisY);

    chart->legend()->setVisible(false);

    return wrapInView(chart, QSize(700, 450));
}
