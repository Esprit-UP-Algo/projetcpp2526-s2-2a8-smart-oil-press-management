#ifndef STATPRODUCTION_H
#define STATPRODUCTION_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QtCharts/QChartView>

QT_USE_NAMESPACE

    class StatProduction
{
public:
    StatProduction();

    // Statistics computed from DB
    int    getTotalProductions()  const { return totalProductions; }
    double getTotalOlives()       const { return totalOlives; }
    double getTotalHuile()        const { return totalHuile; }
    double getRendementMoyen()    const { return rendementMoyen; }
    double getRendementMax()      const { return rendementMax; }
    double getRendementMin()      const { return rendementMin; }

    // Load stats from DB and update the stat card labels
    void calculerEtAfficher(QLabel *labelTotal,
                            QLabel *labelOlives,
                            QLabel *labelHuile,
                            QLabel *labelRendement);

    // Create bar chart: quantity of olives per region (Nord / Centre / Sahel)
    QChartView* creerGraphiqueRegions();

private:
    int    totalProductions;
    double totalOlives;
    double totalHuile;
    double rendementMoyen;
    double rendementMax;
    double rendementMin;

    bool chargerStats();
};

#endif // STATPRODUCTION_H
