#include "client_recherche.h"
#include <QSqlQuery>
#include <QDebug>

ClientRecherche::ClientRecherche(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Recherche initialisé";
}

ClientRecherche::~ClientRecherche()
{
    qDebug() << "Service Recherche détruit";
}

void ClientRecherche::rechercherParNom(QTableWidget *table, const QString &nom)
{
    if (nom.isEmpty()) return;

    table->setRowCount(0);
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                  "FROM ZIT.CLIENT WHERE LOWER(NOM) LIKE LOWER(:nom) ORDER BY NOM");
    query.bindValue(":nom", "%" + nom + "%");

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            table->insertRow(row);
            for (int col = 0; col < 7; col++) {
                table->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
            row++;
        }
    }
}

void ClientRecherche::rechercherParTelephone(QTableWidget *table, const QString &telephone)
{
    if (telephone.isEmpty()) return;

    table->setRowCount(0);
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                  "FROM ZIT.CLIENT WHERE TELEPHONE LIKE :tel ORDER BY NOM");
    query.bindValue(":tel", "%" + telephone + "%");

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            table->insertRow(row);
            for (int col = 0; col < 7; col++) {
                table->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
            row++;
        }
    }
}

void ClientRecherche::rechercherParEmail(QTableWidget *table, const QString &email)
{
    if (email.isEmpty()) return;

    table->setRowCount(0);
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                  "FROM ZIT.CLIENT WHERE LOWER(EMAIL) LIKE LOWER(:email) ORDER BY NOM");
    query.bindValue(":email", "%" + email + "%");

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            table->insertRow(row);
            for (int col = 0; col < 7; col++) {
                table->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
            row++;
        }
    }
}

void ClientRecherche::rechercherParType(QTableWidget *table, const QString &type)
{
    if (type.isEmpty()) return;

    table->setRowCount(0);
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, TYPE_CLIENT, AVIS "
                  "FROM ZIT.CLIENT WHERE TYPE_CLIENT = :type ORDER BY NOM");
    query.bindValue(":type", type);

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            table->insertRow(row);
            for (int col = 0; col < 7; col++) {
                table->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
            row++;
        }
    }
}
