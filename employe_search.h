#ifndef EMPLOYE_SEARCH_H
#define EMPLOYE_SEARCH_H

#include <QTableWidget>
#include <QString>
#include "employe.h"

// ============================================================
//  EmployeSearch — Module de recherche / filtrage
//  Utilisation dans mainwindow.cpp :
//      EmployeSearch::filtrer(ui->employeTable, terme);
//      EmployeSearch::chargerTout(ui->employeTable);
// ============================================================
class EmployeSearch
{
public:
    // Recharge toutes les lignes depuis la BDD
    static void chargerTout(QTableWidget *table);

    // Filtre les lignes selon le terme (ID, Nom, Prénom, Poste)
    static void filtrer(QTableWidget *table, const QString &terme);

private:
    EmployeSearch() = delete;

    // Remplit une ligne du tableau
    static void remplirLigne(QTableWidget *table, int row,
                             const QString &id, const QString &nom,
                             const QString &prenom, const QString &poste,
                             const QString &salaire, const QString &date);
};

#endif // EMPLOYE_SEARCH_H
