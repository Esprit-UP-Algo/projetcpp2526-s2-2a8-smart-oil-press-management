#ifndef EMPLOYE_STATS_H
#define EMPLOYE_STATS_H

#include <QLabel>
#include "employe.h"

// ============================================================
//  EmployeStats — Module de statistiques des Employés
//  Utilisation dans mainwindow.cpp :
//      EmployeStats::charger(ui->valueTotalEmployes,
//                            ui->valueOuvriers,
//                            ui->valueTechniciens);
// ============================================================
class EmployeStats
{
public:
    // Met à jour les 3 labels de statistiques
    static void charger(QLabel *labelTotal,
                        QLabel *labelOuvriers,
                        QLabel *labelTechniciens);

    // Retourne le nombre d'employés par poste (extensible)
    static int parPoste(const QString &poste);

    // Retourne le total
    static int total();

private:
    EmployeStats() = delete;
};

#endif // EMPLOYE_STATS_H
