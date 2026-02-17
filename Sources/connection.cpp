#include "connection.h"
#include <QDebug>
#include <QMessageBox>

// Constructeur privé
Connection::Connection()
{
    qDebug() << "🔧 Constructeur Connection appelé";
}

// Destructeur
Connection::~Connection()
{
    if (db.isOpen()) {
        qDebug() << "🔒 Fermeture de la connexion à la base de données";
        db.close();
    }
}

// Méthode statique pour obtenir l'instance unique (Meyers Singleton)
Connection& Connection::getInstance()
{
    static Connection instance; // Créée une seule fois
    qDebug() << "🎯 getInstance() appelé - Retour de l'instance Singleton";
    return instance;
}

// Méthode pour créer la connexion
bool Connection::createConnection()
{
    qDebug() << "========================================";
    qDebug() << "🚀 TENTATIVE DE CONNEXION À LA BASE DE DONNÉES";
    qDebug() << "========================================";

    bool test = false;

    // Vérifier les drivers disponibles
    qDebug() << "📋 Drivers SQL disponibles:" << QSqlDatabase::drivers();

    // Créer la connexion à la base de données Oracle via ODBC
    db = QSqlDatabase::addDatabase("QODBC");

    // ⚠️ PARAMÈTRES DE CONNEXION
    QString dsn = "Source_Projet2A";
    QString username = "zarrouk";
    QString password = "med123";

    qDebug() << "📊 Configuration de connexion:";
    qDebug() << "   - DSN (Source ODBC):" << dsn;
    qDebug() << "   - Utilisateur:" << username;
    qDebug() << "   - Mot de passe: ********";

    db.setDatabaseName(dsn);
    db.setUserName(username);
    db.setPassword(password);

    // Tentative d'ouverture de la connexion
    qDebug() << "🔌 Tentative d'ouverture de la connexion...";

    if (db.open()) {
        test = true;
        qDebug() << "========================================";
        qDebug() << "✅ CONNEXION RÉUSSIE !";
        qDebug() << "========================================";
        qDebug() << "📍 Base de données:" << db.databaseName();
        qDebug() << "👤 Utilisateur connecté:" << db.userName();
        qDebug() << "🔧 Driver utilisé:" << db.driverName();
    } else {
        test = false;
        qDebug() << "========================================";
        qDebug() << "❌ ÉCHEC DE CONNEXION !";
        qDebug() << "========================================";
        qDebug() << "⚠️ Type d'erreur:" << db.lastError().type();
        qDebug() << "⚠️ Message d'erreur:" << db.lastError().text();
        qDebug() << "⚠️ Code erreur base de données:" << db.lastError().nativeErrorCode();
        qDebug() << "========================================";
        qDebug() << "🔍 VÉRIFICATIONS À FAIRE:";
        qDebug() << "   1. La source ODBC '" << dsn << "' existe-t-elle ?";
        qDebug() << "   2. Le service Oracle est-il démarré ?";
        qDebug() << "   3. Les identifiants sont-ils corrects ?";
        qDebug() << "   4. Le driver ODBC Oracle est-il installé (64 bits) ?";
        qDebug() << "========================================";
    }

    return test;
}

// Méthode pour obtenir la base de données
QSqlDatabase Connection::getDatabase()
{
    return db;
}
