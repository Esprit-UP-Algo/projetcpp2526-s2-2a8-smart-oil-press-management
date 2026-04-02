#include "client.h"

// ─────────────────────────────────────────────────────────────────────────────
// Constructeurs
// ─────────────────────────────────────────────────────────────────────────────

Client::Client()
    : id(0), nom(""), prenom(""), email(""), telephone(""), typeClient(""), avis("")
{
}

Client::Client(int id,
               const QString &nom,
               const QString &prenom,
               const QString &email,
               const QString &telephone,
               const QString &typeClient,
               const QString &avis)
    : id(id), nom(nom), prenom(prenom), email(email),
    telephone(telephone), typeClient(typeClient), avis(avis)
{
}

// ─────────────────────────────────────────────────────────────────────────────
// Ajouter
// ─────────────────────────────────────────────────────────────────────────────
bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ZIT.CLIENT (NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS) "
                  "VALUES (:nom, :prenom, :email, :telephone, :type_client, :avis)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":type_client", typeClient);
    query.bindValue(":avis", avis);

    if (!query.exec()) {
        qDebug() << "[Client::ajouter] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Modifier
// ─────────────────────────────────────────────────────────────────────────────
bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ZIT.CLIENT SET "
                  "NOM = :nom, "
                  "PRENOM = :prenom, "
                  "EMAIL = :email, "
                  "TELEPHONE = :telephone, "
                  "TYPE_CLIENT = :type_client, "
                  "AVIS = :avis "
                  "WHERE ID_CLIENT = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":type_client", typeClient);
    query.bindValue(":avis", avis);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "[Client::modifier] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Supprimer
// ─────────────────────────────────────────────────────────────────────────────
bool Client::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM ZIT.CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "[Client::supprimer] ERREUR :" << query.lastError().text();
        return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Afficher dans un tableau
// ─────────────────────────────────────────────────────────────────────────────
void Client::afficher(QTableWidget *table)
{
    table->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                  "FROM ZIT.CLIENT ORDER BY ID_CLIENT");

    if (!query.exec()) {
        qDebug() << "[Client::afficher] ERREUR :" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        for (int col = 0; col < 7; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }
        row++;
    }

    table->resizeColumnsToContents();
    qDebug() << "Clients chargés. Lignes :" << row;
}

// ─────────────────────────────────────────────────────────────────────────────
// Afficher tous (retourne une liste)
// ─────────────────────────────────────────────────────────────────────────────
QList<Client> Client::afficherTous()
{
    QList<Client> liste;

    QSqlQuery query("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                    "FROM ZIT.CLIENT ORDER BY ID_CLIENT");

    while (query.next()) {
        Client c(
            query.value(0).toInt(),    // ID_CLIENT
            query.value(1).toString(), // NOM
            query.value(2).toString(), // PRENOM
            query.value(3).toString(), // EMAIL
            query.value(4).toString(), // TELEPHONE
            query.value(5).toString(), // TYPE_CLIENT
            query.value(6).toString()  // AVIS
            );
        liste.append(c);
    }
    return liste;
}
