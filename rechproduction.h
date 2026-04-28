#ifndef RECHPRODUCTION_H
#define RECHPRODUCTION_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RechProduction
{
public:
    RechProduction();

    // Main search entry point — parses the term and filters the table
    // Rules:
    //   "123.4 kg" or "123 KG"  → filter by quantite_olive == value
    //   "50.0 l"  or "50 L"     → filter by quantite_huile == value
    //   "04/06/2025"             → filter by date (MM/DD/YYYY)
    void rechercher(const QString &terme, QTableWidget *table);

private:
    void rechercherParOlive(double valeur,  QTableWidget *table);
    void rechercherParHuile(double valeur,  QTableWidget *table);
    void rechercherParDate (const QDate &d, QTableWidget *table);

    void remplirTable(QSqlQuery &query, QTableWidget *table);
};

#endif // RECHPRODUCTION_H

