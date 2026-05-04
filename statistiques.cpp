#include "statistiques.h"
#include <QPainter>
#include <QMap>
#include <QPair>
#include <QPen>

Statistiques::Statistiques(const QSqlDatabase &db, QObject *parent)
    : QObject(parent), db(db)
{
    qDebug() << "Service Statistiques Stock (v2 - Style professionnel) initialisé";
}

Statistiques::~Statistiques()
{
    qDebug() << "Service Statistiques Stock détruit";
}

namespace {

static void applyChartStyle(QChart *chart, const QString &titre)
{
    chart->setTitle(titre);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(800);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setDropShadowEnabled(true);

    chart->setTitleFont(QFont("Arial", 13, QFont::Bold));
    chart->setTitleBrush(QBrush(QColor("#1b5e20")));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));
}

static QChartView *wrapInView(QChart *chart, const QSize &minSize = QSize(520, 400))
{
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(minSize);
    return view;
}

} // namespace

// ============================================================
//  UTILITAIRE COULEURS
// ============================================================

QColor Statistiques::getCouleurDegradeVert(int index, int total)
{
    struct {
        int r, g, b;
    } dark = { 27, 94, 32 };

    struct {
        int r, g, b;
    } light = { 165, 214, 167 };

    const double t = (total <= 1) ? 0.0 : static_cast<double>(index) / static_cast<double>(total - 1);
    return QColor(
        dark.r + static_cast<int>((light.r - dark.r) * t),
        dark.g + static_cast<int>((light.g - dark.g) * t),
        dark.b + static_cast<int>((light.b - dark.b) * t));
}

// ============================================================
//  1) CAMEMBERT — Répartition par type de stock
// ============================================================

QChartView *Statistiques::creerGraphiqueRepartitionTypeStock()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    QSqlQuery q(db);
    q.exec("SELECT TYPE_STOCK, COUNT(*) FROM ZIT.STOCK GROUP BY TYPE_STOCK");

    QList<QPair<QString, int>> resultats;
    while (q.next()) {
        resultats.append({ q.value(0).toString(), q.value(1).toInt() });
    }

    int total = 0;
    for (const auto &r : resultats) {
        total += r.second;
    }

    for (int i = 0; i < resultats.size(); ++i) {
        const QString type = resultats[i].first;
        const int count = resultats[i].second;
        const double pct = (total > 0) ? (count * 100.0 / total) : 0.0;

        QPieSlice *slice = series->append(
            QString("%1\n%2 (%3%)").arg(type).arg(count).arg(pct, 0, 'f', 1),
            count);

        slice->setBrush(getCouleurDegradeVert(i, qMax(resultats.size(), 2)));
        slice->setLabelColor(QColor("#1b5e20"));
        slice->setLabelFont(QFont("Arial", 10, QFont::Bold));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);

        if (i == 0) {
            slice->setExploded(true);
        }
        slice->setExplodeDistanceFactor(0.06f);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Répartition des stocks par type");
    chart->legend()->setVisible(false);

    return wrapInView(chart, QSize(520, 420));
}

// ============================================================
//  2) BARRES — Quantité totale par origine
// ============================================================

QChartView *Statistiques::creerGraphiqueQuantiteParOrigine()
{
    QSqlQuery q(db);
    q.exec("SELECT ORIGINE, NVL(SUM(QUANTITE), 0) AS TOTAL_QTE "
           "FROM ZIT.STOCK "
           "GROUP BY ORIGINE "
           "ORDER BY TOTAL_QTE DESC");

    QList<QPair<QString, double>> origines;
    while (q.next()) {
        QString origine = q.value(0).toString().trimmed();
        if (origine.isEmpty()) {
            origine = "Non spécifiée";
        }
        origines.append({ origine, q.value(1).toDouble() });
    }

    if (origines.isEmpty()) {
        origines.append({ "Aucune donnée", 0.0 });
    }

    QBarSeries *series = new QBarSeries();
    QStringList categories;
    const int n = origines.size();

    for (int i = 0; i < n; ++i) {
        categories << origines[i].first;
    }

    for (int i = 0; i < n; ++i) {
        auto *set = new QBarSet(origines[i].first);
        for (int j = 0; j < n; ++j) {
            *set << (j == i ? origines[i].second : 0.0);
        }
        set->setColor(getCouleurDegradeVert(i, qMax(n, 2)));
        set->setBorderColor(QColor("#1b5e20"));
        series->append(set);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value kg");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Quantité totale par origine");
    chart->legend()->setVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Origine");
    axisX->setLabelsAngle(-20);
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
//  3) BARRES GROUPÉES — Quantité vs seuil par type
// ============================================================

QChartView *Statistiques::creerGraphiqueNiveauxVsSeuils()
{
    QSqlQuery q(db);
    q.exec("SELECT TYPE_STOCK, NVL(SUM(QUANTITE),0), NVL(SUM(SEUIL_ALERTE),0) "
           "FROM ZIT.STOCK "
           "GROUP BY TYPE_STOCK "
           "ORDER BY TYPE_STOCK");

    QStringList categories;
    auto *setQuantite = new QBarSet("Quantité");
    auto *setSeuil = new QBarSet("Seuil d'alerte");
    setQuantite->setColor(QColor("#2e7d32"));
    setSeuil->setColor(QColor("#a5d6a7"));

    bool hasData = false;
    while (q.next()) {
        hasData = true;
        categories << q.value(0).toString();
        *setQuantite << q.value(1).toDouble();
        *setSeuil << q.value(2).toDouble();
    }

    if (!hasData) {
        categories << "Aucune donnée";
        *setQuantite << 0.0;
        *setSeuil << 0.0;
    }

    QBarSeries *series = new QBarSeries();
    series->append(setQuantite);
    series->append(setSeuil);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Niveaux de stock vs seuils d'alerte");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Type de stock");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité (kg)");
    axisY->setLabelFormat("%.0f");
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return wrapInView(chart, QSize(700, 450));
}

// ── Requêtes SQL (cartes de stats) ───────────────────────────

int Statistiques::getTotalArticles()
{
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK") && q.next())
        return q.value(0).toInt();
    return 0;
}

int Statistiques::getArticlesEnAlerte()
{
    // Stocks dont la quantité est <= au seuil d'alerte
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK WHERE QUANTITE <= SEUIL_ALERTE") && q.next())
        return q.value(0).toInt();
    return 0;
}

double Statistiques::getTotalQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT NVL(SUM(QUANTITE), 0) FROM ZIT.STOCK") && q.next())
        return q.value(0).toDouble();
    return 0.0;
}

double Statistiques::getMoyenneQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT NVL(AVG(QUANTITE), 0) FROM ZIT.STOCK") && q.next())
        return q.value(0).toDouble();
    return 0.0;
}

QString Statistiques::getStockMaxQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT TYPE_STOCK, QUANTITE, ORIGINE FROM ZIT.STOCK "
               "WHERE QUANTITE = (SELECT MAX(QUANTITE) FROM ZIT.STOCK) "
               "AND ROWNUM = 1") && q.next()) {
        return QString("%1 (%2 kg) — %3")
            .arg(q.value(0).toString())
            .arg(q.value(1).toDouble(), 0, 'f', 2)
            .arg(q.value(2).toString());
    }
    return "—";
}

QString Statistiques::getStockMinQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT TYPE_STOCK, QUANTITE, ORIGINE FROM ZIT.STOCK "
               "WHERE QUANTITE = (SELECT MIN(QUANTITE) FROM ZIT.STOCK) "
               "AND ROWNUM = 1") && q.next()) {
        return QString("%1 (%2 kg) — %3")
            .arg(q.value(0).toString())
            .arg(q.value(1).toDouble(), 0, 'f', 2)
            .arg(q.value(2).toString());
    }
    return "—";
}

int Statistiques::getNbOriginesDistinctes()
{
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(DISTINCT ORIGINE) FROM ZIT.STOCK") && q.next())
        return q.value(0).toInt();
    return 0;
}

int Statistiques::getStocksCritiques()
{
    // Stocks dont la quantité est STRICTEMENT inférieure au seuil
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK WHERE QUANTITE < SEUIL_ALERTE") && q.next())
        return q.value(0).toInt();
    return 0;
}

// ── Méthode principale ────────────────────────────────────────

void Statistiques::chargerStats(QLabel *valueTotalStocks,
                                QLabel *valueAlertStocks,
                                QLabel *valueTotalQuantite,
                                QLabel *valueMoyenneQuantite,
                                QLabel *valueStockMax,
                                QLabel *valueStockMin,
                                QLabel *valueNbOrigines,
                                QLabel *valueStockCritique)
{
    int    total      = getTotalArticles();
    int    alertes    = getArticlesEnAlerte();
    double totalQte   = getTotalQuantite();
    double moyenneQte = getMoyenneQuantite();
    QString stockMax  = getStockMaxQuantite();
    QString stockMin  = getStockMinQuantite();
    int    nbOrigines = getNbOriginesDistinctes();
    int    critiques  = getStocksCritiques();

    // Mettre à jour les labels si non null
    if (valueTotalStocks)
        valueTotalStocks->setText(QString::number(total));

    if (valueAlertStocks) {
        valueAlertStocks->setText(QString::number(alertes));
        // Colorer en rouge si des alertes existent
        if (alertes > 0)
            valueAlertStocks->setStyleSheet(
                "color: #ff4444; font: 16pt 'Segoe UI'; font-weight: bold;");
        else
            valueAlertStocks->setStyleSheet(
                "color: #44cc44; font: 16pt 'Segoe UI'; font-weight: bold;");
    }

    if (valueTotalQuantite)
        valueTotalQuantite->setText(
            QString::number(totalQte, 'f', 2) + " kg");

    if (valueMoyenneQuantite)
        valueMoyenneQuantite->setText(
            QString::number(moyenneQte, 'f', 2) + " kg");

    if (valueStockMax)
        valueStockMax->setText(stockMax);

    if (valueStockMin)
        valueStockMin->setText(stockMin);

    if (valueNbOrigines)
        valueNbOrigines->setText(QString::number(nbOrigines));

    if (valueStockCritique) {
        valueStockCritique->setText(QString::number(critiques));
        if (critiques > 0)
            valueStockCritique->setStyleSheet(
                "color: #ff2222; font: 16pt 'Segoe UI'; font-weight: bold;");
        else
            valueStockCritique->setStyleSheet(
                "color: #44cc44; font: 16pt 'Segoe UI'; font-weight: bold;");
    }

    qDebug() << "Stats chargées — Total:" << total
             << "Alertes:" << alertes
             << "TotalQte:" << totalQte
             << "Critiques:" << critiques;
}
