#ifndef FILTERPRODUCTION_H
#define FILTERPRODUCTION_H

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

class FilterProduction
{
public:
    FilterProduction();

    // Filter options — called after user picks from the menu
    void filtrerParDateRecente      (QTableWidget *table);  // 1. most recent first
    void filtrerParOliveDecroissant (QTableWidget *table);  // 2. olive qty DESC
    void filtrerParHuileDecroissant (QTableWidget *table);  // 3. huile qty DESC
    void filtrerParRendementDecroissant(QTableWidget *table); // 4. rendement DESC

private:
    void execEtRemplir(const QString &sql, QTableWidget *table);
};

#endif // FILTERPRODUCTION_H
