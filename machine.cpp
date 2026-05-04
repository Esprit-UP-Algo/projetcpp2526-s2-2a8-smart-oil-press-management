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

    // Envoie une alerte email si l'état est mauvais
    envoyerAlerteMauvaisEtatSiNecessaire();

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

    // Envoie une alerte email si l'état est mauvais
    envoyerAlerteMauvaisEtatSiNecessaire();

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

void Machine::envoyerAlerteMauvaisEtatSiNecessaire()
{
    // Vérifie si l'état est mauvais
    if (etat_machine.toLower() == "mauvais" || 
        etat_machine.toLower() == "bad" || 
        etat_machine.toLower() == "panne" ||
        etat_machine.toLower() == "hors service") {
        
        Mailing mailer;
        
        QString sujet = QString("[ALERTE] Machine %1 en mauvais état").arg(type_machine);
        
        QString message = QString(
            "Machine ID: %1\n"
            "Type: %2\n"
            "État: %3\n"
            "Durée de fonctionnement: %4 heures\n"
            "Date dernière maintenance: %5\n\n"
            "ALERTE: Cette machine est en mauvais état et nécessite une intervention urgente."
        ).arg(id_machine)
         .arg(type_machine)
         .arg(etat_machine)
         .arg(duree_fonctionnement)
         .arg(date_derniere_maintenance.toString("dd/MM/yyyy"));
        
        // Envoie l'email à l'admin
        bool envoyeAvecSucces = mailer.envoyerEmailAdmin(message, sujet);
        
        if (envoyeAvecSucces) {
            qDebug() << "[Machine] Email d'alerte envoyé avec succès pour la machine" << id_machine;
        } else {
            qDebug() << "[Machine] ERREUR lors de l'envoi de l'email d'alerte:" << mailer.erreurMessage();
        }
    }
}
