#include "client_historique.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QSqlError>  // AJOUTEZ CETTE LIGNE


ClientHistorique::ClientHistorique(QObject *parent) : QObject(parent)
{
    m_achatService = new ClientAchat(this);
    qDebug() << "Service Historique initialisé";
}

ClientHistorique::~ClientHistorique()
{
    qDebug() << "Service Historique détruit";
}

void ClientHistorique::afficherHistoriqueAchats(int idClient, QTableWidget *table)
{
    table->setRowCount(0);

    QVector<Achat> achats = m_achatService->getAchatsClient(idClient);

    table->setColumnCount(5);
    QStringList headers = {"Date", "Produit", "Quantité (kg)", "Prix unitaire (DT)", "Total (DT)"};
    table->setHorizontalHeaderLabels(headers);

    int row = 0;
    double totalGlobal = 0;

    for (const Achat &achat : achats) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(achat.dateAchat.toString("dd/MM/yyyy")));
        table->setItem(row, 1, new QTableWidgetItem(achat.produit));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(achat.quantite, 'f', 2)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(achat.prixUnitaire, 'f', 2)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(achat.getTotal(), 'f', 2)));

        for (int col = 0; col < 5; col++) {
            if (table->item(row, col)) {
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
        }

        totalGlobal += achat.getTotal();
        row++;
    }

    // Ligne de total
    if (row > 0) {
        table->insertRow(row);
        QTableWidgetItem *totalItem = new QTableWidgetItem("TOTAL");
        totalItem->setTextAlignment(Qt::AlignCenter);
        QFont boldFont = totalItem->font();
        boldFont.setBold(true);
        totalItem->setFont(boldFont);
        table->setItem(row, 0, totalItem);

        QTableWidgetItem *totalValueItem = new QTableWidgetItem(QString::number(totalGlobal, 'f', 2));
        totalValueItem->setTextAlignment(Qt::AlignCenter);
        totalValueItem->setFont(boldFont);
        table->setItem(row, 4, totalValueItem);
    }

    table->resizeColumnsToContents();
}

void ClientHistorique::afficherResumeAchats(int idClient, QTextEdit *textEdit)
{
    QString resume = getHistoriqueTexte(idClient);
    textEdit->setPlainText(resume);
}

QString ClientHistorique::getHistoriqueTexte(int idClient)
{
    QString texte;

    // Récupérer les infos du client
    QSqlQuery clientQuery;
    clientQuery.prepare("SELECT NOM, PRENOM, TYPE_CLIENT FROM ZIT.CLIENT WHERE ID_CLIENT = :id");
    clientQuery.bindValue(":id", idClient);

    QString nomClient = "Client inconnu";
    QString typeClient = "";

    if (clientQuery.exec() && clientQuery.next()) {
        nomClient = clientQuery.value(0).toString() + " " + clientQuery.value(1).toString();
        typeClient = clientQuery.value(2).toString();
    }

    QVector<Achat> achats = m_achatService->getAchatsClient(idClient);

    texte += "========================================\n";
    texte += "      HISTORIQUE D'ACHAT\n";
    texte += "========================================\n\n";
    texte += "Client : " + nomClient + "\n";
    texte += "Type   : " + typeClient + "\n";
    texte += "ID     : " + QString::number(idClient) + "\n";
    texte += "----------------------------------------\n\n";

    if (achats.isEmpty()) {
        texte += "Aucun achat enregistré pour ce client.\n";
    } else {
        texte += "Liste des achats :\n\n";
        texte += QString("%1 | %2 | %3 | %4 | %5\n")
                     .arg("Date", 12)
                     .arg("Produit", 20)
                     .arg("Quantité", 12)
                     .arg("Prix unit.", 12)
                     .arg("Total", 12);
        texte += QString("%1 | %2 | %3 | %4 | %5\n")
                     .arg("----------", 12)
                     .arg("---------------", 20)
                     .arg("----------", 12)
                     .arg("----------", 12)
                     .arg("----------", 12);

        double totalGlobal = 0;
        for (const Achat &achat : achats) {
            texte += QString("%1 | %2 | %3 | %4 | %5\n")
            .arg(achat.dateAchat.toString("dd/MM/yyyy"), 12)
                .arg(achat.produit.left(18), 20)
                .arg(QString::number(achat.quantite, 'f', 2), 12)
                .arg(QString::number(achat.prixUnitaire, 'f', 2), 12)
                .arg(QString::number(achat.getTotal(), 'f', 2), 12);
            totalGlobal += achat.getTotal();
        }

        texte += "\n----------------------------------------\n";
        texte += QString("TOTAL GÉNÉRAL : %1 DT\n").arg(totalGlobal, 0, 'f', 2);
        texte += QString("NOMBRE D'ACHATS : %1\n").arg(achats.size());

        double moyenne = totalGlobal / achats.size();
        texte += QString("PANIER MOYEN : %1 DT\n").arg(moyenne, 0, 'f', 2);
    }

    texte += "\n========================================\n";
    texte += "Généré le : " + QDate::currentDate().toString("dd/MM/yyyy") + "\n";
    texte += "========================================\n";

    return texte;
}
