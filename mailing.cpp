#include "mailing.h"
#include <QProcess>
#include <QTemporaryFile>
#include <QTextStream>
#include <QDebug>

const QString Mailing::SMTP_HOST      = "smtp.gmail.com";
const QString Mailing::SMTP_PORT      = "587";
const QString Mailing::SMTP_USER      = "gattoufimhamed9@gmail.com";
const QString Mailing::SMTP_PASSWORD  = "lvsnzevxkpcunpsk";
const QString Mailing::EXPEDITEUR_NOM = "ZitTech Gestion";

Mailing::Mailing() {}

QList<Partenaire> Mailing::chargerPartenaires()
{
    Partenaire p;
    return p.afficherTous();
}

// ─────────────────────────────────────────────────────────────
// envoyerEmail — un seul destinataire
// ─────────────────────────────────────────────────────────────
bool Mailing::envoyerEmail(const Partenaire &destinataire,
                           const QString    &sujet,
                           const QString    &message)
{
    m_erreur.clear();
    if (destinataire.getEmail().isEmpty()) {
        m_erreur = "L'adresse email du partenaire est vide.";
        return false;
    }
    if (sujet.trimmed().isEmpty()) {
        m_erreur = "Le sujet du message est vide.";
        return false;
    }
    if (message.trimmed().isEmpty()) {
        m_erreur = "Le contenu du message est vide.";
        return false;
    }
    return lancerCurl(destinataire.getEmail(), destinataire.getNom(), sujet, message);
}

// ─────────────────────────────────────────────────────────────
// envoyerEmailMultiple — plusieurs destinataires (checkboxes)
// ─────────────────────────────────────────────────────────────
int Mailing::envoyerEmailMultiple(const QList<Partenaire> &destinataires,
                                  const QString           &sujet,
                                  const QString           &message,
                                  QStringList             &emailsEchoues)
{
    emailsEchoues.clear();
    int succes = 0;

    for (const Partenaire &p : destinataires) {
        if (lancerCurl(p.getEmail(), p.getNom(), sujet, message))
            ++succes;
        else
            emailsEchoues << p.getNom() + " <" + p.getEmail() + ">";
    }
    return succes;
}

// ─────────────────────────────────────────────────────────────
// lancerCurl
// ─────────────────────────────────────────────────────────────
bool Mailing::lancerCurl(const QString &destinataireEmail,
                         const QString &destinataireNom,
                         const QString &sujet,
                         const QString &corps)
{
    QString mailContent;
    QTextStream ts(&mailContent);
    ts << "From: " << EXPEDITEUR_NOM << " <" << SMTP_USER << ">\r\n";
    ts << "To: "   << destinataireNom << " <" << destinataireEmail << ">\r\n";
    ts << "Subject: " << sujet << "\r\n";
    ts << "MIME-Version: 1.0\r\n";
    ts << "Content-Type: text/plain; charset=UTF-8\r\n";
    ts << "\r\n";
    ts << corps << "\r\n";

    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(true);
    if (!tmpFile.open()) {
        m_erreur = "Impossible de créer le fichier temporaire.";
        return false;
    }
    tmpFile.write(mailContent.toUtf8());
    tmpFile.flush();

    QStringList args;
    args << "--url"         << QString("smtp://%1:%2").arg(SMTP_HOST, SMTP_PORT)
         << "--ssl-reqd"
         << "--user"        << QString("%1:%2").arg(SMTP_USER, SMTP_PASSWORD)
         << "--mail-from"   << SMTP_USER
         << "--mail-rcpt"   << destinataireEmail
         << "--upload-file" << tmpFile.fileName()
         << "--silent"
         << "--show-error";

    QProcess process;
    process.start("curl", args);
    if (!process.waitForFinished(15000)) {
        m_erreur = "curl n'a pas répondu (timeout 15s).";
        process.kill();
        return false;
    }
    if (process.exitCode() != 0) {
        QString err = QString::fromUtf8(process.readAllStandardError()).trimmed();
        m_erreur = QString("Échec (code %1) : %2")
                       .arg(process.exitCode())
                       .arg(err.isEmpty() ? "erreur inconnue" : err);
        qDebug() << "[Mailing] ERREUR:" << m_erreur;
        return false;
    }
    qDebug() << "[Mailing] Email envoyé à" << destinataireEmail;
    return true;
}

// ─────────────────────────────────────────────────────────────
// envoyerEmailAdmin — envoie un email à l'administrateur
// ─────────────────────────────────────────────────────────────
bool Mailing::envoyerEmailAdmin(const QString &message,
                                const QString &sujet)
{
    m_erreur.clear();
    const QString ADMIN_EMAIL = "mehdibenamira2005@gmail.com";
    const QString ADMIN_NOM   = "Admin ZitTech";

    if (sujet.trimmed().isEmpty()) {
        m_erreur = "Le sujet du message est vide.";
        return false;
    }
    if (message.trimmed().isEmpty()) {
        m_erreur = "Le contenu du message est vide.";
        return false;
    }

    return lancerCurl(ADMIN_EMAIL, ADMIN_NOM, sujet, message);
}
