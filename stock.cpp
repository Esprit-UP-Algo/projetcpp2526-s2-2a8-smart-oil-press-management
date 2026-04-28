#include "stock.h"
#include <QHeaderView>

Stock::Stock(const QSqlDatabase &db, QObject *parent)
    : QObject(parent), db(db)
{
}

void Stock::setupTableHeaders(QTableWidget *table)
{
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID Stock", "Type Stock", "Quantité (kg)", "Seuil Alerte", "Origine"});
    table->horizontalHeader()->setStretchLastSection(true);

    // ── Tri par clic sur l'en-tête ──────────────────────────
    // Un clic  → tri croissant ↑
    // Deux clics → tri décroissant ↓
    table->setSortingEnabled(true);

    // Style visuel : curseur "main" sur les en-têtes pour indiquer
    // qu'ils sont cliquables
    table->horizontalHeader()->setCursor(Qt::PointingHandCursor);

    // Optionnel : trier par défaut par ID_STOCK croissant au départ
    table->sortByColumn(0, Qt::AscendingOrder);
}

void Stock::populateTable(QSqlQuery &query, QTableWidget *table)
{
    // ⚠️ Désactiver le tri PENDANT le remplissage pour éviter
    //    les décalages de lignes en cours d'insertion
    table->setSortingEnabled(false);

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        for (int col = 0; col < 5; col++) {
            QTableWidgetItem *item = new QTableWidgetItem();

            if (col == 2 || col == 3) {
                // Colonnes numériques : stocker la valeur numérique
                // pour que le tri soit numérique (pas alphabétique)
                double val = query.value(col).toDouble();
                item->setText(QString::number(val, 'f', 2));
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

                // Clé de tri numérique
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

    qDebug() << "Stock chargé. Lignes :" << row;
}

void Stock::loadData(QTableWidget *table)
{
    qDebug() << "Chargement des données stock...";
    setupTableHeaders(table);

    QSqlQuery query(db);
    if (!query.exec("SELECT ID_STOCK, TYPE_STOCK, QUANTITE, SEUIL_ALERTE, ORIGINE FROM ZIT.STOCK ORDER BY ID_STOCK")) {
        QMessageBox::critical(nullptr, "Erreur Base de Données",
                              "Échec du chargement des stocks :\n" + query.lastError().text());
        return;
    }
    populateTable(query, table);
}

void Stock::addStock(const QString &typeStock, double quantite, double seuilAlerte,
                     const QString &origine, QTableWidget *table)
{
    if (typeStock == "Sélectionner ...") {
        QMessageBox::warning(nullptr, "Champ manquant", "Veuillez sélectionner un type de stock.");
        return;
    }
    if (origine.isEmpty()) {
        QMessageBox::warning(nullptr, "Champ manquant", "Veuillez saisir l'origine du stock.");
        return;
    }

    QSqlQuery seqQuery(db);
    int nextId = -1;

    seqQuery.prepare("SELECT ZIT.STOCK_SEQ.NEXTVAL FROM DUAL");
    if (seqQuery.exec() && seqQuery.next()) {
        nextId = seqQuery.value(0).toInt();
    } else {
        QSqlQuery maxQuery(db);
        if (!maxQuery.exec("SELECT NVL(MAX(ID_STOCK), 0) + 1 FROM ZIT.STOCK") || !maxQuery.next()) {
            QMessageBox::critical(nullptr, "Erreur",
                                  "Impossible de générer un ID.\nErreur : " + maxQuery.lastError().text());
            return;
        }
        nextId = maxQuery.value(0).toInt();
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO ZIT.STOCK (ID_STOCK, TYPE_STOCK, QUANTITE, SEUIL_ALERTE, ORIGINE) "
                  "VALUES (:id, :type, :quantite, :seuil, :origine)");
    query.bindValue(":id",       nextId);
    query.bindValue(":type",     typeStock);
    query.bindValue(":quantite", quantite);
    query.bindValue(":seuil",    seuilAlerte);
    query.bindValue(":origine",  origine);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Succès", "✅ Le stock a été ajouté avec succès !");
        loadData(table);
    } else {
        QMessageBox::critical(nullptr, "Erreur d'ajout",
                              "Impossible d'ajouter le stock.\nErreur : " + query.lastError().text());
    }
}

void Stock::updateStock(int id, const QString &typeStock, double quantite,
                        double seuilAlerte, const QString &origine, QTableWidget *table)
{
    if (typeStock == "Sélectionner ...") {
        QMessageBox::warning(nullptr, "Champ manquant", "Veuillez sélectionner un type de stock.");
        return;
    }
    if (origine.isEmpty()) {
        QMessageBox::warning(nullptr, "Champ manquant", "Veuillez saisir l'origine du stock.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE ZIT.STOCK SET TYPE_STOCK=:type, QUANTITE=:quantite, "
                  "SEUIL_ALERTE=:seuil, ORIGINE=:origine WHERE ID_STOCK=:id");
    query.bindValue(":type",     typeStock);
    query.bindValue(":quantite", quantite);
    query.bindValue(":seuil",    seuilAlerte);
    query.bindValue(":origine",  origine);
    query.bindValue(":id",       id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Succès", "✅ Le stock a été modifié avec succès !");
        loadData(table);
    } else {
        QMessageBox::critical(nullptr, "Erreur de modification",
                              "Impossible de modifier le stock.\nErreur : " + query.lastError().text());
    }
}

void Stock::deleteStock(int id, QTableWidget *table)
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        nullptr, "Confirmation de suppression",
        "Êtes-vous sûr de vouloir supprimer ce stock ?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM ZIT.STOCK WHERE ID_STOCK=:id");
        query.bindValue(":id", id);

        if (query.exec()) {
            QMessageBox::information(nullptr, "Succès", "✅ Le stock a été supprimé avec succès !");
            loadData(table);
        } else {
            QMessageBox::critical(nullptr, "Erreur de suppression",
                                  "Impossible de supprimer le stock.\n"
                                  "Vérifiez qu'il n'est pas référencé dans ACHETER ou PRODUCTION.\n"
                                  "Erreur : " + query.lastError().text());
        }
    }
}

void Stock::searchStock(const QString &searchTerm, QTableWidget *table)
{
    if (searchTerm.isEmpty()) {
        loadData(table);
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT ID_STOCK, TYPE_STOCK, QUANTITE, SEUIL_ALERTE, ORIGINE "
                  "FROM ZIT.STOCK "
                  "WHERE TO_CHAR(ID_STOCK) LIKE :t1 "
                  "OR UPPER(TYPE_STOCK) LIKE UPPER(:t2) "
                  "OR UPPER(ORIGINE) LIKE UPPER(:t3) "
                  "ORDER BY ID_STOCK");

    QString pattern = "%" + searchTerm + "%";
    query.bindValue(":t1", pattern);
    query.bindValue(":t2", pattern);
    query.bindValue(":t3", pattern);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur de recherche",
                              "Échec de la recherche :\n" + query.lastError().text());
        return;
    }

    populateTable(query, table);
}
