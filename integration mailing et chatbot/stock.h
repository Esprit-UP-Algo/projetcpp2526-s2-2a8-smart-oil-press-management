#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

class Stock : public QObject
{
    Q_OBJECT

public:
    explicit Stock(const QSqlDatabase &db, QObject *parent = nullptr);

    void loadData(QTableWidget *table);
    void addStock(const QString &typeStock, double quantite, double seuilAlerte, const QString &origine, QTableWidget *table);
    void updateStock(int id, const QString &typeStock, double quantite, double seuilAlerte, const QString &origine, QTableWidget *table);
    void deleteStock(int id, QTableWidget *table);
    void searchStock(const QString &searchTerm, QTableWidget *table);

private:
    QSqlDatabase db;

    void populateTable(QSqlQuery &query, QTableWidget *table);
    void setupTableHeaders(QTableWidget *table);
};

#endif // STOCK_H
