#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QMap>
#include <QString>
#include <QDebug>

class Statistiques : public QObject
{
    Q_OBJECT

public:
    explicit Statistiques(const QSqlDatabase &db, QObject *parent = nullptr);

    // Met à jour tous les labels de statistiques
    void chargerStats(QLabel *valueTotalStocks,
                      QLabel *valueAlertStocks,
                      QLabel *valueTotalQuantite,
                      QLabel *valueMoyenneQuantite,
                      QLabel *valueStockMax,
                      QLabel *valueStockMin,
                      QLabel *valueNbOrigines,
                      QLabel *valueStockCritique);

private:
    QSqlDatabase db;

    int    getTotalArticles();
    int    getArticlesEnAlerte();
    double getTotalQuantite();
    double getMoyenneQuantite();
    QString getStockMaxQuantite();
    QString getStockMinQuantite();
    int    getNbOriginesDistinctes();
    int    getStocksCritiques();  // quantite < seuil_alerte
};

#endif // STATISTIQUES_H
