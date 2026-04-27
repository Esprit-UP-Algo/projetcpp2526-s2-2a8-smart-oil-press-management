#include "client.h"
#include <QHeaderView>

// ─────────────────────────────────────────────────────────────────────────────
// Utilitaire : calcul de la saison à partir d'une date
// ─────────────────────────────────────────────────────────────────────────────
QString Client::calculerSaison(const QDate &date)
{
    if (!date.isValid())
        return "Non définie";

    int mois  = date.month();
    int annee = date.year();

    if (mois == 12)
        return QString("Hiver %1/%2").arg(QString::number(annee),
                                          QString::number(annee + 1));

    if (mois == 1 || mois == 2)
        return QString("Hiver %1/%2").arg(QString::number(annee - 1),
                                          QString::number(annee));

    return "Hors saison";
}

// ─────────────────────────────────────────────────────────────────────────────
// Constructeurs
// ─────────────────────────────────────────────────────────────────────────────

Client::Client()
    : id(0), nom(""), prenom(""), email(""), telephone(""),
    typeClient(""), avis(""), quantiteAchat(0.0), saison("Non définie")
{}

Client::Client(int id,
               const QString &nom,
               const QString &prenom,
               const QString &email,
               const QString &telephone,
               const QString &typeClient,
               const QString &avis,
               const QDate   &dateAchat,
               double         quantiteAchat,
               const QString &saison)
    : id(id), nom(nom), prenom(prenom), email(email),
    telephone(telephone), typeClient(typeClient), avis(avis),
    dateAchat(dateAchat), quantiteAchat(quantiteAchat),
    saison(saison.isEmpty() ? calculerSaison(dateAchat) : saison)
{}

// ─────────────────────────────────────────────────────────────────────────────
// Ajouter
// ─────────────────────────────────────────────────────────────────────────────
bool Client::ajouter()
{
    // Calculer la saison avant insertion
    saison = calculerSaison(dateAchat);

    QSqlQuery query;
    query.prepare(
        "INSERT INTO ZIT.CLIENT "
        "(NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS, DATE_ACHAT, QUANTITE_ACHAT, SAISON) "
        "VALUES (:nom, :prenom, :email, :telephone, :type_client, :avis, "
        ":date_achat, :quantite_achat, :saison)"
        );

    query.bindValue(":nom",            nom);
    query.bindValue(":prenom",         prenom);
    query.bindValue(":email",          email);
    query.bindValue(":telephone",      telephone);
    query.bindValue(":type_client",    typeClient);
    query.bindValue(":avis",           avis);
    query.bindValue(":date_achat",     dateAchat.isValid() ? dateAchat : QVariant(QMetaType(QMetaType::QDate)));
    query.bindValue(":quantite_achat", quantiteAchat);
    query.bindValue(":saison",         saison);

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
    // Recalculer la saison si la date a changé
    saison = calculerSaison(dateAchat);

    QSqlQuery query;
    query.prepare(
        "UPDATE ZIT.CLIENT SET "
        "NOM            = :nom, "
        "PRENOM         = :prenom, "
        "EMAIL          = :email, "
        "TELEPHONE      = :telephone, "
        "TYPE_CLIENT    = :type_client, "
        "AVIS           = :avis, "
        "DATE_ACHAT     = :date_achat, "
        "QUANTITE_ACHAT = :quantite_achat, "
        "SAISON         = :saison "
        "WHERE ID_CLIENT = :id"
        );

    query.bindValue(":nom",            nom);
    query.bindValue(":prenom",         prenom);
    query.bindValue(":email",          email);
    query.bindValue(":telephone",      telephone);
    query.bindValue(":type_client",    typeClient);
    query.bindValue(":avis",           avis);
    query.bindValue(":date_achat",     dateAchat.isValid() ? dateAchat : QVariant(QMetaType(QMetaType::QDate)));
    query.bindValue(":quantite_achat", quantiteAchat);
    query.bindValue(":saison",         saison);
    query.bindValue(":id",             id);

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
// Afficher dans un tableau (10 colonnes)
// ─────────────────────────────────────────────────────────────────────────────
void Client::afficher(QTableWidget *table)
{
    table->setRowCount(0);
    table->setColumnCount(10);
    table->setHorizontalHeaderLabels({
        "ID", "Nom", "Prénom", "Email", "Téléphone",
        "Type", "Avis", "Date Achat", "Quantité (kg)", "Saison"
    });
    table->horizontalHeader()->setStretchLastSection(true);

    QSqlQuery query;
    query.prepare(
        "SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS, "
        "DATE_ACHAT, QUANTITE_ACHAT, SAISON "
        "FROM ZIT.CLIENT ORDER BY ID_CLIENT"
        );

    if (!query.exec()) {
        qDebug() << "[Client::afficher] ERREUR :" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        // Colonnes 0-6 : données texte directes
        for (int col = 0; col <= 6; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, col, item);
        }

        // Colonne 7 : DATE_ACHAT — formater en dd/MM/yyyy
        QDate d = query.value(7).toDate();
        QString dateStr = d.isValid() ? d.toString("dd/MM/yyyy") : "-";
        QTableWidgetItem *dateItem = new QTableWidgetItem(dateStr);
        dateItem->setTextAlignment(Qt::AlignCenter);
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 7, dateItem);

        // Colonne 8 : QUANTITE_ACHAT
        double qte = query.value(8).toDouble();
        QTableWidgetItem *qteItem = new QTableWidgetItem(
            qte > 0 ? QString::number(qte, 'f', 2) + " kg" : "-"
            );
        qteItem->setTextAlignment(Qt::AlignCenter);
        qteItem->setFlags(qteItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 8, qteItem);

        // Colonne 9 : SAISON
        QString saisonVal = query.value(9).toString();
        if (saisonVal.isEmpty()) saisonVal = calculerSaison(d);
        QTableWidgetItem *saisonItem = new QTableWidgetItem(saisonVal);
        saisonItem->setTextAlignment(Qt::AlignCenter);
        saisonItem->setFlags(saisonItem->flags() & ~Qt::ItemIsEditable);

        // Couleur selon saison
        if (saisonVal.startsWith("Hiver"))
            saisonItem->setForeground(QColor("#1565c0")); // bleu foncé
        else if (saisonVal == "Hors saison")
            saisonItem->setForeground(QColor("#2e7d32")); // vert
        else
            saisonItem->setForeground(QColor("#757575")); // gris

        table->setItem(row, 9, saisonItem);
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

    QSqlQuery query(
        "SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS, "
        "DATE_ACHAT, QUANTITE_ACHAT, SAISON "
        "FROM ZIT.CLIENT ORDER BY ID_CLIENT"
        );

    while (query.next()) {
        Client c(
            query.value(0).toInt(),      // ID_CLIENT
            query.value(1).toString(),   // NOM
            query.value(2).toString(),   // PRENOM
            query.value(3).toString(),   // EMAIL
            query.value(4).toString(),   // TELEPHONE
            query.value(5).toString(),   // TYPE_CLIENT
            query.value(6).toString(),   // AVIS
            query.value(7).toDate(),     // DATE_ACHAT
            query.value(8).toDouble(),   // QUANTITE_ACHAT
            query.value(9).toString()    // SAISON
            );
        liste.append(c);
    }
    return liste;
}
