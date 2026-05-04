#ifndef ESTIMATION_H
#define ESTIMATION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <QMessageBox>
#include <QColor>
#include <QFont>
#include <QDebug>

class Estimation : public QObject
{
    Q_OBJECT

public:
    explicit Estimation(const QSqlDatabase &db, QObject *parent = nullptr);

    // Lance le calcul avec le taux fourni par l'utilisateur
    void calculerEstimation(double tauxRendement,
                            QTableWidget *tableEstimation,
                            QLabel *valueTotalOlives,
                            QLabel *valueHuileEstimee,
                            QLabel *valueRendementMoyen,
                            QLabel *valueStocksInsuffisants);

private:
    QSqlDatabase db;

    // Seuil minimum en kg pour considérer un stock comme suffisant
    static constexpr double SEUIL_MIN_PRODUCTION = 5.0;

    void setupTableHeaders(QTableWidget *table);
    QString getStatut(double quantite, double huileEstimee);
    QColor  getCouleurStatut(double quantite, double seuilAlerte);
};

#endif // ESTIMATION_H
