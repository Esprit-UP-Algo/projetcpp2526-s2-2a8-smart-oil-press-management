#include "voicematieres.h"
#include "mainwindow.h"

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMetaObject>
#include <QPushButton>
#include <QRegularExpression>
#include <QStatusBar>
#include <QTabWidget>
#include <QTimer>
#include <QVBoxLayout>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

// =============================================================================
//  Helpers locaux (anonymes)
// =============================================================================
namespace {

/**
 * @brief Sélectionne une valeur dans un QComboBox.
 *        Essai 1 : correspondance exacte (insensible à la casse)
 *        Essai 2 : correspondance partielle
 * @return true si une valeur a pu être sélectionnée
 */
bool setComboValue(QComboBox *combo, const QString &value)
{
    if (!combo || value.trimmed().isEmpty())
        return false;

    const QString wanted = value.trimmed().toLower();

    // Correspondance exacte
    for (int i = 0; i < combo->count(); ++i) {
        if (combo->itemText(i).trimmed().toLower() == wanted) {
            combo->setCurrentIndex(i);
            return true;
        }
    }
    // Correspondance partielle
    for (int i = 0; i < combo->count(); ++i) {
        if (combo->itemText(i).trimmed().toLower().contains(wanted)) {
            combo->setCurrentIndex(i);
            return true;
        }
    }
    return false;
}

/**
 * @brief Convertit une chaîne "12,5" ou "12.5" en double.
 */
double toDoubleValue(QString value)
{
    value.replace(",", ".");
    return value.toDouble();
}

} // namespace anonyme


// =============================================================================
//  Constructeur / Destructeur
// =============================================================================
VoiceMatieres::VoiceMatieres(MainWindow *mainWin, QTableWidget *table)
    : QObject(mainWin)
    , mainWindow(mainWin)
    , stockTable(table)
{
}

VoiceMatieres::~VoiceMatieres()
{
}


// =============================================================================
//  Utilitaires privés
// =============================================================================

/**
 * @brief Retourne le texte d'une cellule (vide si null).
 */
QString VoiceMatieres::cellText(QTableWidget *table, int row, int col) const
{
    QTableWidgetItem *item = table ? table->item(row, col) : nullptr;
    return item ? item->text() : "";
}

/**
 * @brief Met en minuscules, supprime les accents et simplifie les espaces.
 *
 *  Caractères traités : à â ä é è ê ë î ï ô ö ù û ü ç œ
 *  Guillemets / apostrophes remplacés par un espace.
 */
QString VoiceMatieres::normalizeText(const QString &text) const
{
    QString out = text.toLower().trimmed();

    out.replace("à", "a"); out.replace("â", "a"); out.replace("ä", "a");
    out.replace("é", "e"); out.replace("è", "e");
    out.replace("ê", "e"); out.replace("ë", "e");
    out.replace("î", "i"); out.replace("ï", "i");
    out.replace("ô", "o"); out.replace("ö", "o");
    out.replace("ù", "u"); out.replace("û", "u"); out.replace("ü", "u");
    out.replace("ç", "c");
    out.replace("œ", "oe");
    out.replace(QRegularExpression("[\"'`]+"), " ");
    out = out.simplified();

    return out;
}

/**
 * @brief Invoque un slot de MainWindow sans argument, en connexion directe.
 * @return true si l'invocation a réussi
 */
bool VoiceMatieres::invokeMainWindow(const char *slot) const
{
    return mainWindow
           && QMetaObject::invokeMethod(mainWindow, slot, Qt::DirectConnection);
}


// =============================================================================
//  findStockRow — Recherche d'une ligne dans le tableau stock
// =============================================================================
/**
 * Colonnes du tableau stock (stockTable / "stockTable") :
 *   0 = ID_STOCK      (numérique)
 *   1 = TYPE_STOCK    (texte)
 *   2 = QUANTITE      (numérique)
 *   3 = SEUIL_ALERTE  (numérique)
 *   4 = ORIGINE       (texte)
 *
 * La recherche accepte :
 *   - un ID numérique exact         → colonne 0
 *   - un mot contenu dans le type   → colonne 1
 *   - un mot contenu dans l'origine → colonne 4
 */
int VoiceMatieres::findStockRow(const QString &needle) const
{
    // Résolution du tableau (priorité à l'instance membre)
    QTableWidget *table = stockTable;
    if (!table && mainWindow)
        table = mainWindow->findChild<QTableWidget *>("stockTable");
    if (!table)
        return -1;

    const QString wanted = normalizeText(needle);
    if (wanted.isEmpty())
        return -1;

    bool      isNumeric = false;
    const int numVal    = wanted.toInt(&isNumeric);
    const QString numTxt = QString::number(numVal);

    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r))
            continue;

        const QString id      = normalizeText(cellText(table, r, 0));
        const QString type    = normalizeText(cellText(table, r, 1));
        const QString origine = normalizeText(cellText(table, r, 4));

        // Correspondance numérique sur l'ID
        if (isNumeric && id == numTxt)
            return r;

        // Correspondance textuelle sur le type ou l'origine
        if (type.contains(wanted) || origine.contains(wanted))
            return r;
    }

    return -1;
}


// =============================================================================
//  prefillStockForm — Pré-remplissage du formulaire stock
// =============================================================================
/**
 * Widgets ciblés dans MainWindow (objectName défini dans le .ui) :
 *   inputTypeStock      → QComboBox
 *   inputQuantiteStock  → QDoubleSpinBox
 *   inputSeuilStock     → QDoubleSpinBox
 *   inputOrigineStock   → QLineEdit
 *
 * Exemples de phrases reconnues (après normalisation) :
 *   "type produit fini"          → inputTypeStock
 *   "type matiere premiere"      → inputTypeStock
 *   "quantite 50"                → inputQuantiteStock  (= 50.0)
 *   "quantite 50.5 kg"           → inputQuantiteStock  (= 50.5)
 *   "seuil 10"                   → inputSeuilStock     (= 10.0)
 *   "seuil alerte 10 kg"         → inputSeuilStock     (= 10.0)
 *   "origine Mahdia"             → inputOrigineStock
 *   "de sfax"                    → inputOrigineStock
 */
void VoiceMatieres::prefillStockForm(const QString &normalizedCmd) const
{
    if (!mainWindow) return;

    QComboBox      *typeCombo    = mainWindow->findChild<QComboBox *>     ("inputTypeStock");
    QDoubleSpinBox *quantiteSpin = mainWindow->findChild<QDoubleSpinBox *>("inputQuantiteStock");
    QDoubleSpinBox *seuilSpin    = mainWindow->findChild<QDoubleSpinBox *>("inputSeuilStock");
    QLineEdit      *origineEdit  = mainWindow->findChild<QLineEdit *>     ("inputOrigineStock");

    // ── 1. Type de stock ──────────────────────────────────────────────────────
    // Patterns acceptés :
    //   "type <valeur>"
    //   "type de stock <valeur>"
    //   "stock de <valeur>"
    const QList<QRegularExpression> typePatterns = {
        QRegularExpression(
            "(?:type\\s*(?:de\\s*)?stock|type\\s*de|type)\\s+([a-z][a-z0-9\\s\\-]{1,50})"),
        QRegularExpression(
            "stock\\s+de\\s+([a-z][a-z0-9\\s\\-]{1,50})")
    };
    for (const QRegularExpression &pat : typePatterns) {
        const auto m = pat.match(normalizedCmd);
        if (m.hasMatch()) {
            QString typeVal = m.captured(1).trimmed();
            // Retirer les mots-clés qui viendraient coller après la valeur
            typeVal.remove(QRegularExpression(
                "\\s*(quantite|quantité|qte|seuil|alerte|origine|de|kg).*$"));
            typeVal = typeVal.trimmed();
            if (!typeVal.isEmpty() && typeCombo)
                setComboValue(typeCombo, typeVal);
            break;
        }
    }

    // ── 2. Quantité ───────────────────────────────────────────────────────────
    // Patterns : "quantite 50", "qte 50", "quantite 50.5 kg"
    {
        const auto m = QRegularExpression(
                           "(?:quantite|quantité|qte)\\s+(\\d+[.,]?\\d*)\\s*(?:kg)?")
                           .match(normalizedCmd);
        if (m.hasMatch() && quantiteSpin)
            quantiteSpin->setValue(toDoubleValue(m.captured(1)));
    }

    // ── 3. Seuil d'alerte ─────────────────────────────────────────────────────
    // Patterns : "seuil 10", "seuil alerte 10", "alerte 10", "seuil 10 kg"
    {
        const auto m = QRegularExpression(
                           "(?:seuil\\s*(?:alerte|alert)?|alerte)\\s+(\\d+[.,]?\\d*)\\s*(?:kg)?")
                           .match(normalizedCmd);
        if (m.hasMatch() && seuilSpin)
            seuilSpin->setValue(toDoubleValue(m.captured(1)));
    }

    // ── 4. Origine ────────────────────────────────────────────────────────────
    // Patterns : "origine Mahdia", "de Sfax"
    {
        const auto m = QRegularExpression(
                           "(?:origine|de)\\s+([a-z][a-z0-9\\s\\-]{1,50})")
                           .match(normalizedCmd);
        if (m.hasMatch() && origineEdit) {
            QString orig = m.captured(1).trimmed();
            // Retirer les mots-clés parasites
            orig.remove(QRegularExpression(
                "\\s*(quantite|quantité|qte|seuil|alerte|type|kg).*$"));
            orig = orig.trimmed();
            if (!orig.isEmpty())
                origineEdit->setText(orig);
        }
    }
}


// =============================================================================
//  openVoiceDialog — Dialog de saisie / dictée vocale
// =============================================================================
void VoiceMatieres::openVoiceDialog()
{
    QDialog dlg(mainWindow);
    dlg.setWindowTitle("Commande vocale — Gestion des Stocks");
    dlg.setFixedSize(560, 165);
    dlg.setStyleSheet("QDialog { background: #f8f9fa; }");

    QVBoxLayout lay(&dlg);
    lay.setContentsMargins(20, 18, 20, 14);
    lay.setSpacing(10);

    QLabel *lbl = new QLabel("🎙  Entrez ou dictez votre commande :");
    lbl->setStyleSheet("font-size:13px; font-weight:bold; color:#2d4a1f;");
    lay.addWidget(lbl);

    QLineEdit *input = new QLineEdit;
    input->setPlaceholderText(
        "ex : \"ajouter stock type produit fini quantite 50 seuil 10 origine Mahdia\"");
    input->setStyleSheet(
        "padding:8px; border:2px solid #5d732c; border-radius:6px;"
        "font-size:13px; background:white;");
    lay.addWidget(input);

    QHBoxLayout btnLay;
    QPushButton *btnOk     = new QPushButton("✅  Valider");
    QPushButton *btnCancel = new QPushButton("Annuler");
    btnOk->setStyleSheet(
        "background:#ffd700; color:#2d4a1f; border:none;"
        "padding:9px 24px; border-radius:6px; font-weight:bold; font-size:13px;");
    btnCancel->setStyleSheet(
        "background:#6c757d; color:white; border:none;"
        "padding:9px 24px; border-radius:6px; font-weight:bold; font-size:13px;");
    btnLay.addStretch();
    btnLay.addWidget(btnOk);
    btnLay.addWidget(btnCancel);
    lay.addLayout(&btnLay);

    connect(btnOk,     &QPushButton::clicked,    &dlg, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked,    &dlg, &QDialog::reject);
    connect(input,     &QLineEdit::returnPressed, &dlg, &QDialog::accept);

    input->setFocus();

    // Sur Windows : déclenche la dictée vocale système (Win + H)
    QTimer::singleShot(300, [&]() {
#ifdef Q_OS_WIN
        INPUT inputs[4] = {};
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LWIN;
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = 'H';
        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = 'H';
        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = VK_LWIN;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(4, inputs, sizeof(INPUT));
#endif
    });

    if (dlg.exec() == QDialog::Accepted) {
        const QString cmd = input->text().trimmed();
        if (!cmd.isEmpty())
            processVoiceCommand(cmd);
    }
}


// =============================================================================
//  processVoiceCommand — Dispatch des commandes
// =============================================================================
void VoiceMatieres::processVoiceCommand(const QString &rawCmd)
{
    if (!mainWindow) return;

    // Normalisation + suppression de la ponctuation finale
    QString cmd = normalizeText(rawCmd);
    cmd.remove(QRegularExpression("[.!?,;]$"));

    // Naviguer vers la page Stock
    invokeMainWindow("on_btnStock_clicked");

    // Texte affiché dans la barre de statut à la fin
    const QString feedback = "Commande vocale stock : \"" + rawCmd.trimmed() + "\"";

    // ── Résolution du tableau stock ───────────────────────────────────────────
    auto resolveStockTable = [this]() -> QTableWidget * {
        if (stockTable) return stockTable;
        return mainWindow
                   ? mainWindow->findChild<QTableWidget *>("stockTable")
                   : nullptr;
    };

    // ── Extraction de la cible (ID, type ou origine) ──────────────────────────
    // Utilisé par MODIFIER et SUPPRIMER pour localiser la ligne à sélectionner.
    auto extractTarget = [&cmd]() -> QString {
        // ID numérique : "id 5", "stock 5", "id stock 5"
        auto m = QRegularExpression(
                     "(?:id\\s*(?:stock)?|stock)\\s*#?\\s*(\\d+)").match(cmd);
        if (m.hasMatch()) return m.captured(1);

        // Origine : "origine sfax"
        m = QRegularExpression(
                "origine\\s+([a-z][a-z0-9\\s\\-]{1,50})").match(cmd);
        if (m.hasMatch()) return m.captured(1).trimmed();

        // Type : "type huile"
        m = QRegularExpression(
                "type\\s+([a-z][a-z0-9\\s\\-]{1,50})").match(cmd);
        if (m.hasMatch()) return m.captured(1).trimmed();

        return QString();
    };

    // =========================================================================
    //  AJOUTER un stock
    //  Mots-clés : ajouter, ajoutez, ajoute, ajout, creer, cree,
    //              nouveau, nouvelle, inserer
    // =========================================================================
    if (cmd.contains("ajouter")  || cmd.contains("ajoutez") || cmd.contains("ajoute")
        || cmd.contains("ajout") || cmd.contains("creer")   || cmd.contains("cree")
        || cmd.contains("nouveau") || cmd.contains("nouvelle")
        || cmd.contains("inserer"))
    {
        // 1. Vider le formulaire
        invokeMainWindow("on_btnClearStock_clicked");
        // 2. Pré-remplir les champs reconnus
        prefillStockForm(cmd);
        // 3. Soumettre l'ajout
        invokeMainWindow("on_btnAddStock_clicked");
    }

    // =========================================================================
    //  MODIFIER un stock
    //  Mots-clés : modifier, modifiez, modifie, changer, changez,
    //              editer, mettre a jour
    // =========================================================================
    else if (cmd.contains("modifier") || cmd.contains("modifiez") || cmd.contains("modifie")
             || cmd.contains("changer")  || cmd.contains("changez")
             || cmd.contains("editer")   || cmd.contains("mettre a jour"))
    {
        // Localiser la ligne cible dans le tableau
        const QString cible = extractTarget();
        if (!cible.isEmpty()) {
            const int row = findStockRow(cible);
            QTableWidget *table = resolveStockTable();
            if (row >= 0 && table) {
                table->setCurrentCell(row, 0);
                table->selectRow(row);
                // Simuler un clic pour peupler le formulaire avec les valeurs actuelles
                QMetaObject::invokeMethod(
                    mainWindow,
                    "on_stockTable_itemClicked",
                    Qt::DirectConnection,
                    Q_ARG(QTableWidgetItem *, table->item(row, 0)));
            }
        }
        // Écraser avec les nouvelles valeurs contenues dans la commande
        prefillStockForm(cmd);
        invokeMainWindow("on_btnUpdateStock_clicked");
    }

    // =========================================================================
    //  SUPPRIMER un stock
    //  Mots-clés : supprimer, supprimez, supprime, effacer, enlever, retirer
    // =========================================================================
    else if (cmd.contains("supprimer") || cmd.contains("supprimez") || cmd.contains("supprime")
             || cmd.contains("effacer") || cmd.contains("enlever")  || cmd.contains("retirer"))
    {
        const QString cible = extractTarget();
        if (!cible.isEmpty()) {
            const int row = findStockRow(cible);
            QTableWidget *table = resolveStockTable();
            if (row >= 0 && table) {
                table->setCurrentCell(row, 0);
                table->selectRow(row);
                QMetaObject::invokeMethod(
                    mainWindow,
                    "on_stockTable_itemClicked",
                    Qt::DirectConnection,
                    Q_ARG(QTableWidgetItem *, table->item(row, 0)));
            }
        }
        invokeMainWindow("on_btnDeleteStock_clicked");
    }

    // =========================================================================
    //  RECHERCHER / FILTRER
    //  Mots-clés : rechercher, recherche, chercher, trouver, filtrer, afficher
    //  "rechercher tout" ou "reset" → rafraîchit la liste complète
    // =========================================================================
    else if (cmd.contains("rechercher") || cmd.contains("recherche") || cmd.contains("chercher")
             || cmd.contains("trouver")  || cmd.contains("filtrer")  || cmd.contains("afficher"))
    {
        // Retirer les mots-clés de navigation pour isoler le terme de recherche
        QString term = cmd;
        for (const QString &kw : QStringList{
                                             "rechercher", "recherche", "chercher", "trouver",
                                             "filtrer", "afficher", "stock", "stocks",
                                             "la", "les", "le", "des", "un", "une"}) {
            term.remove(kw);
        }
        term = term.trimmed();

        if (term.isEmpty()
            || term == "tout" || term == "tous" || term == "toutes"
            || term.contains("reset") || term.contains("reinitialiser"))
        {
            // Remettre la liste complète
            invokeMainWindow("on_btnRefreshStock_clicked");
        } else {
            // Injecter le terme dans la barre de recherche puis lancer
            if (QLineEdit *searchEdit =
                mainWindow->findChild<QLineEdit *>("searchBoxStock"))
                searchEdit->setText(term);
            invokeMainWindow("on_btnSearchStock_clicked");
        }
    }

    // =========================================================================
    //  STATISTIQUES
    //  Mots-clés : statistique, statistiques, stats
    //  → Active l'onglet statistiques (index 1 du tabWidgetStock)
    // =========================================================================
    else if (cmd.contains("statistique") || cmd.contains("statistiques")
             || cmd.contains("stats"))
    {
        if (QTabWidget *tw = mainWindow->findChild<QTabWidget *>("tabWidgetStock"))
            tw->setCurrentIndex(1);
    }

    // =========================================================================
    //  ESTIMATION / RENDEMENT
    //  Mots-clés : estimation, estimer, rendement, huile, calculer
    //  → Active l'onglet estimation (index 2) et lance le calcul
    // =========================================================================
    else if (cmd.contains("estimation") || cmd.contains("estimer")
             || cmd.contains("rendement") || cmd.contains("huile")
             || cmd.contains("calculer"))
    {
        if (QTabWidget *tw = mainWindow->findChild<QTabWidget *>("tabWidgetStock"))
            tw->setCurrentIndex(2);
        invokeMainWindow("on_btnCalculerEstimation_clicked");
    }

    // =========================================================================
    //  EXPORT PDF
    //  Mots-clés : export, exporter, pdf, rapport
    // =========================================================================
    else if (cmd.contains("export") || cmd.contains("exporter")
             || cmd.contains("pdf")  || cmd.contains("rapport"))
    {
        invokeMainWindow("on_btnExportStockPDF_clicked");
    }

    // =========================================================================
    //  RAFRAÎCHIR
    //  Mots-clés : rafraichir, actualiser, recharger
    // =========================================================================
    else if (cmd.contains("rafraichir") || cmd.contains("actualiser")
             || cmd.contains("recharger"))
    {
        invokeMainWindow("on_btnRefreshStock_clicked");
    }

    // =========================================================================
    //  VIDER LE FORMULAIRE
    //  Mots-clés : vider, reinitialiser, reset, effacer formulaire
    // =========================================================================
    else if (cmd.contains("vider")         || cmd.contains("reinitialiser")
             || cmd.contains("reset")      || cmd.contains("effacer formulaire"))
    {
        invokeMainWindow("on_btnClearStock_clicked");
    }

    // =========================================================================
    //  TRIER le tableau
    //  Mots-clés : trier, tri, classer, ordonner
    //  Colonnes : type(1), quantite(2), seuil(3), origine(4)  — défaut : ID(0)
    //  Ordre    : "desc" ou "decroissant" → descendant  — défaut : ascendant
    // =========================================================================
    else if (cmd.contains("trier") || cmd.contains("tri") || cmd.contains("trie")
             || cmd.contains("classer") || cmd.contains("ordonner"))
    {
        QTableWidget *table = resolveStockTable();
        if (table) {
            int sortCol = 0; // défaut : ID_STOCK
            if      (cmd.contains("type"))                          sortCol = 1;
            else if (cmd.contains("quantite") || cmd.contains("quantité")) sortCol = 2;
            else if (cmd.contains("seuil"))                         sortCol = 3;
            else if (cmd.contains("origine"))                       sortCol = 4;

            const Qt::SortOrder order =
                (cmd.contains("desc") || cmd.contains("decroissant"))
                    ? Qt::DescendingOrder
                    : Qt::AscendingOrder;

            table->sortItems(sortCol, order);
        }
    }

    // =========================================================================
    //  COMMANDE NON RECONNUE → message d'aide
    // =========================================================================
    else {
        QMessageBox::information(
            mainWindow,
            "Vocal — Stock",
            "Commande non reconnue : \"" + cmd + "\"\n\n"
                                                 "Exemples de commandes valides :\n"
                                                 "• \"ajouter stock type produit fini quantite 50 seuil 10 origine Mahdia\"\n"
                                                 "• \"ajouter stock type matiere premiere quantite 200 seuil 20 origine Sfax\"\n"
                                                 "• \"modifier stock id 3 quantite 80 seuil 15 origine Tunis\"\n"
                                                 "• \"modifier stock type huile quantite 120\"\n"
                                                 "• \"supprimer stock id 5\"\n"
                                                 "• \"supprimer stock type produit fini\"\n"
                                                 "• \"rechercher stock type huile\"\n"
                                                 "• \"rechercher stock origine Sfax\"\n"
                                                 "• \"rechercher tout\"\n"
                                                 "• \"statistiques\"\n"
                                                 "• \"estimation\"\n"
                                                 "• \"exporter\"\n"
                                                 "• \"trier par type\"\n"
                                                 "• \"trier par quantite decroissant\"\n"
                                                 "• \"rafraichir\"\n"
                                                 "• \"vider formulaire\"");
        return; // Ne pas afficher de feedback dans la barre de statut
    }

    // Afficher le feedback dans la barre de statut (3 secondes)
    if (mainWindow->statusBar())
        mainWindow->statusBar()->showMessage(feedback, 3000);
}
