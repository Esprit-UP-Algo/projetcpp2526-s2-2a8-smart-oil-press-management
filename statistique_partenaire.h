#ifndef STATISTIQUE_PARTENAIRE_H
#define STATISTIQUE_PARTENAIRE_H

#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

class StatistiquePartenaire
{
public:
    StatistiquePartenaire();

    // Charge les stats et met à jour les labels + graphique
    void calculerEtAfficher(QLabel *labelNbPartenaires,
                            QLabel *labelTotalInvestissement,
                            QChartView *chartView = nullptr);

    int    getNbPartenaires()       const { return nbPartenaires; }
    double getTotalInvestissement() const { return totalInvestissement; }

private:
    bool chargerStats();
    void afficherGraphique(QChartView *chartView);

    int    nbPartenaires;
    double totalInvestissement;

    // Données pour le graphique : nom → investissement
    QList<QPair<QString, double>> donneesPartenaires;
};

#endif // STATISTIQUE_PARTENAIRE_H
