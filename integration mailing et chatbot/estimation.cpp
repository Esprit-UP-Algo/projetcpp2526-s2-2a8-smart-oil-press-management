#include "estimation.h"
#include <QHeaderView>

Estimation::Estimation(const QSqlDatabase &db, QObject *parent)
    : QObject(parent), db(db)
{
}

// ─────────────────────────────────────────────────────────────
//  En-têtes du tableau
// ─────────────────────────────────────────────────────────────
void Estimation::setupTableHeaders(QTableWidget *table)
{
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({
        "Origine",
        "Type Stock",
        "Qté Stock (kg)",
        "Taux (%)",
        "Huile Estimée (kg)",
        "Statut"
    });
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSortingEnabled(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// ─────────────────────────────────────────────────────────────
//  Détermine le statut texte selon la quantité
// ─────────────────────────────────────────────────────────────
QString Estimation::getStatut(double quantite, double huileEstimee)
{
    if (quantite <= 0)
        return "❌ Stock vide";
    if (quantite < SEUIL_MIN_PRODUCTION)
        return "⚠ Insuffisant";
    if (huileEstimee >= 100)
        return "✅ Très bon";
    if (huileEstimee >= 20)
        return "✅ Bon";
    return "⚠ Faible rendement";
}

// ─────────────────────────────────────────────────────────────
//  Couleur de fond selon le statut
// ─────────────────────────────────────────────────────────────
QColor Estimation::getCouleurStatut(double quantite, double seuilAlerte)
{
    if (quantite <= 0)          return QColor("#ffcccc"); // rouge clair
    if (quantite < seuilAlerte) return QColor("#ffe0b2"); // orange clair
    return QColor("#e8f5e9");                              // vert clair
}

// ─────────────────────────────────────────────────────────────
//  CALCUL PRINCIPAL
// ─────────────────────────────────────────────────────────────
void Estimation::calculerEstimation(double tauxRendement,
                                    QTableWidget *tableEstimation,
                                    QLabel *valueTotalOlives,
                                    QLabel *valueHuileEstimee,
                                    QLabel *valueRendementMoyen,
                                    QLabel *valueStocksInsuffisants)
{
    if (!tableEstimation) return;

    setupTableHeaders(tableEstimation);

    // ── Récupérer UNIQUEMENT les stocks de type "Matière Première"
    //    car ce sont les olives qui produisent de l'huile
    QSqlQuery query(db);
    if (!query.exec(
            "SELECT ORIGINE, TYPE_STOCK, QUANTITE, SEUIL_ALERTE "
            "FROM ZIT.STOCK "
            "WHERE UPPER(TYPE_STOCK) LIKE UPPER('%Mati%') "
            "   OR UPPER(TYPE_STOCK) LIKE UPPER('%Olive%') "
            "   OR UPPER(TYPE_STOCK) LIKE UPPER('%Mati_re%') "
            "ORDER BY ORIGINE")) {
        QMessageBox::critical(nullptr, "Erreur",
                              "Impossible de charger les données :\n" +
                                  query.lastError().text());
        return;
    }

    tableEstimation->setRowCount(0);

    double totalOlives       = 0.0;
    double totalHuileEstimee = 0.0;
    int    stocksInsuffisants = 0;
    int    row               = 0;

    while (query.next()) {
        QString origine     = query.value(0).toString();
        QString typeStock   = query.value(1).toString();
        double  quantite    = query.value(2).toDouble();
        double  seuilAlerte = query.value(3).toDouble();

        // Calcul de l'huile estimée
        double huileEstimee = quantite * (tauxRendement / 100.0);

        totalOlives       += quantite;
        totalHuileEstimee += huileEstimee;

        if (quantite < SEUIL_MIN_PRODUCTION) stocksInsuffisants++;

        // ── Remplir la ligne ──────────────────────────────────
        tableEstimation->insertRow(row);

        QColor couleurFond = getCouleurStatut(quantite, seuilAlerte);

        // Col 0 : Origine
        auto *itemOrigine = new QTableWidgetItem(origine);
        itemOrigine->setBackground(couleurFond);
        tableEstimation->setItem(row, 0, itemOrigine);

        // Col 1 : Type Stock
        auto *itemType = new QTableWidgetItem(typeStock);
        itemType->setBackground(couleurFond);
        tableEstimation->setItem(row, 1, itemType);

        // Col 2 : Quantité Stock
        auto *itemQte = new QTableWidgetItem(
            QString::number(quantite, 'f', 2) + " kg");
        itemQte->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemQte->setBackground(couleurFond);
        tableEstimation->setItem(row, 2, itemQte);

        // Col 3 : Taux
        auto *itemTaux = new QTableWidgetItem(
            QString::number(tauxRendement, 'f', 1) + " %");
        itemTaux->setTextAlignment(Qt::AlignCenter);
        itemTaux->setBackground(couleurFond);
        tableEstimation->setItem(row, 3, itemTaux);

        // Col 4 : Huile Estimée
        auto *itemHuile = new QTableWidgetItem(
            QString::number(huileEstimee, 'f', 2) + " kg");
        itemHuile->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemHuile->setBackground(couleurFond);
        // Mettre en gras si production intéressante
        if (huileEstimee >= 20) {
            QFont f = itemHuile->font();
            f.setBold(true);
            itemHuile->setFont(f);
        }
        tableEstimation->setItem(row, 4, itemHuile);

        // Col 5 : Statut
        QString statut = getStatut(quantite, huileEstimee);
        auto *itemStatut = new QTableWidgetItem(statut);
        itemStatut->setTextAlignment(Qt::AlignCenter);
        itemStatut->setBackground(couleurFond);
        tableEstimation->setItem(row, 5, itemStatut);

        row++;
    }

    // ── Si aucune matière première trouvée ───────────────────
    if (row == 0) {
        QMessageBox::information(nullptr, "Estimation",
                                 "Aucun stock de type 'Matière Première' trouvé.\n"
                                 "L'estimation ne concerne que les stocks de matière première (olives).");

        // Afficher tout de même les valeurs à zéro
        if (valueTotalOlives)      valueTotalOlives->setText("0.00 kg");
        if (valueHuileEstimee)     valueHuileEstimee->setText("0.00 kg");
        if (valueRendementMoyen)   valueRendementMoyen->setText(
                QString::number(tauxRendement, 'f', 1) + " %");
        if (valueStocksInsuffisants) valueStocksInsuffisants->setText("0");
        return;
    }

    // ── Mettre à jour les cartes de résumé ───────────────────
    if (valueTotalOlives)
        valueTotalOlives->setText(
            QString::number(totalOlives, 'f', 2) + " kg");

    if (valueHuileEstimee)
        valueHuileEstimee->setText(
            QString::number(totalHuileEstimee, 'f', 2) + " kg");

    if (valueRendementMoyen)
        valueRendementMoyen->setText(
            QString::number(tauxRendement, 'f', 1) + " %");

    if (valueStocksInsuffisants) {
        valueStocksInsuffisants->setText(
            QString::number(stocksInsuffisants));
        // Rouge si des stocks insuffisants
        if (stocksInsuffisants > 0)
            valueStocksInsuffisants->setStyleSheet(
                "color:#ffaaaa; font:900 20pt 'Segoe UI';");
        else
            valueStocksInsuffisants->setStyleSheet(
                "color:#aaffaa; font:900 20pt 'Segoe UI';");
    }

    qDebug() << "Estimation calculée — Olives:" << totalOlives
             << "kg → Huile estimée:" << totalHuileEstimee
             << "kg (taux:" << tauxRendement << "%)";
}
