#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Machine
{
private:
    int id_machine;
    QString type_machine;
    QString etat_machine;
    QDate date_derniere_maintenance;
    int duree_fonctionnement;

public:
    Machine();
    Machine(int id,
            const QString &type,
            const QString &etat,
            const QDate &dateMaintenance,
            int dureeFonctionnement);

    int getId() const { return id_machine; }
    QString getType() const { return type_machine; }
    QString getEtat() const { return etat_machine; }
    QDate getDateMaintenance() const { return date_derniere_maintenance; }
    int getDureeFonctionnement() const { return duree_fonctionnement; }

    void setId(int id) { id_machine = id; }
    void setType(const QString &type) { type_machine = type; }
    void setEtat(const QString &etat) { etat_machine = etat; }
    void setDateMaintenance(const QDate &date) { date_derniere_maintenance = date; }
    void setDureeFonctionnement(int duree) { duree_fonctionnement = duree; }

    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
};

#endif // MACHINE_H
