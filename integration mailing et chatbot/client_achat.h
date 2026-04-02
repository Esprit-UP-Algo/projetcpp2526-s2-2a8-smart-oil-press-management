#ifndef CLIENT_ACHAT_H
#define CLIENT_ACHAT_H

#include <QObject>
#include <QSqlQuery>
#include <QDate>
#include <QVector>
#include <QDebug>

struct Achat {
    int id;
    int idClient;
    QString produit;
    double quantite;
    double prixUnitaire;
    QDate dateAchat;

    double getTotal() const { return quantite * prixUnitaire; }
};

struct Demande {
    int id;
    int idClient;
    QString produit;
    double quantiteDemandee;
    QDate dateDemande;
    bool estRealisee;
};

class ClientAchat : public QObject
{
    Q_OBJECT

public:
    explicit ClientAchat(QObject *parent = nullptr);
    ~ClientAchat();

    // Gestion des achats
    bool ajouterAchat(int idClient, const QString &produit, double quantite, double prixUnitaire, QWidget *parent = nullptr);
    QVector<Achat> getAchatsClient(int idClient);
    double getVolumeTotalAchats(int idClient);
    QVector<Achat> getAchatsParPeriode(int idClient, const QDate &debut, const QDate &fin);

    // Gestion des demandes (pour les prévisions)
    bool ajouterDemande(int idClient, const QString &produit, double quantite);
    QVector<Demande> getDemandesClient(int idClient);
    QVector<Demande> getDemandesNonRealisees();
    void marquerDemandeRealisee(int idDemande);

private:
    QSqlQuery query;
};

#endif // CLIENT_ACHAT_H
