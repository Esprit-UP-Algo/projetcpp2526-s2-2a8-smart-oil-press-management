#ifndef STATISTIQUE_PARTENAIRE_H
#define STATISTIQUE_PARTENAIRE_H

#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class StatistiquePartenaire
{
public:
    StatistiquePartenaire();

    // Charge les stats depuis la DB et met à jour les labels
    void calculerEtAfficher(QLabel *labelNbPartenaires,
                            QLabel *labelTotalInvestissement);

    // Getters
    int    getNbPartenaires()      const { return nbPartenaires; }
    double getTotalInvestissement() const { return totalInvestissement; }

private:
    bool chargerStats();

    int    nbPartenaires;
    double totalInvestissement;
};

#endif // STATISTIQUE_PARTENAIRE_H
