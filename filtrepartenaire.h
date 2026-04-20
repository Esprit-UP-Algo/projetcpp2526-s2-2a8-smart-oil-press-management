#ifndef FILTREPARTENAIRE_H
#define FILTREPARTENAIRE_H

#include "partenaire.h"
#include <QList>

class FiltrePartenaire
{
public:
    FiltrePartenaire();

    // Retourne la liste des partenaires triée par montant d'investissement
    // en ordre décroissant (le plus grand investissement en premier)
    static QList<Partenaire> trierParInvestissementDecroissant();
};

#endif // FILTREPARTENAIRE_H
