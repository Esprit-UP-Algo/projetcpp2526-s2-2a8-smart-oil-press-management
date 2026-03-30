#include "production.h"

Production::Production()
    : id_prod(0),
    date_prod(QDate::currentDate()),
    quantite_huile(0.0),
    quantite_olive(0.0),
    rendement(0.0)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// AJOUTER — Insert a new production record into the DB
// ─────────────────────────────────────────────────────────────────────────────
bool Production::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO ZIT.PRODUCTION (DATE_PROD, QUANTITE_HUILE, QUANTITE_OLIVE, RENDEMENT) "
                  "VALUES (:date_prod, :quantite_huile, :quantite_olive, :rendement)");

    query.bindValue(":date_prod",      date_prod);
    query.bindValue(":quantite_huile", quantite_huile);
    query.bindValue(":quantite_olive", quantite_olive);
    query.bindValue(":rendement",      rendement);

    if (!query.exec()) {
        qDebug() << "Erreur ajouter production :" << query.lastError().text();
        return false;
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// AFFICHER — Load all production records from DB into the given QTableWidget
// ─────────────────────────────────────────────────────────────────────────────
void Production::afficher(QTableWidget *table)
{
    // Clear existing rows
    table->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
                  "FROM ZIT.PRODUCTION "
                  "ORDER BY ID_PROD ASC");

    if (!query.exec()) {
        qDebug() << "Erreur afficher production :" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        // Column 0 — ID
        table->setItem(row, 0,
                       new QTableWidgetItem(query.value("ID_PROD").toString()));

        // Column 1 — Date
        QDate date = query.value("DATE_PROD").toDate();
        table->setItem(row, 1,
                       new QTableWidgetItem(date.toString("dd/MM/yyyy")));

        // Column 2 — Quantité Olives
        table->setItem(row, 2,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_OLIVE").toDouble(), 'f', 2) + " kg"));

        // Column 3 — Quantité Huile
        table->setItem(row, 3,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_HUILE").toDouble(), 'f', 2) + " L"));

        // Column 4 — Rendement
        table->setItem(row, 4,
                       new QTableWidgetItem(
                           QString::number(query.value("RENDEMENT").toDouble(), 'f', 2) + " %"));

        // Make all cells read-only
        for (int col = 0; col < 5; col++) {
            if (table->item(row, col)) {
                table->item(row, col)
                ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
        }

        row++;
    }

    table->resizeColumnsToContents();
}

// ─────────────────────────────────────────────────────────────────────────────
// MODIFIER — Update an existing production record in the DB
// ─────────────────────────────────────────────────────────────────────────────
bool Production::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE ZIT.PRODUCTION "
                  "SET DATE_PROD       = :date_prod, "
                  "    QUANTITE_HUILE  = :quantite_huile, "
                  "    QUANTITE_OLIVE  = :quantite_olive, "
                  "    RENDEMENT       = :rendement "
                  "WHERE ID_PROD = :id_prod");

    query.bindValue(":date_prod",      date_prod);
    query.bindValue(":quantite_huile", quantite_huile);
    query.bindValue(":quantite_olive", quantite_olive);
    query.bindValue(":rendement",      rendement);
    query.bindValue(":id_prod",        id_prod);

    if (!query.exec()) {
        qDebug() << "Erreur modifier production :" << query.lastError().text();
        return false;
    }

    // Check that a row was actually updated
    if (query.numRowsAffected() == 0) {
        qDebug() << "Aucune production trouvée avec ID =" << id_prod;
        return false;
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// SUPPRIMER — Delete a production record from the DB by ID
// ─────────────────────────────────────────────────────────────────────────────
bool Production::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM ZIT.PRODUCTION WHERE ID_PROD = :id_prod");
    query.bindValue(":id_prod", id);

    if (!query.exec()) {
        qDebug() << "Erreur supprimer production :" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "Aucune production trouvée avec ID =" << id;
        return false;
    }

    return true;
}
