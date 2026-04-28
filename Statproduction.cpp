#include "Statproduction.h"

#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QFont>
#include <algorithm>

QT_USE_NAMESPACE

StatProduction::StatProduction()
    : totalProductions(0),
    totalOlives(0.0),
    totalHuile(0.0),
    rendementMoyen(0.0),
    rendementMax(0.0),
    rendementMin(0.0)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// chargerStats — fetch aggregated statistics from the DB
// ─────────────────────────────────────────────────────────────────────────────
bool StatProduction::chargerStats()
{
    QSqlQuery query;

    query.prepare(
        "SELECT "
        "    COUNT(*)                    AS TOTAL_PROD, "
        "    NVL(SUM(QUANTITE_OLIVE), 0) AS TOTAL_OLIVES, "
        "    NVL(SUM(QUANTITE_HUILE), 0) AS TOTAL_HUILE, "
        "    NVL(AVG(RENDEMENT),      0) AS REND_MOY, "
        "    NVL(MAX(RENDEMENT),      0) AS REND_MAX, "
        "    NVL(MIN(RENDEMENT),      0) AS REND_MIN "
        "FROM ZIT.PRODUCTION"
        );

    if (!query.exec()) {
        qDebug() << "Erreur chargement statistiques :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        totalProductions = query.value("TOTAL_PROD").toInt();
        totalOlives      = query.value("TOTAL_OLIVES").toDouble();
        totalHuile       = query.value("TOTAL_HUILE").toDouble();
        rendementMoyen   = query.value("REND_MOY").toDouble();
        rendementMax     = query.value("REND_MAX").toDouble();
        rendementMin     = query.value("REND_MIN").toDouble();
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// calculerEtAfficher — load stats from DB and push them into the UI labels
// ─────────────────────────────────────────────────────────────────────────────
void StatProduction::calculerEtAfficher(QLabel *labelTotal,
                                        QLabel *labelOlives,
                                        QLabel *labelHuile,
                                        QLabel *labelRendement)
{
    if (!chargerStats()) {
        if (labelTotal)     labelTotal->setText("Erreur");
        if (labelOlives)    labelOlives->setText("Erreur");
        if (labelHuile)     labelHuile->setText("Erreur");
        if (labelRendement) labelRendement->setText("Erreur");
        return;
    }

    if (labelTotal)
        labelTotal->setText(QString::number(totalProductions));

    if (labelOlives)
        labelOlives->setText(QString::number(totalOlives, 'f', 2));

    if (labelHuile)
        labelHuile->setText(QString::number(totalHuile, 'f', 2));

    if (labelRendement) {
        labelRendement->setText(QString::number(rendementMoyen, 'f', 2) + "%");
        labelRendement->setToolTip(
            QString("Max : %1 %\nMin : %2 %")
                .arg(QString::number(rendementMax, 'f', 2))
                .arg(QString::number(rendementMin, 'f', 2))
            );
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// creerGraphiqueRegions — bar chart: total olives (kg) per region
// ─────────────────────────────────────────────────────────────────────────────
QChartView* StatProduction::creerGraphiqueRegions()
{
    // ── Fetch sums per region ──────────────────────────────────────────────
    double nordTotal   = 0.0;
    double centreTotal = 0.0;
    double sahelTotal  = 0.0;
    double autreTotal  = 0.0;

    QSqlQuery q;
    q.prepare(
        "SELECT NVL(REG, 'autre') AS REGION, "
        "       NVL(SUM(QUANTITE_OLIVE), 0) AS TOTAL_OLIVES "
        "FROM ZIT.PRODUCTION "
        "GROUP BY REG"
        );

    if (q.exec()) {
        while (q.next()) {
            QString region = q.value("REGION").toString().trimmed().toLower();
            double  total  = q.value("TOTAL_OLIVES").toDouble();

            if (region == "nord")
                nordTotal += total;
            else if (region == "centre")
                centreTotal += total;
            else if (region == "sahel")
                sahelTotal += total;
            else
                autreTotal += total;
        }
    } else {
        qDebug() << "Erreur graphique régions :" << q.lastError().text();
    }

    // ── Build bar set ──────────────────────────────────────────────────────
    QBarSet *barSet = new QBarSet("Olives (kg)");
    barSet->setColor(QColor("#5d732c"));
    barSet->setBorderColor(QColor("#2d4a1f"));
    *barSet << nordTotal << centreTotal << sahelTotal;

    // Include "Non défini" only if there is actually data
    QStringList categories;
    categories << "Nord" << "Centre" << "Sahel";
    if (autreTotal > 0.0) {
        *barSet << autreTotal;
        categories << "Non défini";
    }

    QBarSeries *series = new QBarSeries();
    series->append(barSet);
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value kg");
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

    // ── Axes ───────────────────────────────────────────────────────────────
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Région");

    // compute a nice max for Y axis — fix: replace qMax({...}) with std::max
    double maxVal = std::max({nordTotal, centreTotal, sahelTotal, autreTotal});
    double yMax   = (maxVal > 0) ? maxVal * 1.25 : 100.0;

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, yMax);
    axisY->setTitleText("Quantité d'olives (kg)");
    axisY->setLabelFormat("%.0f");

    // ── Chart ──────────────────────────────────────────────────────────────
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("🫒 Quantité d'olives par région");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(false);

    // Attach axes
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Style
    chart->setBackgroundBrush(QBrush(QColor("#ffffff")));
    chart->setBackgroundRoundness(8);

    QFont titleFont;
    titleFont.setPointSize(13);
    titleFont.setBold(true);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor("#2d4a1f")));

    // ── ChartView ──────────────────────────────────────────────────────────
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumHeight(280);

    return view;
}
