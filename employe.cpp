#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <cstdlib>  // pour rand() et srand()

Employe::Employe() {}

Employe::Employe(int id, QString nom, QString prenom, QString poste, int salaire, QDate date_embauche)
{
    this->id_employe    = id;
    this->nom           = nom;
    this->prenom        = prenom;
    this->poste         = poste;
    this->salaire       = salaire;
    this->date_embauche = date_embauche;
}

// =============================================================================
//  GÉNÉRATION ID ALÉATOIRE 5 CHIFFRES
// =============================================================================

int Employe::genererIdAleatoire()
{
    // Initialiser le générateur avec l'heure courante
    srand(static_cast<unsigned int>(
        QDateTime::currentMSecsSinceEpoch() & 0xFFFFFFFF));

    int  newId        = -1;
    bool idDisponible = false;

    while (!idDisponible) {
        // Générer un entier aléatoire entre 10000 et 99999
        newId = 10000 + (rand() % 90000);

        // Vérifier que cet ID n'existe pas déjà en base
        QSqlQuery qCheck;
        qCheck.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_EMPLOYE = :id");
        qCheck.bindValue(":id", newId);

        if (qCheck.exec() && qCheck.next()) {
            if (qCheck.value(0).toInt() == 0)
                idDisponible = true; // ID libre, on peut l'utiliser
        } else {
            qDebug() << "Erreur genererIdAleatoire:" << qCheck.lastError().text();
            return -1;
        }
    }
    return newId;
}

// =============================================================================
//  CRUD
// =============================================================================

bool Employe::ajouter()
{
    // Générer un ID aléatoire de 5 chiffres
    int newId = genererIdAleatoire();
    if (newId == -1) {
        qDebug() << "Erreur: impossible de générer un ID unique.";
        return false;
    }

    this->id_employe = newId; // Sauvegarder pour getLastInsertedId()

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, DATE_EMBAUCHE) "
        "VALUES (:id, :nom, :prenom, :poste, :salaire, :date_embauche)");
    query.bindValue(":id",            newId);
    query.bindValue(":nom",           nom);
    query.bindValue(":prenom",        prenom);
    query.bindValue(":poste",         poste);
    query.bindValue(":salaire",       salaire);
    query.bindValue(":date_embauche", date_embauche);

    if (!query.exec()) {
        qDebug() << "Erreur ajouter:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::ajouterAvecMdp(const QString &mdp)
{
    // Générer un ID aléatoire de 5 chiffres
    int newId = genererIdAleatoire();
    if (newId == -1) {
        qDebug() << "Erreur: impossible de générer un ID unique.";
        return false;
    }

    this->id_employe = newId; // Sauvegarder pour getLastInsertedId()

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, DATE_EMBAUCHE, MDP) "
        "VALUES (:id, :nom, :prenom, :poste, :salaire, :date_embauche, :mdp)");
    query.bindValue(":id",            newId);
    query.bindValue(":nom",           nom);
    query.bindValue(":prenom",        prenom);
    query.bindValue(":poste",         poste);
    query.bindValue(":salaire",       salaire);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":mdp",           mdp);

    if (!query.exec()) {
        qDebug() << "Erreur ajouterAvecMdp:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYE SET NOM=:nom, PRENOM=:prenom, POSTE=:poste, "
        "SALAIRE=:salaire, DATE_EMBAUCHE=:date_embauche "
        "WHERE ID_EMPLOYE=:id");
    query.bindValue(":nom",           nom);
    query.bindValue(":prenom",        prenom);
    query.bindValue(":poste",         poste);
    query.bindValue(":salaire",       salaire);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":id",            id_employe);

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
    model->setQuery(
        "SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, "
        "TO_CHAR(DATE_EMBAUCHE,'DD/MM/YYYY') AS DATE_EMBAUCHE FROM EMPLOYE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Embauche"));

    return model;
}

int Employe::getLastInsertedId()
{
    // Retourne directement l'ID généré et sauvegardé dans this->id_employe
    return this->id_employe;
}

// =============================================================================
//  STATISTIQUES
// =============================================================================

int Employe::getTotalEmployes()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE");
    if (query.exec() && query.next())
        return query.value(0).toInt();
    return 0;
}

int Employe::getNombreParPoste(const QString &poste)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE POSTE = :poste");
    query.bindValue(":poste", poste);
    if (query.exec() && query.next())
        return query.value(0).toInt();
    return 0;
}
