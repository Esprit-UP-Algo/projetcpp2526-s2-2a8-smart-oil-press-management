#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QList>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

class Client
{
public:
    // ── Constructeurs ────────────────────────────────────────────────────────
    Client();
    Client(int id,
           const QString &nom,
           const QString &prenom,
           const QString &email,
           const QString &telephone,
           const QString &typeClient,
           const QString &avis       = "",
           const QDate   &dateAchat  = QDate(),
           double         quantiteAchat = 0.0,
           const QString &saison     = "");

    // ── Getters ──────────────────────────────────────────────────────────────
    int     getId()             const { return id; }
    QString getNom()            const { return nom; }
    QString getPrenom()         const { return prenom; }
    QString getEmail()          const { return email; }
    QString getTelephone()      const { return telephone; }
    QString getTypeClient()     const { return typeClient; }
    QString getAvis()           const { return avis; }
    QDate   getDateAchat()      const { return dateAchat; }
    double  getQuantiteAchat()  const { return quantiteAchat; }
    QString getSaison()         const { return saison; }

    // ── Setters ──────────────────────────────────────────────────────────────
    void setId(int v)                    { id = v; }
    void setNom(const QString &v)        { nom = v; }
    void setPrenom(const QString &v)     { prenom = v; }
    void setEmail(const QString &v)      { email = v; }
    void setTelephone(const QString &v)  { telephone = v; }
    void setTypeClient(const QString &v) { typeClient = v; }
    void setAvis(const QString &v)       { avis = v; }
    void setDateAchat(const QDate &v)    { dateAchat = v; updateSaison(); }
    void setQuantiteAchat(double v)      { quantiteAchat = v; }

    // ── CRUD ─────────────────────────────────────────────────────────────────
    bool ajouter();
    bool modifier();
    bool supprimer();
    void afficher(QTableWidget *table);
    QList<Client> afficherTous();

    // ── Utilitaire saison ────────────────────────────────────────────────────
    static QString calculerSaison(const QDate &date);

private:
    int     id;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QString typeClient;
    QString avis;
    QDate   dateAchat;
    double  quantiteAchat;
    QString saison;

    void updateSaison() { saison = calculerSaison(dateAchat); }
};

#endif // CLIENT_H
