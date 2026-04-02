#include "machine.h"

#include <QSqlError>
#include <QDebug>

Machine::Machine()
    : id_machine(0), duree_fonctionnement(0)
{
}

Machine::Machine(int id,
                 const QString &type,
                 const QString &etat,
                 const QDate &dateMaintenance,
                 int dureeFonctionnement)
    : id_machine(id)
    , type_machine(type)
    , etat_machine(etat)
    , date_derniere_maintenance(dateMaintenance)
    , duree_fonctionnement(dureeFonctionnement)
{
}

bool Machine::ajouter()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO MACHINE (TYPE_MACHINE, ETAT_MACHINE, DATE_DERNIERE_MAINTENANCE, DUREE_FONCTIONNEMENT) "
        "VALUES (:type, :etat, :date_maintenance, :duree)");

    query.bindValue(":type", type_machine);
    query.bindValue(":etat", etat_machine);
    query.bindValue(":date_maintenance", date_derniere_maintenance);
    query.bindValue(":duree", duree_fonctionnement);

    if (!query.exec()) {
        qDebug() << "Erreur ajouter Machine:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Machine::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE MACHINE SET TYPE_MACHINE=:type, ETAT_MACHINE=:etat, "
        "DATE_DERNIERE_MAINTENANCE=:date_maintenance, DUREE_FONCTIONNEMENT=:duree "
        "WHERE ID_MACHINE=:id");

    query.bindValue(":type", type_machine);
    query.bindValue(":etat", etat_machine);
    query.bindValue(":date_maintenance", date_derniere_maintenance);
    query.bindValue(":duree", duree_fonctionnement);
    query.bindValue(":id", id_machine);

    if (!query.exec()) {
        qDebug() << "Erreur modifier Machine:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Machine::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM MACHINE WHERE ID_MACHINE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur supprimer Machine:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Machine::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID_MACHINE, TYPE_MACHINE, ETAT_MACHINE, "
        "TO_CHAR(DATE_DERNIERE_MAINTENANCE,'DD/MM/YYYY') AS DATE_DERNIERE_MAINTENANCE, "
        "DUREE_FONCTIONNEMENT "
        "FROM MACHINE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Maintenance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Durée (h)"));

    return model;
}
