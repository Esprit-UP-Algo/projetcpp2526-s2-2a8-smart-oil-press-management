#include "statistique_partenaire.h"
#include <algorithm>

StatistiquePartenaire::StatistiquePartenaire()
    : nbPartenaires(0), totalInvestissement(0.0)
{
}

bool StatistiquePartenaire::chargerStats()
{
    donneesPartenaires.clear();

    QSqlQuery q1;
    q1.prepare(
        "SELECT COUNT(*) AS NB_PARTENAIRES, "
        "       NVL(SUM(TO_NUMBER(INVESTISSEMENT)), 0) AS TOTAL_INVEST "
        "FROM PARTENAIRE"
        );
    if (!q1.exec()) {
        qDebug() << "[StatistiquePartenaire] Erreur SQL totaux :" << q1.lastError().text();
        return false;
    }
    if (q1.next()) {
        nbPartenaires       = q1.value("NB_PARTENAIRES").toInt();
        totalInvestissement = q1.value("TOTAL_INVEST").toDouble();
    }

    QSqlQuery q2;
    q2.prepare(
        "SELECT NOM, NVL(TO_NUMBER(INVESTISSEMENT), 0) AS INVEST "
        "FROM PARTENAIRE "
        "ORDER BY INVEST DESC"
        );
    if (!q2.exec()) {
        qDebug() << "[StatistiquePartenaire] Erreur SQL détail :" << q2.lastError().text();
        return false;
    }
    while (q2.next()) {
        donneesPartenaires.append({
            q2.value("NOM").toString(),
            q2.value("INVEST").toDouble()
        });
    }
    return true;
}

void StatistiquePartenaire::afficherGraphique(QChartView *chartView)
{
    if (!chartView || totalInvestissement <= 0 || donneesPartenaires.isEmpty())
        return;

    // ── Préparer les données : Top 3 + "Autres" ───────────────
    QStringList categories;
    QList<double> pourcentages;

    double sommeAutres = 0.0;
    int top = qMin(3, donneesPartenaires.size());

    for (int i = 0; i < top; ++i) {
        const auto &p = donneesPartenaires[i];
        categories << p.first;
        pourcentages << (p.second / totalInvestissement * 100.0);
    }
    for (int i = top; i < donneesPartenaires.size(); ++i)
        sommeAutres += donneesPartenaires[i].second;
    if (donneesPartenaires.size() > 3) {
        categories << "Autres";
        pourcentages << (sommeAutres / totalInvestissement * 100.0);
    }

    // ── Couleurs ───────────────────────────────────────────────
    QList<QColor> couleurs = {
        QColor("#2d6a4f"),
        QColor("#52b788"),
        QColor("#95d5b2"),
        QColor("#b7b7b7"),
    };

    // ── Axe X commun avec TOUTES les catégories ────────────────
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsFont(QFont("Arial", 9, QFont::Bold));

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("% du total");
    axisY->setLabelFormat("%.0f%%");
    axisY->setTickCount(6);

    QChart *chart = new QChart();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ── Une série par barre : valeur réelle sur sa position, 0 ailleurs ──
    for (int i = 0; i < categories.size(); ++i) {
        QBarSet *barSet = new QBarSet(
            QString("%1 %2%").arg(categories[i]).arg(pourcentages[i], 0, 'f', 1)
            );
        barSet->setColor(couleurs[qMin(i, couleurs.size() - 1)]);
        barSet->setLabelColor(Qt::white);

        for (int j = 0; j < categories.size(); ++j) {
            double val = (j == i ? pourcentages[i] : 0.0);
            *barSet << qRound(val * 10.0) / 10.0;
        }

        QBarSeries *series = new QBarSeries();
        series->append(barSet);
        series->setLabelsVisible(true);
        series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);


        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    chart->setTitle("Répartition des investissements (%)");
    chart->setTitleFont(QFont("Arial", 11, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(Qt::white);

    if (chartView->chart())
        delete chartView->chart();

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void StatistiquePartenaire::calculerEtAfficher(QLabel *labelNbPartenaires,
                                               QLabel *labelTotalInvestissement,
                                               QChartView *chartView)
{
    if (!chargerStats()) {
        if (labelNbPartenaires)       labelNbPartenaires->setText("Erreur");
        if (labelTotalInvestissement) labelTotalInvestissement->setText("Erreur");
        return;
    }

    if (labelNbPartenaires)
        labelNbPartenaires->setText(QString::number(nbPartenaires));

    if (labelTotalInvestissement)
        labelTotalInvestissement->setText(
            QString::number(totalInvestissement, 'f', 2));

    afficherGraphique(chartView);
}
