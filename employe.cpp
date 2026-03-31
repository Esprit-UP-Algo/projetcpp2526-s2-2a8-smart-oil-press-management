#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Employe::Employe() {}

Employe::Employe(int id, QString nom, QString prenom, QString poste, int salaire, QDate date_embauche)
{
    this->id_employe = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->salaire = salaire;
    this->date_embauche = date_embauche;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (NOM, PRENOM, POSTE, SALAIRE, DATE_EMBAUCHE) "
                  "VALUES (:nom, :prenom, :poste, :salaire, :date_embauche)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", date_embauche);

    if (!query.exec()) {
        qDebug() << "Erreur ajouter:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:nom, PRENOM=:prenom, POSTE=:poste, "
                  "SALAIRE=:salaire, DATE_EMBAUCHE=:date_embauche "
                  "WHERE ID_EMPLOYE=:id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":id", id_employe);

    if (!query.exec()) {
        qDebug() << "Erreur modifier:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur supprimer:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, "
                    "TO_CHAR(DATE_EMBAUCHE,'DD/MM/YYYY') AS DATE_EMBAUCHE FROM EMPLOYE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Embauche"));

    return model;
}

// ===================== STATISTIQUES =====================

int Employe::getTotalEmployes()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Employe::getNombreParPoste(const QString &poste)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE POSTE = :poste");
    query.bindValue(":poste", poste);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}
