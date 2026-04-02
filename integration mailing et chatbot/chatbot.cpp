#include "chatbot.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

// ─────────────────────────────────────────────────────────────
// ⚠️ IMPORTANT : NE PAS EXPOSER LA CLÉ EN PROD
// ─────────────────────────────────────────────────────────────
const QString ChatBot::API_KEY = "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"; // 🔴 mets une NOUVELLE clé
const QString ChatBot::API_URL = "https://api.groq.com/openai/v1/chat/completions";
const QString ChatBot::MODEL   = "llama-3.1-8b-instant";

// ─────────────────────────────────────────────────────────────
// Constructeur
// ─────────────────────────────────────────────────────────────
ChatBot::ChatBot(QObject *parent)
    : QObject(parent)
    , m_network(new QNetworkAccessManager(this))
{
    connect(m_network, &QNetworkAccessManager::finished,
            this,      &ChatBot::onReponseHTTP);

    QJsonObject systeme;
    systeme["role"]    = "system";
    systeme["content"] = "Tu es un assistant intelligent intégré dans ZitTech. "
                         "Réponds clairement en français.";
    m_historique.append(systeme);
}

// ─────────────────────────────────────────────────────────────
// envoyerMessage
// ─────────────────────────────────────────────────────────────
void ChatBot::envoyerMessage(const QString &messageUtilisateur)
{
    if (messageUtilisateur.trimmed().isEmpty())
        return;

    QJsonObject msgUser;
    msgUser["role"]    = "user";
    msgUser["content"] = messageUtilisateur;
    m_historique.append(msgUser);

    QJsonObject body;
    body["model"]       = MODEL;
    body["messages"]    = m_historique;
    body["max_tokens"]  = 1024;
    body["temperature"] = 0.7;

    QByteArray donnees = QJsonDocument(body).toJson(QJsonDocument::Compact);

    QNetworkRequest requete{QUrl(API_URL)};

    requete.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requete.setRawHeader("Authorization",
                         QString("Bearer %1").arg(API_KEY).toUtf8());

    m_network->post(requete, donnees);
}

// ─────────────────────────────────────────────────────────────
// onReponseHTTP (VERSION DEBUG PRO 🔥)
// ─────────────────────────────────────────────────────────────
void ChatBot::onReponseHTTP(QNetworkReply *reply)
{
    QByteArray donnees = reply->readAll();
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "==============================";
    qDebug() << "STATUS CODE:" << status;
    qDebug() << "RESPONSE BODY:" << donnees;
    qDebug() << "==============================";

    reply->deleteLater();

    // 🔴 gérer les erreurs AVEC le vrai message serveur
    if (reply->error() != QNetworkReply::NoError) {
        QString err = QString("Erreur (%1): %2\n%3")
        .arg(status)
            .arg(reply->errorString())
            .arg(QString(donnees));
        emit erreurSurvenue(err);
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(donnees);
    if (!doc.isObject()) {
        emit erreurSurvenue("Réponse JSON invalide.");
        return;
    }

    QJsonObject obj = doc.object();

    // 🔴 erreur API (Groq)
    if (obj.contains("error")) {
        QString err = obj["error"].toObject()["message"].toString();
        emit erreurSurvenue("Erreur API : " + err);
        return;
    }

    QJsonArray choices = obj["choices"].toArray();
    if (choices.isEmpty()) {
        emit erreurSurvenue("Réponse vide de l'API.");
        return;
    }

    QString reponse = choices[0].toObject()["message"]
                          .toObject()["content"]
                          .toString()
                          .trimmed();

    QJsonObject msgAssistant;
    msgAssistant["role"]    = "assistant";
    msgAssistant["content"] = reponse;
    m_historique.append(msgAssistant);

    emit reponseRecue(reponse);
}
