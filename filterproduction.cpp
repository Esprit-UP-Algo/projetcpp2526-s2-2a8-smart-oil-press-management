#include "filterproduction.h"

FilterProduction::FilterProduction() {}

// ─────────────────────────────────────────────────────────────────────────────
// execEtRemplir — shared helper: run SQL and fill the QTableWidget
// ─────────────────────────────────────────────────────────────────────────────
void FilterProduction::execEtRemplir(const QString &sql, QTableWidget *table)
{
    table->setRowCount(0);

    QSqlQuery query;
    if (!query.exec(sql)) {
        qDebug() << "FilterProduction::execEtRemplir error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        table->setItem(row, 0,
                       new QTableWidgetItem(query.value("ID_PROD").toString()));

        QDate date = query.value("DATE_PROD").toDate();
        table->setItem(row, 1,
                       new QTableWidgetItem(date.toString("dd/MM/yyyy")));

        table->setItem(row, 2,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_OLIVE").toDouble(), 'f', 2) + " kg"));

        table->setItem(row, 3,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_HUILE").toDouble(), 'f', 2) + " L"));

        table->setItem(row, 4,
                       new QTableWidgetItem(
                           QString::number(query.value("RENDEMENT").toDouble(), 'f', 2) + " %"));

        for (int col = 0; col < 5; col++) {
            if (table->item(row, col))
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        row++;
    }
    table->resizeColumnsToContents();
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. Trier par date la plus récente
// ─────────────────────────────────────────────────────────────────────────────
void FilterProduction::filtrerParDateRecente(QTableWidget *table)
{
    execEtRemplir(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "ORDER BY DATE_PROD DESC",
        table);
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. Trier par quantité d'olives décroissante
// ─────────────────────────────────────────────────────────────────────────────
void FilterProduction::filtrerParOliveDecroissant(QTableWidget *table)
{
    execEtRemplir(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "ORDER BY QUANTITE_OLIVE DESC",
        table);
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. Trier par quantité d'huile décroissante
// ─────────────────────────────────────────────────────────────────────────────
void FilterProduction::filtrerParHuileDecroissant(QTableWidget *table)
{
    execEtRemplir(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "ORDER BY QUANTITE_HUILE DESC",
        table);
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. Trier par rendement décroissant
// ─────────────────────────────────────────────────────────────────────────────
void FilterProduction::filtrerParRendementDecroissant(QTableWidget *table)
{
    execEtRemplir(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "ORDER BY RENDEMENT DESC",
        table);
}
