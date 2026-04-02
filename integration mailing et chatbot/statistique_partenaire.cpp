#include "statistique_partenaire.h"

StatistiquePartenaire::StatistiquePartenaire()
    : nbPartenaires(0), totalInvestissement(0.0)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// chargerStats — requête agrégée sur la table PARTENAIRE
// ─────────────────────────────────────────────────────────────────────────────
bool StatistiquePartenaire::chargerStats()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "    COUNT(*)                          AS NB_PARTENAIRES, "
        "    NVL(SUM(TO_NUMBER(INVESTISSEMENT)), 0) AS TOTAL_INVEST "
        "FROM PARTENAIRE"
        );

    if (!query.exec()) {
        qDebug() << "[StatistiquePartenaire] Erreur SQL :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        nbPartenaires      = query.value("NB_PARTENAIRES").toInt();
        totalInvestissement = query.value("TOTAL_INVEST").toDouble();
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// calculerEtAfficher — charge et pousse dans les labels UI
// ─────────────────────────────────────────────────────────────────────────────
void StatistiquePartenaire::calculerEtAfficher(QLabel *labelNbPartenaires,
                                               QLabel *labelTotalInvestissement)
{
    if (!chargerStats()) {
        if (labelNbPartenaires)       labelNbPartenaires->setText("Erreur");
        if (labelTotalInvestissement) labelTotalInvestissement->setText("Erreur");
        return;
    }

    if (labelNbPartenaires)
        labelNbPartenaires->setText(QString::number(nbPartenaires));

    if (labelTotalInvestissement)
        labelTotalInvestissement->setText(
            QString::number(totalInvestissement, 'f', 2));
}
