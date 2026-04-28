#ifndef CLIENT_HISTORIQUE_H
#define CLIENT_HISTORIQUE_H

#include <QObject>
#include <QTableWidget>
#include <QTextEdit>
#include <QVector>
#include <QString>
#include <QDate>

struct Achat {
    int id = 0;
    int idClient = 0;
    QString produit;
    double quantite = 0.0;
    double prixUnitaire = 0.0;
    QDate dateAchat;

    double getTotal() const { return quantite * prixUnitaire; }
};

class ClientHistorique : public QObject
{
    Q_OBJECT

public:
    explicit ClientHistorique(QObject *parent = nullptr);
    ~ClientHistorique();

    void afficherHistoriqueAchats(int idClient, QTableWidget *table);
    void afficherResumeAchats(int idClient, QTextEdit *textEdit);
    QString getHistoriqueTexte(int idClient);

    static QVector<Achat> chargerAchatsClient(int idClient);

    /// Saison oléicole courte depuis la date (ex. « Hiver 25/26 »).
    static QString saisonDepuisDate(const QDate &date);

    bool insererAchat(int idClient, const QDate &date, const QString &produit,
                      double quantite, double prixUnitaire, QString *erreurMsg = nullptr);

    /// Emplacement du carnet d'achats (tous les clients), lisible dans le Bloc-notes.
    static QString cheminFichierAchatsExternes();

    /// Campagne oléicole type « 2025/2026 » (juillet → juin suivant).
    static QString campagneOleicoleAnnee(const QDate &date);
    static QString campagneOleicoleAnneeSuivante(const QString &campagneCourante);

    /// Tous les achats : fichier carnet + Oracle (si la table existe).
    static QVector<Achat> chargerTousLesAchats();
};

#endif // CLIENT_HISTORIQUE_H
