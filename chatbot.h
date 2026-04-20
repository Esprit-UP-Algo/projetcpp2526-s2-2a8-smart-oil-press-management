#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QSqlDatabase>

class ChatBot : public QObject
{
    Q_OBJECT

public:
    explicit ChatBot(QObject *parent = nullptr);

    static const QString API_KEY;
    static const QString API_URL;
    static const QString MODEL;

    // ── Nouveau : injecter la BD depuis MainWindow ──────────────
    void setDatabase(const QSqlDatabase &db);

    void envoyerMessage(const QString &messageUtilisateur);

signals:
    void reponseRecue(const QString &reponse);
    void erreurSurvenue(const QString &erreur);

private slots:
    void onReponseHTTP(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network;
    QJsonArray             m_historique;
    QSqlDatabase           m_db;          // référence à la BD

    // ── Méthodes de lecture de la BD ────────────────────────────
    QString lireContexteBD(const QString &message);
    QString lirePartenaires();
    QString lireClients();
    QString lireStocks();
    QString lireEmployes();
    QString lireMachines();
    QString lireProductions();
};

#endif // CHATBOT_H
