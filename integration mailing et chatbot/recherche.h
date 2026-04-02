#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>

class Recherche : public QObject
{
    Q_OBJECT

public:
    explicit Recherche(const QSqlDatabase &db, QObject *parent = nullptr);

    // Recherche dans la table STOCK
    void rechercherStock(const QString &terme, QTableWidget *table);

private:
    QSqlDatabase db;

    void setupTableHeaders(QTableWidget *table);
    void remplirTableau(QSqlQuery &query, QTableWidget *table);
};

#endif // RECHERCHE_H
