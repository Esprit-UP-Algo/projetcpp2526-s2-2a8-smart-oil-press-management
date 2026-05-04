#include "employe_tri.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <algorithm>

EmployeTri::EmployeTri() {}

QList<Employe> EmployeTri::chargerTousLesEmployes()
{
    QList<Employe> liste;
    QSqlQuery query;

    // Même requête que dans employe.cpp mais sans TO_CHAR
    // pour récupérer la date en QDate directement
    if (!query.exec("SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, DATE_EMBAUCHE "
                    "FROM EMPLOYE ORDER BY ID_EMPLOYE")) {
        qDebug() << "Erreur chargerTousLesEmployes:" << query.lastError().text();
        return liste;
    }

    while (query.next()) {
        Employe e(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toInt(),
            query.value(5).toDate()   // QDate directement depuis Oracle
        );
        liste.append(e);
    }
    return liste;
}

QList<Employe> EmployeTri::trierParNom(const QList<Employe> &employes, bool ascendant)
{
    QList<Employe> result = employes;
    std::sort(result.begin(), result.end(),
              [ascendant](const Employe &a, const Employe &b) {
                  return ascendant ? a.getNom().toLower() < b.getNom().toLower()
                                   : a.getNom().toLower() > b.getNom().toLower();
              });
    return result;
}

QList<Employe> EmployeTri::trierParPrenom(const QList<Employe> &employes, bool ascendant)
{
    QList<Employe> result = employes;
    std::sort(result.begin(), result.end(),
              [ascendant](const Employe &a, const Employe &b) {
                  return ascendant ? a.getPrenom().toLower() < b.getPrenom().toLower()
                                   : a.getPrenom().toLower() > b.getPrenom().toLower();
              });
    return result;
}

QList<Employe> EmployeTri::trierParPoste(const QList<Employe> &employes)
{
    QList<Employe> result = employes;
    std::sort(result.begin(), result.end(),
              [](const Employe &a, const Employe &b) {
                  return a.getPoste().toLower() < b.getPoste().toLower();
              });
    return result;
}

QList<Employe> EmployeTri::trierParSalaire(const QList<Employe> &employes, bool ascendant)
{
    QList<Employe> result = employes;
    std::sort(result.begin(), result.end(),
              [ascendant](const Employe &a, const Employe &b) {
                  return ascendant ? a.getSalaire() < b.getSalaire()
                                   : a.getSalaire() > b.getSalaire();
              });
    return result;
}

QList<Employe> EmployeTri::trierParDateEmbauche(const QList<Employe> &employes, bool ascendant)
{
    QList<Employe> result = employes;
    std::sort(result.begin(), result.end(),
              [ascendant](const Employe &a, const Employe &b) {
                  return ascendant ? a.getDateEmbauche() < b.getDateEmbauche()
                                   : a.getDateEmbauche() > b.getDateEmbauche();
              });
    return result;
}
