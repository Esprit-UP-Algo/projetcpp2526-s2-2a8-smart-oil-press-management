#ifndef MAILING_H
#define MAILING_H

#include <QString>
#include <QList>
#include "partenaire.h"

class Mailing
{
public:
    Mailing();

    static const QString SMTP_HOST;
    static const QString SMTP_PORT;
    static const QString SMTP_USER;
    static const QString SMTP_PASSWORD;
    static const QString EXPEDITEUR_NOM;

    // Retourne tous les partenaires
    QList<Partenaire> chargerPartenaires();

    // Envoie un email à UN partenaire
    bool envoyerEmail(const Partenaire &destinataire,
                      const QString    &sujet,
                      const QString    &message);

    // ── NOUVEAU : envoie à PLUSIEURS partenaires ──────────────
    // Retourne le nombre d'emails envoyés avec succès.
    // emailsEchoues contiendra les noms des partenaires en échec.
    int envoyerEmailMultiple(const QList<Partenaire> &destinataires,
                             const QString           &sujet,
                             const QString           &message,
                             QStringList             &emailsEchoues);

    // Envoie un email à l'administrateur
    bool envoyerEmailAdmin(const QString &message,
                           const QString &sujet);

    QString erreurMessage() const { return m_erreur; }

private:
    QString m_erreur;

    bool lancerCurl(const QString &destinataireEmail,
                    const QString &destinataireNom,
                    const QString &sujet,
                    const QString &corps);
};

#endif // MAILING_H
