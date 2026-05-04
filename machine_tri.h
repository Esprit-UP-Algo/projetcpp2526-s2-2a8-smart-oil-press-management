#ifndef MACHINE_TRI_H
#define MACHINE_TRI_H

#include <QTableWidget>

class MachineTri
{
public:
    MachineTri() = delete;

    static void trierParId(QTableWidget *table, bool ascendant = true);
    static void trierParType(QTableWidget *table, bool ascendant = true);
    static void trierParEtat(QTableWidget *table, bool ascendant = true);
    static void trierParDateMaintenance(QTableWidget *table, bool ascendant = true);
    static void trierParDuree(QTableWidget *table, bool ascendant = true);
    static void reinitialiser(QTableWidget *table);
};

#endif // MACHINE_TRI_H
