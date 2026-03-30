#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QDate>
#include <QDebug>

class Production
{
public:
    Production();

    // Getters
    int    getId()           const { return id_prod; }
    QDate  getDateProd()     const { return date_prod; }
    double getQuantiteHuile()const { return quantite_huile; }
    double getQuantiteOlive()const { return quantite_olive; }
    double getRendement()    const { return rendement; }

    // Setters
    void setId(int id)                  { id_prod       = id; }
    void setDateProd(const QDate &date) { date_prod      = date; }
    void setQuantiteHuile(double qte)   { quantite_huile = qte; }
    void setQuantiteOlive(double qte)   { quantite_olive = qte; }
    void setRendement(double r)         { rendement      = r; }

    // CRUD
    bool ajouter();
    void afficher(QTableWidget *table);
    bool modifier();
    bool supprimer(int id);

private:
    int    id_prod;
    QDate  date_prod;
    double quantite_huile;
    double quantite_olive;
    double rendement;
};

#endif // PRODUCTION_H
