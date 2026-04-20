#ifndef EMPLOYE_TRI_H
#define EMPLOYE_TRI_H

#include "employe.h"
#include <QList>

class EmployeTri
{
public:
    EmployeTri();

    // Charge tous les employés depuis la DB
    static QList<Employe> chargerTousLesEmployes();

    // Méthodes de tri
    static QList<Employe> trierParNom(const QList<Employe> &employes, bool ascendant = true);
    static QList<Employe> trierParPrenom(const QList<Employe> &employes, bool ascendant = true);
    static QList<Employe> trierParPoste(const QList<Employe> &employes);
    static QList<Employe> trierParSalaire(const QList<Employe> &employes, bool ascendant = true);
    static QList<Employe> trierParDateEmbauche(const QList<Employe> &employes, bool ascendant = true);
};

#endif // EMPLOYE_TRI_H
