#ifndef VOICEMATIERES_H
#define VOICEMATIERES_H

#include <QObject>
#include <QString>
#include <QTableWidget>

// Forward declaration
class MainWindow;

class VoiceMatieres : public QObject
{
    Q_OBJECT

public:
    explicit VoiceMatieres(MainWindow *mainWin, QTableWidget *table);
    ~VoiceMatieres();

    // Ouvrir le dialog de commande vocale
    void openVoiceDialog();

private:
    // Traite la commande brute saisie par l'utilisateur
    void processVoiceCommand(const QString &rawCmd);

    // Retourne le texte d'une cellule du tableau
    QString cellText(QTableWidget *table, int row, int col) const;

    // Normalise un texte : minuscules + suppression des accents
    QString normalizeText(const QString &text) const;

    // Recherche une ligne dans le tableau stock (par ID, type ou origine)
    int findStockRow(const QString &needle) const;

    // Pré-remplit le formulaire stock depuis la commande normalisée
    void prefillStockForm(const QString &normalizedCmd) const;

    // Invoque un slot de MainWindow sans argument
    bool invokeMainWindow(const char *slot) const;

    MainWindow   *mainWindow;
    QTableWidget *stockTable;
};

#endif // VOICEMATIERES_H
