#include "recherche.h"
#include <QHeaderView>

Recherche::Recherche(const QSqlDatabase &db, QObject *parent)
    : QObject(parent), db(db)
{
}

void Recherche::setupTableHeaders(QTableWidget *table)
{
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID Stock", "Type Stock", "Quantité (kg)", "Seuil Alerte", "Origine"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setCursor(Qt::PointingHandCursor);
    table->setSortingEnabled(true);
}

void Recherche::remplirTableau(QSqlQuery &query, QTableWidget *table)
{
    // Désactiver le tri pendant le remplissage
    table->setSortingEnabled(false);

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        for (int col = 0; col < 5; col++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (col == 2 || col == 3) {
                double val = query.value(col).toDouble();
                item->setText(QString::number(val, 'f', 2));
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                item->setData(Qt::UserRole, val);
            } else {
                item->setText(query.value(col).toString());
            }
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }
        row++;
    }

    // Réactiver le tri après remplissage
    table->setSortingEnabled(true);

    if (row == 0) {
        QMessageBox::information(nullptr, "Recherche",
                                 "Aucun résultat trouvé pour cette recherche.");
    }

    qDebug() << "Recherche terminée. Résultats :" << row;
}

void Recherche::rechercherStock(const QString &terme, QTableWidget *table)
{
    setupTableHeaders(table);

    if (terme.trimmed().isEmpty()) {
        QSqlQuery query(db);
        if (!query.exec("SELECT ID_STOCK, TYPE_STOCK, QUANTITE, SEUIL_ALERTE, ORIGINE "
                        "FROM ZIT.STOCK ORDER BY ID_STOCK")) {
            QMessageBox::critical(nullptr, "Erreur",
                                  "Impossible de charger les stocks :\n" + query.lastError().text());
            return;
        }
        remplirTableau(query, table);
        return;
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT ID_STOCK, TYPE_STOCK, QUANTITE, SEUIL_ALERTE, ORIGINE "
        "FROM ZIT.STOCK "
        "WHERE TO_CHAR(ID_STOCK) LIKE :t1 "
        "OR UPPER(TYPE_STOCK)   LIKE UPPER(:t2) "
        "OR UPPER(ORIGINE)      LIKE UPPER(:t3) "
        "ORDER BY ID_STOCK"
        );

    QString pattern = "%" + terme.trimmed() + "%";
    query.bindValue(":t1", pattern);
    query.bindValue(":t2", pattern);
    query.bindValue(":t3", pattern);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur de recherche",
                              "Échec de la recherche :\n" + query.lastError().text());
        return;
    }

    remplirTableau(query, table);
}
