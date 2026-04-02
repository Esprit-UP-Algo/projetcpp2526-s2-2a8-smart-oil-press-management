#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>

// ─────────────────────────────────────────────────────────────────────────────
//  ChatBot — interface avec l'API Groq (compatible OpenAI)
//
//  Utilisation :
//    1. Instancier ChatBot dans MainWindow (membre privé)
//    2. Connecter le signal reponseRecue(QString) à votre slot d'affichage
//    3. Appeler envoyerMessage(texte) quand l'utilisateur envoie un message
//
//  Widgets concernés dans le .ui (onglet ChatBot) :
//    - chatbotDisplayArea    (QTextEdit, readOnly)
//    - chatbotInputLineEdit  (QLineEdit)
//    - chatbotSendButton     (QPushButton)
// ─────────────────────────────────────────────────────────────────────────────

class ChatBot : public QObject
{
    Q_OBJECT

public:
    explicit ChatBot(QObject *parent = nullptr);

    // ── Configuration ─────────────────────────────────────────────────────────
    // Remplacez la valeur par votre clé API Groq
    static const QString API_KEY;
    static const QString API_URL;   // endpoint Groq (format OpenAI)
    static const QString MODEL;     // modèle Groq rapide et gratuit

    // ── API publique ──────────────────────────────────────────────────────────
    // Envoie le message de l'utilisateur à l'API Groq de manière asynchrone.
    // Émet reponseRecue() ou erreurSurvenue() selon le résultat.
    void envoyerMessage(const QString &messageUtilisateur);

signals:
    // Émis quand la réponse de l'IA est disponible
    void reponseRecue(const QString &reponse);

    // Émis en cas d'erreur réseau ou API
    void erreurSurvenue(const QString &erreur);

private slots:
    void onReponseHTTP(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network;
    QJsonArray             m_historique; // conserve le contexte de la conversation
};

#endif // CHATBOT_H
