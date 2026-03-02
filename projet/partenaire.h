#ifndef PARTENAIRE_H
#define PARTENAIRE_H
#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPair>

class Partenaire
{
public:
    // ── Constructeurs ────────────────────────────────────────────────────────
    Partenaire();
    Partenaire(int id,
               const QString &nom,
               const QString &email,
               const QString &investissement,
               const QString &telephone,
               int idEmploye = 0);

    // ── Getters ──────────────────────────────────────────────────────────────
    int     getId()             const { return id; }
    QString getNom()            const { return nom; }
    QString getEmail()          const { return email; }
    QString getInvestissement() const { return investissement; }
    QString getTelephone()      const { return telephone; }
    int     getIdEmploye()      const { return idEmploye; }

    // ── Setters ──────────────────────────────────────────────────────────────
    void setId(int v)                       { id = v; }
    void setNom(const QString &v)           { nom = v; }
    void setEmail(const QString &v)         { email = v; }
    void setInvestissement(const QString &v){ investissement = v; }
    void setTelephone(const QString &v)     { telephone = v; }
    void setIdEmploye(int v)               { idEmploye = v; }

    // ── CRUD ─────────────────────────────────────────────────────────────────
    bool ajouter();
    bool supprimer();

    // ── Affichage ────────────────────────────────────────────────────────────
    QList<Partenaire> afficherTous();

    // ── Employés ─────────────────────────────────────────────────────────────
    // Retourne une liste de paires (ID_EMPLOYE, "NOM PRENOM")
    static QList<QPair<int,QString>> listerEmployes();

private:
    int     id;
    QString nom;
    QString email;
    QString investissement;
    QString telephone;
    int     idEmploye;
};

#endif // PARTENAIRE_H
