#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    // Méthode statique pour obtenir l'instance unique (Singleton)
    static Connection& getInstance();

    // Méthode pour créer la connexion
    bool createConnection();

    // Méthode pour obtenir la base de données
    QSqlDatabase getDatabase();

    // Supprimer le constructeur de copie et l'opérateur d'affectation
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

private:
    // Constructeur privé
    Connection();

    // Destructeur privé
    ~Connection();

    // Instance de la base de données
    QSqlDatabase db;
};

#endif // CONNECTION_H
