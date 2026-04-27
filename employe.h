#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:
    int id_employe;
    QString nom;
    QString prenom;
    QString poste;
    int salaire;
    QDate date_embauche;

public:
    // Constructeurs
    Employe();
    Employe(int id, QString nom, QString prenom, QString poste, int salaire, QDate date_embauche);

    // Getters
    int getId() const { return id_employe; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getPoste() const { return poste; }
    int getSalaire() const { return salaire; }
    QDate getDateEmbauche() const { return date_embauche; }


    // Setters
    void setId(int id) { this->id_employe = id; }
    void setNom(QString n) { this->nom = n; }
    void setPrenom(QString p) { this->prenom = p; }
    void setPoste(QString po) { this->poste = po; }
    void setSalaire(int s) { this->salaire = s; }
    void setDateEmbauche(QDate d) { this->date_embauche = d; }

    // Méthodes CRUD
    bool ajouter();
    bool ajouterAvecMdp(const QString &mdp);
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    int  getLastInsertedId();

    // Génération ID
    int  genererIdAleatoire();

    // Méthodes Statistiques
    int getTotalEmployes();
    int getNombreParPoste(const QString &poste);
};

#endif // EMPLOYE_H
