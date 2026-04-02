#include "mailing.h"

#include <QProcess>
#include <QTemporaryFile>
#include <QTextStream>
#include <QDebug>

// ─────────────────────────────────────────────────────────────────────────────
//  Configuration SMTP  —  ← MODIFIEZ CES DEUX LIGNES
// ─────────────────────────────────────────────────────────────────────────────
const QString Mailing::SMTP_HOST      = "smtp.gmail.com";
const QString Mailing::SMTP_PORT      = "587";
const QString Mailing::SMTP_USER      = "gattoufimhamed9@gmail.com";   // ← à modifier
const QString Mailing::SMTP_PASSWORD  = "lvsnzevxkpcunpsk";  // ← à modifier
const QString Mailing::EXPEDITEUR_NOM = "ZitTech Gestion";

// ─────────────────────────────────────────────────────────────────────────────
//  Constructeur
// ─────────────────────────────────────────────────────────────────────────────
Mailing::Mailing() {}

// ─────────────────────────────────────────────────────────────────────────────
//  chargerPartenaires — récupère la liste depuis la base de données
// ─────────────────────────────────────────────────────────────────────────────
QList<Partenaire> Mailing::chargerPartenaires()
{
    Partenaire p;
    return p.afficherTous();
}

// ─────────────────────────────────────────────────────────────────────────────
//  envoyerEmail — valide les champs puis délègue à lancerCurl()
// ─────────────────────────────────────────────────────────────────────────────
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

    return lancerCurl(destinataire.getEmail(),
                      destinataire.getNom(),
                      sujet,
                      message);
}

// ─────────────────────────────────────────────────────────────────────────────
//  lancerCurl — construit le mail RFC-822, le stocke dans un fichier
//               temporaire, puis invoque curl en SMTP/STARTTLS (port 587)
// ─────────────────────────────────────────────────────────────────────────────
bool Mailing::lancerCurl(const QString &destinataireEmail,
                         const QString &destinataireNom,
                         const QString &sujet,
                         const QString &corps)
{
    // ── 1. Construire le contenu RFC-822 ─────────────────────────────────────
    QString mailContent;
    QTextStream ts(&mailContent);
    ts << "From: " << EXPEDITEUR_NOM << " <" << SMTP_USER << ">\r\n";
    ts << "To: "   << destinataireNom << " <" << destinataireEmail << ">\r\n";
    ts << "Subject: " << sujet << "\r\n";
    ts << "MIME-Version: 1.0\r\n";
    ts << "Content-Type: text/plain; charset=UTF-8\r\n";
    ts << "\r\n";
    ts << corps << "\r\n";

    // ── 2. Écrire dans un fichier temporaire (curl --upload-file) ─────────────
    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(true);
    if (!tmpFile.open()) {
        m_erreur = "Impossible de créer le fichier temporaire pour le mail.";
        return false;
    }
    tmpFile.write(mailContent.toUtf8());
    tmpFile.flush();

    // ── 3. Arguments curl ────────────────────────────────────────────────────
    QStringList args;
    args << "--url"         << QString("smtp://%1:%2").arg(SMTP_HOST, SMTP_PORT)
         << "--ssl-reqd"
         << "--user"        << QString("%1:%2").arg(SMTP_USER, SMTP_PASSWORD)
         << "--mail-from"   << SMTP_USER
         << "--mail-rcpt"   << destinataireEmail
         << "--upload-file" << tmpFile.fileName()
         << "--silent"
         << "--show-error";

    // ── 4. Exécuter curl (timeout 15 s) ──────────────────────────────────────
    QProcess process;
    process.start("curl", args);

    if (!process.waitForFinished(15000)) {
        m_erreur = "curl n'a pas répondu dans le délai imparti (15 s).";
        process.kill();
        return false;
    }

    // ── 5. Vérifier le code de retour ────────────────────────────────────────
    if (process.exitCode() != 0) {
        QString errStderr = QString::fromUtf8(process.readAllStandardError()).trimmed();
        m_erreur = QString("Échec de l'envoi (code %1) : %2")
                       .arg(process.exitCode())
                       .arg(errStderr.isEmpty() ? "erreur inconnue" : errStderr);
        qDebug() << "[Mailing] ERREUR curl :" << m_erreur;
        return false;
    }

    qDebug() << "[Mailing] Email envoyé à" << destinataireEmail;
    return true;
}
