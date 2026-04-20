#ifndef CLIENT_PREVISION_H
#define CLIENT_PREVISION_H

#include <QObject>

class QWidget;
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
    /// Somme des prévisions par client (tous produits confondus).
    QVector<PrevisionData> getPrevisionsAgregeesParClient();
    void afficherPrevisions(QTableWidget *table);

    // Graphiques
    QChartView* creerGraphiquePrevisionClient(int idClient, const QString &produit = "");
    QChartView* creerGraphiquePrevisionsGlobal();
    /// Barres groupées : volume réalisé campagne en cours vs prévision campagne suivante (fichier + Oracle).
    QChartView* creerGraphiqueDeuxCampagnes();
    QChartView* creerGraphiqueEvolution12Mois(int idClient, const QString &produit);

    /// Prévision sur une série de quantités (sans requête SQL).
    double predireQuantiteDepuisSerie(const QVector<double> &historiqueQuantites) const;

    // Export PDF historique
    void exporterHistoriquePDF(int idClient, const QString &cheminFichier, QWidget *parentWidget = nullptr);

private:
    // Récupération données
    QVector<DonneeHistorique> getHistoriqueDetaille(int idClient, const QString &produit);
    QVector<double> getHistoriqueQuantites(int idClient, const QString &produit);

    // Algorithmes de prévision (const : pas d’état mutable sur l’objet)
    double calculerTendanceRegression(const QVector<double> &donnees) const;
    double calculerMoyenneMobilePondef(const QVector<double> &donnees, int periode = 4) const;
    double calculerFacteurSaisonnier(int idClient, const QString &produit, int moisCible);
    double calculerConfiance(const QVector<double> &donnees);
    QString niveauConfianceTexte(double confiance);

    // Couleurs dégradé vert
    QColor getCouleurVert(int index, int total);
};

#endif // CLIENT_PREVISION_H
