#ifndef MAILING_H
#define MAILING_H

#include <QString>
#include <QList>
#include "partenaire.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Mailing — envoi d'emails aux partenaires via curl (SMTP/STARTTLS)
//
//  Widgets utilisés dans mainwindow.ui (onglet "Mailing") :
//    - mailingPartenaireComboBox  ← QComboBox  (ajouté dans le .ui livré)
//    - subjectLineEdit            ← QLineEdit  (existant)
//    - messageTextEdit            ← QTextEdit  (existant)
//    - sendMailButton             ← QPushButton (existant)
//
//  Utilisation :
//    1. Appeler chargerPartenaires() → remplit la ComboBox
//    2. Appeler envoyerEmail() avec le partenaire, le sujet, le message
// ─────────────────────────────────────────────────────────────────────────────

class Mailing
{
public:
    Mailing();

    // ── Configuration SMTP ────────────────────────────────────────────────────
    // Modifiez SMTP_USER et SMTP_PASSWORD avec vos identifiants.
    // Pour Gmail : activez "Mots de passe d'application" dans les paramètres Google.
    static const QString SMTP_HOST;      // "smtp.gmail.com"
    static const QString SMTP_PORT;      // "587"
    static const QString SMTP_USER;      // "moncompte@gmail.com"  ← à modifier
    static const QString SMTP_PASSWORD;  // mot de passe d'application  ← à modifier
    static const QString EXPEDITEUR_NOM; // "ZitTech Gestion"

    // ── API publique ──────────────────────────────────────────────────────────

    // Retourne tous les partenaires (pour remplir mailingPartenaireComboBox).
    QList<Partenaire> chargerPartenaires();

    // Envoie un email au partenaire donné.
    // Retourne true si succès. En cas d'échec : erreurMessage() donne le détail.
    bool envoyerEmail(const Partenaire &destinataire,
                      const QString    &sujet,
                      const QString    &message);

    // Dernier message d'erreur (vide si succès).
    QString erreurMessage() const { return m_erreur; }

private:
    QString m_erreur;

    // Construit le mail RFC-822, l'écrit dans un fichier temporaire, lance curl.
    bool lancerCurl(const QString &destinataireEmail,
                    const QString &destinataireNom,
                    const QString &sujet,
                    const QString &corps);
};

#endif // MAILING_H
