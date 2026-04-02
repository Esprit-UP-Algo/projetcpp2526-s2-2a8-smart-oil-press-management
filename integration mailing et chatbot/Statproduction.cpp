#include "statproduction.h"

StatProduction::StatProduction()
    : totalProductions(0),
    totalOlives(0.0),
    totalHuile(0.0),
    rendementMoyen(0.0),
    rendementMax(0.0),
    rendementMin(0.0)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// chargerStats — fetch aggregated statistics from the DB
// ─────────────────────────────────────────────────────────────────────────────
bool StatProduction::chargerStats()
{
    QSqlQuery query;

    query.prepare(
        "SELECT "
        "    COUNT(*)                    AS TOTAL_PROD, "
        "    NVL(SUM(QUANTITE_OLIVE), 0) AS TOTAL_OLIVES, "
        "    NVL(SUM(QUANTITE_HUILE), 0) AS TOTAL_HUILE, "
        "    NVL(AVG(RENDEMENT),      0) AS REND_MOY, "
        "    NVL(MAX(RENDEMENT),      0) AS REND_MAX, "
        "    NVL(MIN(RENDEMENT),      0) AS REND_MIN "
        "FROM ZIT.PRODUCTION"
        );

    if (!query.exec()) {
        qDebug() << "Erreur chargement statistiques :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        totalProductions = query.value("TOTAL_PROD").toInt();
        totalOlives      = query.value("TOTAL_OLIVES").toDouble();
        totalHuile       = query.value("TOTAL_HUILE").toDouble();
        rendementMoyen   = query.value("REND_MOY").toDouble();
        rendementMax     = query.value("REND_MAX").toDouble();
        rendementMin     = query.value("REND_MIN").toDouble();
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// calculerEtAfficher — load stats from DB and push them into the UI labels
// ─────────────────────────────────────────────────────────────────────────────
void StatProduction::calculerEtAfficher(QLabel *labelTotal,
                                        QLabel *labelOlives,
                                        QLabel *labelHuile,
                                        QLabel *labelRendement)
{
    if (!chargerStats()) {
        // If DB failed, show error state in labels
        if (labelTotal)     labelTotal->setText("Erreur");
        if (labelOlives)    labelOlives->setText("Erreur");
        if (labelHuile)     labelHuile->setText("Erreur");
        if (labelRendement) labelRendement->setText("Erreur");
        return;
    }

    // Total productions
    if (labelTotal)
        labelTotal->setText(QString::number(totalProductions));

    // Total olives in kg
    if (labelOlives)
        labelOlives->setText(QString::number(totalOlives, 'f', 2));

    // Total huile in L
    if (labelHuile)
        labelHuile->setText(QString::number(totalHuile, 'f', 2));

    // Average rendement in %
    // Also append max/min as a tooltip for extra info
    if (labelRendement) {
        labelRendement->setText(QString::number(rendementMoyen, 'f', 2) + "%");
        labelRendement->setToolTip(
            QString("Max : %1 %\nMin : %2 %")
                .arg(QString::number(rendementMax, 'f', 2))
                .arg(QString::number(rendementMin, 'f', 2))
            );
    }
}
