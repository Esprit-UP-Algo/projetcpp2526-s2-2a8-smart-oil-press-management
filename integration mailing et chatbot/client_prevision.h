#ifndef CLIENT_PREVISION_H
#define CLIENT_PREVISION_H

#include <QObject>
#include <QTableWidget>
#include <QVector>
#include <QString>
#include <QDate>
#include <QtCharts>

struct PrevisionData {
    int idClient;
    QString nomClient;
    QString produit;
    double quantitePredite;
    double confiance;           // 0.0 à 1.0
    QString niveauConfiance;    // "Faible", "Moyen", "Élevé"
    double tendance;            // pente de régression
    double saisonnalite;        // facteur saisonnier
};

struct DonneeHistorique {
    QDate date;
    double quantite;
    int mois;
    int annee;
};

class ClientPrevision : public QObject
{
    Q_OBJECT

public:
    explicit ClientPrevision(QObject *parent = nullptr);
    ~ClientPrevision();

    // Prévision principale
    double predireDemandeClient(int idClient, const QString &produit);
    QVector<PrevisionData> getPrevisionsTousClients();
    void afficherPrevisions(QTableWidget *table);

    // Graphiques
    QChartView* creerGraphiquePrevisionClient(int idClient, const QString &produit = "");
    QChartView* creerGraphiquePrevisionsGlobal();
    QChartView* creerGraphiqueEvolution12Mois(int idClient, const QString &produit);

    // Export PDF historique
    void exporterHistoriquePDF(int idClient, const QString &cheminFichier);

private:
    class ClientAchat *m_achatService;

    // Récupération données
    QVector<DonneeHistorique> getHistoriqueDetaille(int idClient, const QString &produit);
    QVector<double> getHistoriqueQuantites(int idClient, const QString &produit);

    // Algorithmes de prévision
    double calculerTendanceRegression(const QVector<double> &donnees);
    double calculerMoyenneMobilePondef(const QVector<double> &donnees, int periode = 4);
    double calculerFacteurSaisonnier(int idClient, const QString &produit, int moisCible);
    double calculerConfiance(const QVector<double> &donnees);
    QString niveauConfianceTexte(double confiance);

    // Couleurs dégradé vert
    QColor getCouleurVert(int index, int total);
};

#endif // CLIENT_PREVISION_H
