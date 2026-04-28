#ifndef EMPLOYE_STATS_H
#define EMPLOYE_STATS_H

#include <QLabel>
#include <QColor>
#include <QtCharts>
#include "employe.h"

class EmployeStats
{
public:
    EmployeStats() {}
    ~EmployeStats() {}

    static void charger(QLabel *labelTotal,
                        QLabel *labelOuvriers,
                        QLabel *labelTechniciens);

    QChartView* creerGraphiqueRepartitionPostes();
    QChartView* creerGraphiqueSalaires();
    QChartView* creerGraphiqueAnciennete();

    static int parPoste(const QString &poste);
    static int total();
    static QColor getCouleurDegradeVert(int index, int total);
};

#endif // EMPLOYE_STATS_H
