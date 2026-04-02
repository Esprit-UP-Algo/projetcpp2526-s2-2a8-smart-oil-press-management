#include "partenaire.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// ─────────────────────────────────────────────────────────────────────────────
// Constructeurs
// ─────────────────────────────────────────────────────────────────────────────

Partenaire::Partenaire()
    : id(0), nom(""), email(""), investissement(""), telephone(""), idEmploye(0)
{
}

Partenaire::Partenaire(int id,
                       const QString &nom,
                       const QString &email,
                       const QString &investissement,
                       const QString &telephone,
                       int idEmploye)
    : id(id), nom(nom), email(email),
    investissement(investissement), telephone(telephone), idEmploye(idEmploye)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// Ajouter
// ─────────────────────────────────────────────────────────────────────────────
bool Partenaire::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PARTENAIRE "
                  "(NOM, EMAIL, INVESTISSEMENT, TELEPHONE, ID_EMPLOYE) "
                  "VALUES (:nom, :email, :investissement, :telephone, :idEmploye)");
    query.bindValue(":nom",            nom);
    query.bindValue(":email",          email);
    query.bindValue(":investissement", investissement);
    query.bindValue(":telephone",      telephone);
    query.bindValue(":idEmploye",      idEmploye > 0 ? QVariant(idEmploye) : QVariant(QVariant::Int));
    if (!query.exec()) {
        qDebug() << "[Partenaire::ajouter] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifier
// ─────────────────────────────────────────────────────────────────────────────
bool Partenaire::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE PARTENAIRE SET "
                  "NOM = :nom, "
                  "EMAIL = :email, "
                  "INVESTISSEMENT = :investissement, "
                  "TELEPHONE = :telephone, "
                  "ID_EMPLOYE = :idEmploye "
                  "WHERE ID_PARTENAIRE = :id");
    query.bindValue(":nom",            nom);
    query.bindValue(":email",          email);
    query.bindValue(":investissement", investissement);
    query.bindValue(":telephone",      telephone);
    query.bindValue(":idEmploye",      idEmploye > 0 ? QVariant(idEmploye) : QVariant(QVariant::Int));
    query.bindValue(":id",             id);

    if (!query.exec()) {
        qDebug() << "[Partenaire::modifier] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Supprimer
// ─────────────────────────────────────────────────────────────────────────────

bool Partenaire::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM PARTENAIRE WHERE ID_PARTENAIRE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "[Partenaire::supprimer] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Afficher tous
// ─────────────────────────────────────────────────────────────────────────────

QList<Partenaire> Partenaire::afficherTous()
{
    QList<Partenaire> liste;

    QSqlQuery query("SELECT ID_PARTENAIRE, NOM, EMAIL, INVESTISSEMENT, TELEPHONE, "
                    "NVL(ID_EMPLOYE, 0) "
                    "FROM PARTENAIRE ");

    while (query.next()) {
        Partenaire p(
            query.value(0).toInt(),    // ID_PARTENAIRE
            query.value(1).toString(), // NOM
            query.value(2).toString(), // EMAIL
            query.value(3).toString(), // INVESTISSEMENT
            query.value(4).toString(), // TELEPHONE
            query.value(5).toInt()     // ID_EMPLOYE
            );
        liste.append(p);
    }
    return liste;
}

// ─────────────────────────────────────────────────────────────────────────────
// Lister les employés (statique)
// ─────────────────────────────────────────────────────────────────────────────

QList<QPair<int,QString>> Partenaire::listerEmployes()
{
    QList<QPair<int,QString>> liste;

    QSqlQuery query("SELECT ID_EMPLOYE, NOM || ' ' || PRENOM FROM EMPLOYE ORDER BY NOM");

    while (query.next()) {
        int     idEmp  = query.value(0).toInt();
        QString nomEmp = query.value(1).toString();
        liste.append(qMakePair(idEmp, nomEmp));
    }
    return liste;
}
