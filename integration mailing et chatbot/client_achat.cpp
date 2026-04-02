#include "client_achat.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

ClientAchat::ClientAchat(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Achats/Demandes initialisé";
}

ClientAchat::~ClientAchat()
{
    qDebug() << "Service Achats/Demandes détruit";
}

bool ClientAchat::ajouterAchat(int idClient, const QString &produit,
                               double quantite, double prixUnitaire,
                               QWidget *parent)
{
    if (quantite <= 0) {
        if (parent) QMessageBox::warning(parent, "Erreur", "La quantité doit être positive");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ZIT.ACHATS (ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT) "
                  "VALUES (:id_client, :produit, :quantite, :prix_unitaire, :date_achat)");

    query.bindValue(":id_client",     idClient);
    query.bindValue(":produit",       produit);
    query.bindValue(":quantite",      quantite);
    query.bindValue(":prix_unitaire", prixUnitaire);
    query.bindValue(":date_achat",    QDate::currentDate());

    if (query.exec()) {
        qDebug() << "Achat ajouté pour client ID:" << idClient;
        return true;
    } else {
        qDebug() << "ERREUR ajout achat:" << query.lastError().text();
        if (parent)
            QMessageBox::critical(parent, "Erreur SQL",
                                  "Impossible d'ajouter l'achat :\n" + query.lastError().text());
        return false;
    }
}

QVector<Achat> ClientAchat::getAchatsClient(int idClient)
{
    QVector<Achat> achats;

    QSqlQuery query;
    query.prepare("SELECT ID, ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT "
                  "FROM ZIT.ACHATS WHERE ID_CLIENT = :id ORDER BY DATE_ACHAT DESC");
    query.bindValue(":id", idClient);

    if (query.exec()) {
        while (query.next()) {
            Achat achat;
            achat.id           = query.value(0).toInt();
            achat.idClient     = query.value(1).toInt();
            achat.produit      = query.value(2).toString();
            achat.quantite     = query.value(3).toDouble();
            achat.prixUnitaire = query.value(4).toDouble();
            achat.dateAchat    = query.value(5).toDate();
            achats.append(achat);
        }
        qDebug() << "getAchatsClient(" << idClient << ") =>" << achats.size() << "lignes";
    } else {
        qDebug() << "ERREUR getAchatsClient:" << query.lastError().text();
    }

    return achats;
}

double ClientAchat::getVolumeTotalAchats(int idClient)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(QUANTITE) FROM ZIT.ACHATS WHERE ID_CLIENT = :id");
    query.bindValue(":id", idClient);

    if (query.exec() && query.next())
        return query.value(0).toDouble();

    qDebug() << "ERREUR getVolumeTotalAchats:" << query.lastError().text();
    return 0.0;
}

QVector<Achat> ClientAchat::getAchatsParPeriode(int idClient,
                                                const QDate &debut,
                                                const QDate &fin)
{
    QVector<Achat> achats;

    QSqlQuery query;
    query.prepare("SELECT ID, ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT "
                  "FROM ZIT.ACHATS "
                  "WHERE ID_CLIENT = :id AND DATE_ACHAT BETWEEN :debut AND :fin "
                  "ORDER BY DATE_ACHAT");
    query.bindValue(":id",    idClient);
    query.bindValue(":debut", debut);
    query.bindValue(":fin",   fin);

    if (query.exec()) {
        while (query.next()) {
            Achat achat;
            achat.id           = query.value(0).toInt();
            achat.idClient     = query.value(1).toInt();
            achat.produit      = query.value(2).toString();
            achat.quantite     = query.value(3).toDouble();
            achat.prixUnitaire = query.value(4).toDouble();
            achat.dateAchat    = query.value(5).toDate();
            achats.append(achat);
        }
    } else {
        qDebug() << "ERREUR getAchatsParPeriode:" << query.lastError().text();
    }

    return achats;
}

bool ClientAchat::ajouterDemande(int idClient, const QString &produit, double quantite)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ZIT.DEMANDES (ID_CLIENT, PRODUIT, QUANTITE_DEMANDEE, DATE_DEMANDE, REALISEE) "
                  "VALUES (:id_client, :produit, :quantite, :date_demande, 0)");

    query.bindValue(":id_client",    idClient);
    query.bindValue(":produit",      produit);
    query.bindValue(":quantite",     quantite);
    query.bindValue(":date_demande", QDate::currentDate());

    if (query.exec()) {
        qDebug() << "Demande ajoutée pour client ID:" << idClient;
        return true;
    }
    qDebug() << "ERREUR ajouterDemande:" << query.lastError().text();
    return false;
}

QVector<Demande> ClientAchat::getDemandesClient(int idClient)
{
    QVector<Demande> demandes;

    QSqlQuery query;
    query.prepare("SELECT ID, ID_CLIENT, PRODUIT, QUANTITE_DEMANDEE, DATE_DEMANDE, REALISEE "
                  "FROM ZIT.DEMANDES WHERE ID_CLIENT = :id ORDER BY DATE_DEMANDE DESC");
    query.bindValue(":id", idClient);

    if (query.exec()) {
        while (query.next()) {
            Demande demande;
            demande.id               = query.value(0).toInt();
            demande.idClient         = query.value(1).toInt();
            demande.produit          = query.value(2).toString();
            demande.quantiteDemandee = query.value(3).toDouble();
            demande.dateDemande      = query.value(4).toDate();
            demande.estRealisee      = query.value(5).toBool();
            demandes.append(demande);
        }
    } else {
        qDebug() << "ERREUR getDemandesClient:" << query.lastError().text();
    }

    return demandes;
}

QVector<Demande> ClientAchat::getDemandesNonRealisees()
{
    QVector<Demande> demandes;

    QSqlQuery query;
    if (!query.exec("SELECT ID, ID_CLIENT, PRODUIT, QUANTITE_DEMANDEE, DATE_DEMANDE, REALISEE "
                    "FROM ZIT.DEMANDES WHERE REALISEE = 0 ORDER BY DATE_DEMANDE")) {
        qDebug() << "ERREUR getDemandesNonRealisees:" << query.lastError().text();
        return demandes;
    }

    while (query.next()) {
        Demande demande;
        demande.id               = query.value(0).toInt();
        demande.idClient         = query.value(1).toInt();
        demande.produit          = query.value(2).toString();
        demande.quantiteDemandee = query.value(3).toDouble();
        demande.dateDemande      = query.value(4).toDate();
        demande.estRealisee      = query.value(5).toBool();
        demandes.append(demande);
    }

    return demandes;
}

void ClientAchat::marquerDemandeRealisee(int idDemande)
{
    QSqlQuery query;
    query.prepare("UPDATE ZIT.DEMANDES SET REALISEE = 1 WHERE ID = :id");
    query.bindValue(":id", idDemande);
    if (!query.exec())
        qDebug() << "ERREUR marquerDemandeRealisee:" << query.lastError().text();
}
