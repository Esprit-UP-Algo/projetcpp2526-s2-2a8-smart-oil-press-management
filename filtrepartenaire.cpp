#include "filtrepartenaire.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

FiltrePartenaire::FiltrePartenaire() {}

// ─────────────────────────────────────────────────────────────────────────────
// Tri par investissement décroissant via ORDER BY côté SQL
// ─────────────────────────────────────────────────────────────────────────────
QList<Partenaire> FiltrePartenaire::trierParInvestissementDecroissant()
{
    QList<Partenaire> liste;

    // On cast INVESTISSEMENT en NUMBER pour un tri numérique correct
    QSqlQuery query(
        "SELECT ID_PARTENAIRE, NOM, EMAIL, INVESTISSEMENT, TELEPHONE, "
        "NVL(ID_EMPLOYE, 0) "
        "FROM PARTENAIRE "
        "ORDER BY TO_NUMBER(INVESTISSEMENT) DESC"
        );

    if (query.lastError().isValid()) {
        qDebug() << "[FiltrePartenaire::trierParInvestissementDecroissant] ERREUR :"
                 << query.lastError().text();
        return liste;
    }

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
