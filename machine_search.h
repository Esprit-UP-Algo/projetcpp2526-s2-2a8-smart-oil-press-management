#ifndef MACHINE_SEARCH_H
#define MACHINE_SEARCH_H

#include <QTableWidget>
#include <QString>
#include "machine.h"

class MachineSearch
{
public:
    static void chargerTout(QTableWidget *table);
    static void filtrer(QTableWidget *table, const QString &terme);

private:
    MachineSearch() = delete;

    static void remplirLigne(QTableWidget *table, int row,
                             const QString &id,
                             const QString &type,
                             const QString &etat,
                             const QString &dateMaintenance,
                             const QString &duree);
};

#endif // MACHINE_SEARCH_H
