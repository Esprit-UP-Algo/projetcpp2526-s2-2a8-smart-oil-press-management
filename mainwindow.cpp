#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machine_tri.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QDateTime>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QTabWidget>
#include <QLocale>
#include <QAbstractItemView>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QFrame>
#include <QScrollArea>
#include <QtCharts/QChartView>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stockManager(nullptr)
    , rechercheManager(nullptr)
    , exportPDFManager(nullptr)
    , statistiquesManager(nullptr)
    , estimationManager(nullptr)
    , selectedStockId(-1)
    , selectedClientId(-1)
{
    ui->setupUi(this);

    // Cacher le champ ID employé de l'interface
    ui->labelIdEmploye->setVisible(false);
    ui->inputIdEmploye->setVisible(false);

    // ← Ajouter ces deux lignes ici
    ui->inputDateEmbaucheEmploye->setDate(QDate::currentDate());
    ui->inputDateMaintenance->setDate(QDate::currentDate());

    ui->stackedWidget->setCurrentWidget(ui->page_login);
    ui->sidebar->setVisible(false);
    // ... reste du constructeur
    // =========================================================
    //  Connexions LOGIN
    // =========================================================
    connect(ui->btnLogin, &QPushButton::clicked,
            this, &MainWindow::onLoginClicked);
    connect(ui->txtPassword, &QLineEdit::returnPressed,
            this, &MainWindow::onLoginClicked);
    connect(ui->txtUsername, &QLineEdit::returnPressed, this, [this]() {
        ui->txtPassword->setFocus();
    });
    connect(ui->btnForgotPassword, &QPushButton::clicked,
            this, &MainWindow::onForgotPasswordClicked);
    connect(ui->btnResetPassword, &QPushButton::clicked,
            this, &MainWindow::onResetPasswordClicked);
    connect(ui->btnReturnToLogin, &QPushButton::clicked,
            this, &MainWindow::onReturnToLoginClicked);

    // =========================================================
    //  Connexion LOGOUT
    // =========================================================
    connect(ui->btnLogout, &QPushButton::clicked, this, [this]() {
        ui->sidebar->setVisible(false);
        ui->stackedWidget->setCurrentWidget(ui->page_login);
        clearLoginFields();
    });

    // =========================================================
    //  Sidebar Navigation
    // =========================================================
    connect(ui->btnEmploye, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
        chargerEmployes();
    });
    connect(ui->btnClient, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageClient);
        refreshClientTable();
    });
    connect(ui->btnStock, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageStock);
        refreshStockTable();
    });
    connect(ui->btnMachine, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMachine);
        chargerMachines();
    });
    connect(ui->btnProduction, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageProduction);
        refreshProductionTable();
    });
    connect(ui->btnPartenaire, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pagePartenaire);
        chargerPartenaires();
        chargerEmployesComboBox();
    });

    // =========================================================
    //  Stock connections
    // =========================================================
    connect(ui->btnRefreshStock,       &QPushButton::clicked, this, &MainWindow::on_btnRefreshStock_clicked);
    connect(ui->btnSearchStock,        &QPushButton::clicked, this, &MainWindow::on_btnSearchStock_clicked);
    connect(ui->btnClearStock,         &QPushButton::clicked, this, &MainWindow::on_btnClearStock_clicked);
    connect(ui->btnExportStockPDF,     &QPushButton::clicked, this, &MainWindow::on_btnExportStockPDF_clicked);
    connect(ui->btnCalculerEstimation, &QPushButton::clicked, this, &MainWindow::on_btnCalculerEstimation_clicked);
    // Bouton vocal stock (connecté si présent dans le .ui)
    if (QPushButton *btnVocal = this->findChild<QPushButton *>("btnVocalStock"))
        connect(btnVocal, &QPushButton::clicked, this, &MainWindow::on_btnVocalStock_clicked);

    connect(ui->stockTable,     &QTableWidget::itemClicked,  this, &MainWindow::on_stockTable_itemClicked);
    connect(ui->searchBoxStock, &QLineEdit::returnPressed,   this, &MainWindow::on_btnSearchStock_clicked);
    connect(ui->tabWidgetStock, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetStock_currentChanged);

    // =========================================================
    //  Production connections
    // =========================================================

    connect(ui->btnClearProduction,     &QPushButton::clicked, this, &MainWindow::on_btnClearProduction_clicked);


    connect(ui->productionTable, &QTableWidget::itemClicked,  this, &MainWindow::on_productionTable_itemClicked);
    connect(ui->tabWidget,       &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

    // Appuyer sur Entrée dans la barre de recherche déclenche la recherche
    connect(ui->searchBox, &QLineEdit::returnPressed,
            this, &MainWindow::on_btnSearchProduction_clicked);

    connect(ui->inputQuantiteOlive,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateRendementDisplay);
    connect(ui->inputQuantiteHuile,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateRendementDisplay);

    // AI: Prédiction
    connect(ui->btnPredictProduction, &QPushButton::clicked,
            this, &MainWindow::on_btnPredictProduction_clicked);
    connect(&predectionProd, &PredectionProd::predictionPrete,
            this, &MainWindow::onPredictionPrete);
    connect(&predectionProd, &PredectionProd::erreurSurvenue,
            this, &MainWindow::onPredectionErreur);

    // AI: Détection anomalies
    connect(ui->btnAnalyzeProduction, &QPushButton::clicked,
            this, &MainWindow::on_btnAnalyzeProduction_clicked);
    connect(&detectionProd, &DetectionProd::analyseTerminee,
            this, &MainWindow::onAnalyseTerminee);
    connect(&detectionProd, &DetectionProd::explicationPrete,
            this, &MainWindow::onDetectionExplicationPrete);
    connect(&detectionProd, &DetectionProd::erreurSurvenue,
            this, &MainWindow::onDetectionErreur);

    // =========================================================
    //  Partenaire connections
    // =========================================================
    connect(ui->searchpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_searchpartenaireButton_clicked);
    connect(ui->filterpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_filterpartenaireButton_clicked);
    connect(ui->exportpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_exportpartenaireButton_clicked);

    connect(ui->partnersTable,            &QTableWidget::itemClicked,  this, &MainWindow::on_partnersTable_itemClicked);
    connect(ui->searchpartenaireLineEdit, &QLineEdit::returnPressed,   this, &MainWindow::on_searchpartenaireButton_clicked);
    connect(ui->searchpartenaireLineEdit, &QLineEdit::textChanged,     this, &MainWindow::on_searchpartenaireLineEdit_textChanged);
    connect(ui->tabWidgetPartenaire,      &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetPartenaire_currentChanged);

    connect(ui->chatbotSendButton,    &QPushButton::clicked,
            this, &MainWindow::on_chatbotSendButton_clicked);
    connect(ui->chatbotInputLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::on_chatbotSendButton_clicked);
    connect(&chatbot, &ChatBot::reponseRecue,
            this, &MainWindow::onChatbotReponse);
    connect(&chatbot, &ChatBot::erreurSurvenue,
            this, &MainWindow::onChatbotErreur);

    // =========================================================
    //  Client connections
    // =========================================================
    connect(ui->btnRefreshClient,    &QPushButton::clicked, this, &MainWindow::on_btnRefreshClient_clicked);
    connect(ui->btnSearchClient,     &QPushButton::clicked, this, &MainWindow::on_btnSearchClient_clicked);
    connect(ui->btnClearClient,      &QPushButton::clicked, this, &MainWindow::on_btnClearClient_clicked);
    connect(ui->btnExportClientPDF,  &QPushButton::clicked, this, &MainWindow::on_btnExportClientPDF_clicked);
    connect(ui->btnTriClient,        &QPushButton::clicked, this, &MainWindow::on_btnTriClient_clicked);
    connect(ui->btnHistoriqueClient, &QPushButton::clicked, this, &MainWindow::on_btnHistoriqueClient_clicked);
    connect(ui->btnPrevisionClient,  &QPushButton::clicked, this, &MainWindow::on_btnPrevisionClient_clicked);

    connect(ui->clientTable,     &QTableWidget::itemClicked,  this, &MainWindow::on_clientTable_itemClicked);
    connect(ui->searchBoxClient, &QLineEdit::returnPressed,   this, &MainWindow::on_btnSearchClient_clicked);
    connect(ui->tabWidgetClient, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetClient_currentChanged);

    // =========================================================
    //  Employé connections
    // =========================================================
    connect(ui->btnRefreshEmploye, &QPushButton::clicked, this, &MainWindow::on_btnRefreshEmploye_clicked);
    connect(ui->employeTable,     &QTableWidget::clicked,      this, &MainWindow::on_employeTable_clicked);
    connect(ui->searchBoxEmploye, &QLineEdit::textChanged,     this, &MainWindow::on_searchBoxEmploye_textChanged);
    connect(ui->tabWidgetEmploye, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetEmploye_currentChanged);

    QPushButton *exportEmployeBtn = ui->employeListTab->findChild<QPushButton*>("exportButton");
    if (exportEmployeBtn)
        connect(exportEmployeBtn, &QPushButton::clicked, this, &MainWindow::exporterEmployesPDF);


    // =========================================================
    //  Machine connections
    // =========================================================
    connect(ui->btnRefreshMachine, &QPushButton::clicked, this, &MainWindow::on_btnRefreshMachine_clicked);
    connect(ui->machineTable,     &QTableWidget::clicked,  this, &MainWindow::on_machineTable_clicked);
    connect(ui->searchBoxMachine, &QLineEdit::textChanged, this, &MainWindow::on_searchBoxMachine_textChanged);

    if (ui->btnExportMachinePDF)
        connect(ui->btnExportMachinePDF, &QPushButton::clicked, this, &MainWindow::exporterMachinesPDF);

    QPushButton *triMachineBtn = ui->machineListTab->findChild<QPushButton*>("btnTriMachine");
    if (triMachineBtn)
        connect(triMachineBtn, &QPushButton::clicked, this, &MainWindow::on_btnTriMachine_clicked);

    // =========================================================
    //  Jumeau Numérique (Digital Twin) — initialization
    // =========================================================
    jumeau = new JumauNumerique(this);
    if (ui->stackedWidget->indexOf(jumeau) == -1)
        ui->stackedWidget->addWidget(jumeau);

    QPushButton *diagnosticMachineBtn = this->findChild<QPushButton*>("btnDiagnosticMachine");
    if (diagnosticMachineBtn)
        connect(diagnosticMachineBtn, &QPushButton::clicked,
                this, &MainWindow::on_btnDiagnosticMachine_clicked);

    // =========================================================
    //  Initial state
    // =========================================================
    applyLoginStyles();
    ui->inputDate->setDate(QDate::currentDate());

    chargerEmployes();
    chargerMachines();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
//  setDatabase
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setDatabase(const QSqlDatabase &database)
{
    this->db            = database;
    stockManager        = new Stock(db, this);
    rechercheManager    = new Recherche(db, this);
    exportPDFManager    = new ExportPDF(this);
    statistiquesManager = new Statistiques(db, this);
    estimationManager   = new Estimation(db, this);
    voiceStock          = new VoiceMatieres(this, ui->stockTable);

    chatbot.setDatabase(database);

    if (jumeau) {
        jumeau->setDatabase(database);
        jumeau->loadMachines();
    }

    refreshProductionTable();
    refreshClientTable();

    // ── RFID Manager ──────────────────────────────────────────
    rfidManager = new RfidManager(this);
    rfidManager->setDatabase(database);

    connect(rfidManager, &RfidManager::employeDetecte,
            this, &MainWindow::onEmployeDetecte);
    connect(rfidManager, &RfidManager::carteInconnue,
            this, &MainWindow::onCarteInconnue);

    // Connexion directe sur COM3
    if (rfidManager->connectToArduino("COM3")) {
        qDebug() << "✅ Arduino connecté sur COM3";
    } else {
        qDebug() << "❌ Échec connexion COM3";
    }
}

void MainWindow::onEmployeDetecte(const QString &nom,
                                  const QString &prenom,
                                  const QString &poste)
{
    QMessageBox::information(this, "✅ Employé identifié",
                             QString("Bienvenue !\n\nNom   : %1\nPrénom: %2\nPoste : %3")
                                 .arg(nom).arg(prenom).arg(poste));
}

void MainWindow::onCarteInconnue(const QString &uid)
{
    QMessageBox::warning(this, "❌ Accès refusé",
                         "Carte RFID inconnue !\nUID: " + uid);
}
// =============================================================================
//  LOGIN
// =============================================================================

void MainWindow::onLoginClicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text();
    if (username.isEmpty() || password.isEmpty()) {
        showMessage("Erreur", "Veuillez remplir tous les champs.", QMessageBox::Warning);
        return;
    }
    if (validateLogin(username, password)) {
        ui->sidebar->setVisible(true);
        ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
        clearLoginFields();
        chargerEmployes();
    } else {
        showMessage("Erreur", "Nom d'utilisateur ou mot de passe incorrect.", QMessageBox::Critical);
        ui->txtPassword->clear();
        ui->txtPassword->setFocus();
    }
}

void MainWindow::onForgotPasswordClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_reset);
    clearResetFields();
    ui->txtResetUsername->setFocus();
}

void MainWindow::onResetPasswordClicked()
{
    QString username        = ui->txtResetUsername->text().trimmed();
    QString newPassword     = ui->txtNewPassword->text();
    QString confirmPassword = ui->txtConfirmPassword->text();

    if (username.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Erreur", "Veuillez remplir tous les champs.", QMessageBox::Warning);
        return;
    }
    if (newPassword != confirmPassword) {
        showMessage("Erreur", "Les mots de passe ne correspondent pas.", QMessageBox::Warning);
        ui->txtConfirmPassword->clear();
        ui->txtConfirmPassword->setFocus();
        return;
    }
    if (newPassword.length() < 4) {
        showMessage("Erreur", "Le mot de passe doit contenir au moins 4 caractères.", QMessageBox::Warning);
        return;
    }

    bool isResponsable   = false;
    QString nomRecherche = "";

    if (username.startsWith("resp_")) {
        nomRecherche = username.mid(5);
        QSqlQuery qCheck;
        qCheck.prepare(
            "SELECT COUNT(*) FROM EMPLOYE "
            "WHERE LOWER(NOM) = LOWER(:nom) "
            "  AND POSTE = 'Responsable'");
        qCheck.bindValue(":nom", nomRecherche);
        if (qCheck.exec() && qCheck.next())
            isResponsable = (qCheck.value(0).toInt() > 0);
    }

    if (!isResponsable) {
        showMessage("Erreur",
                    "Nom d'utilisateur introuvable ou ce compte n'est pas un Responsable.\n"
                    "Format attendu : resp_<votre_nom>",
                    QMessageBox::Warning);
        return;
    }

    QDialog dlgId(this);
    dlgId.setWindowTitle("Vérification d'identité");
    dlgId.setFixedSize(420, 250);
    dlgId.setStyleSheet("background:white;");

    auto *vlay = new QVBoxLayout(&dlgId);
    vlay->setContentsMargins(30, 25, 30, 25);
    vlay->setSpacing(14);

    auto *title = new QLabel("🔎  Vérification d'identité");
    title->setStyleSheet("font-size:15px;font-weight:bold;color:#2d4a1f;");
    vlay->addWidget(title);

    auto *sub = new QLabel(
        QString("Veuillez entrer votre ID Employé\n"
                "pour confirmer la réinitialisation du compte  « %1 ».")
            .arg(username));
    sub->setStyleSheet("color:#555;font-size:12px;");
    sub->setWordWrap(true);
    vlay->addWidget(sub);

    auto *lblId = new QLabel("ID Employé :");
    lblId->setStyleSheet("color:#2d4a1f;font-weight:bold;");
    vlay->addWidget(lblId);

    auto *edtId = new QLineEdit;
    edtId->setPlaceholderText("Entrez votre ID (ex : 21)...");
    edtId->setStyleSheet(
        "padding:9px;border:2px solid #5d732c;border-radius:6px;font-size:13px;");
    vlay->addWidget(edtId);

    auto *errLbl = new QLabel("");
    errLbl->setStyleSheet("color:#dc3545;font-size:11px;");
    vlay->addWidget(errLbl);

    auto *btnRow = new QHBoxLayout;
    auto *btnOk  = new QPushButton("✅ Vérifier");
    auto *btnAnn = new QPushButton("Annuler");
    btnOk->setStyleSheet(
        "background:#ffd700;color:#2d4a1f;border:none;"
        "padding:10px 22px;border-radius:6px;font-weight:bold;");
    btnAnn->setStyleSheet(
        "background:#6c757d;color:white;border:none;"
        "padding:10px 22px;border-radius:6px;font-weight:bold;");
    btnRow->addStretch();
    btnRow->addWidget(btnOk);
    btnRow->addWidget(btnAnn);
    vlay->addLayout(btnRow);

    connect(btnAnn, &QPushButton::clicked, &dlgId, &QDialog::reject);

    bool identiteVerifiee = false;

    connect(btnOk, &QPushButton::clicked, &dlgId, [&]() {
        QString idStr = edtId->text().trimmed();
        if (idStr.isEmpty()) {
            errLbl->setText("⚠  Veuillez entrer votre ID.");
            return;
        }
        bool ok = false;
        int idSaisi = idStr.toInt(&ok);
        if (!ok) {
            errLbl->setText("⚠  L'ID doit être un nombre entier.");
            return;
        }

        QSqlQuery qVerif;
        qVerif.prepare(
            "SELECT COUNT(*) FROM EMPLOYE "
            "WHERE ID_EMPLOYE = :id "
            "  AND LOWER(NOM)  = LOWER(:nom) "
            "  AND POSTE       = 'Responsable'");
        qVerif.bindValue(":id",  idSaisi);
        qVerif.bindValue(":nom", nomRecherche);

        if (!qVerif.exec()) {
            errLbl->setText("⚠  Erreur base de données.");
            return;
        }
        qVerif.next();
        if (qVerif.value(0).toInt() == 0) {
            errLbl->setText("❌  ID incorrect. Vérification échouée.");
            edtId->clear();
            edtId->setFocus();
            return;
        }

        QSqlQuery qUpdate;
        qUpdate.prepare(
            "UPDATE EMPLOYE SET MDP = :mdp "
            "WHERE ID_EMPLOYE = :id "
            "  AND LOWER(NOM)  = LOWER(:nom) "
            "  AND POSTE       = 'Responsable'");
        qUpdate.bindValue(":mdp", newPassword);
        qUpdate.bindValue(":id",  idSaisi);
        qUpdate.bindValue(":nom", nomRecherche);

        if (!qUpdate.exec()) {
            errLbl->setText("⚠  Échec de la mise à jour du mot de passe.");
            return;
        }

        identiteVerifiee = true;
        dlgId.accept();
    });

    connect(edtId, &QLineEdit::returnPressed, btnOk, &QPushButton::click);

    if (dlgId.exec() != QDialog::Accepted || !identiteVerifiee)
        return;

    QDialog dlgOk(this);
    dlgOk.setWindowTitle("Mot de passe réinitialisé");
    dlgOk.setFixedSize(480, 280);
    dlgOk.setStyleSheet("background:white;");

    auto *vl2 = new QVBoxLayout(&dlgOk);
    vl2->setContentsMargins(30, 25, 30, 25);
    vl2->setSpacing(14);

    auto *ico = new QLabel("✅  Mot de passe réinitialisé avec succès !");
    ico->setStyleSheet("font-size:14px;font-weight:bold;color:#2d4a1f;");
    vl2->addWidget(ico);

    auto *sep = new QFrame;
    sep->setFrameShape(QFrame::HLine);
    sep->setStyleSheet("color:#5d732c;");
    vl2->addWidget(sep);

    auto *rowUser = new QHBoxLayout;
    auto *lblUser = new QLabel("👤  Nom d'utilisateur :");
    lblUser->setStyleSheet("font-weight:bold;color:#2d4a1f;min-width:170px;");
    auto *valUser = new QLabel(username);
    valUser->setStyleSheet(
        "background:#f0f7e8;border:2px solid #5d732c;"
        "border-radius:6px;padding:7px 14px;"
        "font-size:13px;font-weight:bold;color:#2d4a1f;");
    valUser->setTextInteractionFlags(Qt::TextSelectableByMouse);
    rowUser->addWidget(lblUser);
    rowUser->addWidget(valUser, 1);
    vl2->addLayout(rowUser);

    auto *rowMdp = new QHBoxLayout;
    auto *lblMdp2 = new QLabel("🔒  Nouveau mot de passe :");
    lblMdp2->setStyleSheet("font-weight:bold;color:#2d4a1f;min-width:170px;");
    auto *valMdp = new QLabel(newPassword);
    valMdp->setStyleSheet(
        "background:#f0f7e8;border:2px solid #5d732c;"
        "border-radius:6px;padding:7px 14px;"
        "font-size:13px;font-weight:bold;color:#2d4a1f;");
    valMdp->setTextInteractionFlags(Qt::TextSelectableByMouse);
    rowMdp->addWidget(lblMdp2);
    rowMdp->addWidget(valMdp, 1);
    vl2->addLayout(rowMdp);

    auto *note = new QLabel("ℹ️  Conservez ces informations pour vous reconnecter.");
    note->setStyleSheet("color:#888;font-size:11px;");
    vl2->addWidget(note);

    auto *btnLogin = new QPushButton("🔑 Aller à la connexion");
    btnLogin->setStyleSheet(
        "background:#2d4a1f;color:white;border:none;"
        "padding:11px 24px;border-radius:6px;font-weight:bold;font-size:13px;");
    connect(btnLogin, &QPushButton::clicked, &dlgOk, &QDialog::accept);
    vl2->addWidget(btnLogin, 0, Qt::AlignRight);

    dlgOk.exec();

    ui->stackedWidget->setCurrentWidget(ui->page_login);
    clearResetFields();
    ui->txtUsername->setText(username);
    ui->txtPassword->setFocus();
}

void MainWindow::onReturnToLoginClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_login);
    clearResetFields();
}

bool MainWindow::validateLogin(const QString &username, const QString &password)
{
    if (username == "admin" && password == "admin123")
        return true;

    if (username.startsWith("resp_")) {
        QString nomRecherche = username.mid(5);

        QSqlQuery q;
        q.prepare(
            "SELECT COUNT(*) FROM EMPLOYE "
            "WHERE LOWER(NOM) = LOWER(:nom) "
            "  AND POSTE = 'Responsable' "
            "  AND MDP = :mdp");
        q.bindValue(":nom", nomRecherche);
        q.bindValue(":mdp", password);

        if (q.exec() && q.next() && q.value(0).toInt() > 0)
            return true;
    }

    return false;
}

bool MainWindow::validatePasswordReset(const QString &username,
                                       const QString &newPassword,
                                       const QString &confirmPassword)
{
    if (username.length() < 3) {
        showMessage("Erreur", "Le nom d'utilisateur est invalide.", QMessageBox::Warning);
        return false;
    }
    if (newPassword != confirmPassword) {
        showMessage("Erreur", "Les mots de passe ne correspondent pas.", QMessageBox::Warning);
        ui->txtConfirmPassword->clear();
        ui->txtConfirmPassword->setFocus();
        return false;
    }
    if (newPassword.length() < 6) {
        showMessage("Erreur", "Le mot de passe doit contenir au moins 6 caractères.", QMessageBox::Warning);
        return false;
    }
    return true;
}

void MainWindow::clearLoginFields()
{
    ui->txtUsername->clear();
    ui->txtPassword->clear();
}

void MainWindow::clearResetFields()
{
    ui->txtResetUsername->clear();
    ui->txtNewPassword->clear();
    ui->txtConfirmPassword->clear();
}

void MainWindow::applyLoginStyles()
{
    QString inputStyle =
        "QLineEdit {"
        "   background-color: #f8f9fa;"
        "   border: none;"
        "   border-bottom: 2px solid #e0e0e0;"
        "   border-radius: 0px;"
        "   padding: 12px 5px;"
        "   font-size: 14px;"
        "   color: #333;"
        "}"
        "QLineEdit:focus {"
        "   border-bottom: 2px solid #4a7c2e;"
        "   background-color: white;"
        "}";
    ui->txtUsername->setStyleSheet(inputStyle);
    ui->txtPassword->setStyleSheet(inputStyle);
    ui->txtResetUsername->setStyleSheet(inputStyle);
    ui->txtNewPassword->setStyleSheet(inputStyle);
    ui->txtConfirmPassword->setStyleSheet(inputStyle);

    QString primaryButtonStyle =
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4a7c2e, stop:1 #2d5016);"
        "   color: white; border: none; border-radius: 25px;"
        "   font-size: 16px; font-weight: bold; padding: 12px; letter-spacing: 1px;"
        "}"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5a9c3e, stop:1 #3d6026); }"
        "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3a6c2e, stop:1 #1d4016); }";
    ui->btnLogin->setStyleSheet(primaryButtonStyle);
    ui->btnResetPassword->setStyleSheet(primaryButtonStyle);

    ui->btnForgotPassword->setStyleSheet(
        "QPushButton { background: transparent; color: #4a7c2e; border: none; font-size: 12px; text-decoration: underline; }"
        "QPushButton:hover { color: #2d5016; }");
    ui->btnReturnToLogin->setStyleSheet(
        "QPushButton { background: transparent; color: #888; border: none; font-size: 13px; padding: 8px; text-decoration: underline; }"
        "QPushButton:hover { color: #4a7c2e; }");
}

void MainWindow::showMessage(const QString &title, const QString &message, QMessageBox::Icon icon)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(icon);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: white; }"
        "QMessageBox QLabel { color: #333; font-size: 13px; border: none; background: transparent; }"
        "QPushButton { background-color: #4a7c2e; color: white; border: none; border-radius: 5px; padding: 8px 20px; font-size: 13px; min-width: 80px; }"
        "QPushButton:hover { background-color: #5a9c3e; }");
    msgBox.exec();
}

// =============================================================================
//  Navigation stubs
// =============================================================================
void MainWindow::on_btnEmploye_clicked()    {}
void MainWindow::on_btnClient_clicked()     {}
void MainWindow::on_btnStock_clicked()      {}
void MainWindow::on_btnMachine_clicked()    {}
void MainWindow::on_btnProduction_clicked() {}
void MainWindow::on_btnPartenaire_clicked() {}

// =============================================================================
//  STOCK
// =============================================================================

void MainWindow::refreshStockTable()
{
    if (stockManager) stockManager->loadData(ui->stockTable);
}

void MainWindow::clearFormStock()
{
    selectedStockId = -1;
    ui->inputTypeStock->setCurrentIndex(0);
    ui->inputQuantiteStock->setValue(0.0);
    ui->inputSeuilStock->setValue(0.0);
    ui->inputOrigineStock->clear();
}

void MainWindow::on_tabWidgetStock_currentChanged(int index)
{
    if (index == 1 && statistiquesManager) {
        statistiquesManager->chargerStats(
            ui->valueTotalStocks, ui->valueAlertStocks,
            ui->valueTotalQuantite, ui->valueMoyenneQuantite,
            ui->valueStockMax, ui->valueStockMin,
            ui->valueNbOrigines, ui->valueStockCritique);
    } else if (index == 2 && estimationManager) {
        estimationManager->calculerEstimation(
            ui->spinTauxRendement->value(), ui->tableEstimation,
            ui->valueTotalOlives, ui->valueHuileEstimee,
            ui->valueRendementMoyen, ui->valueStocksInsuffisants);
    }
}

void MainWindow::on_btnCalculerEstimation_clicked()
{
    if (!estimationManager) return;
    double taux = ui->spinTauxRendement->value();
    if (taux <= 0) {
        QMessageBox::warning(this, "Taux invalide", "Le taux de rendement doit être supérieur à 0%.");
        return;
    }
    estimationManager->calculerEstimation(
        taux, ui->tableEstimation, ui->valueTotalOlives,
        ui->valueHuileEstimee, ui->valueRendementMoyen, ui->valueStocksInsuffisants);
}

void MainWindow::on_stockTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;
    int row = item->row();
    selectedStockId = ui->stockTable->item(row, 0)->text().toInt();
    QString typeText = ui->stockTable->item(row, 1)->text();
    int idx = ui->inputTypeStock->findText(typeText);
    ui->inputTypeStock->setCurrentIndex(idx != -1 ? idx : 0);
    ui->inputQuantiteStock->setValue(ui->stockTable->item(row, 2)->text().toDouble());
    ui->inputSeuilStock->setValue(ui->stockTable->item(row, 3)->text().toDouble());
    ui->inputOrigineStock->setText(ui->stockTable->item(row, 4)->text());
}

void MainWindow::on_btnAddStock_clicked()
{
    if (!stockManager) return;
    stockManager->addStock(
        ui->inputTypeStock->currentText(),
        ui->inputQuantiteStock->value(),
        ui->inputSeuilStock->value(),
        ui->inputOrigineStock->text().trimmed(),
        ui->stockTable);
    clearFormStock();
}

void MainWindow::on_btnUpdateStock_clicked()
{
    if (!stockManager) return;
    if (selectedStockId == -1) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un stock dans le tableau pour le modifier.");
        return;
    }
    stockManager->updateStock(selectedStockId, ui->inputTypeStock->currentText(),
                              ui->inputQuantiteStock->value(), ui->inputSeuilStock->value(),
                              ui->inputOrigineStock->text().trimmed(), ui->stockTable);
    clearFormStock();
}

void MainWindow::on_btnDeleteStock_clicked()
{
    if (!stockManager) return;
    if (selectedStockId == -1) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un stock dans le tableau pour le supprimer.");
        return;
    }
    stockManager->deleteStock(selectedStockId, ui->stockTable);
    clearFormStock();
}

void MainWindow::on_btnRefreshStock_clicked()
{
    ui->searchBoxStock->clear();
    clearFormStock();
    ui->stockTable->clearSelection();
    refreshStockTable();
}

void MainWindow::on_btnSearchStock_clicked()
{
    if (!rechercheManager) return;
    rechercheManager->rechercherStock(ui->searchBoxStock->text().trimmed(), ui->stockTable);
}

void MainWindow::on_btnClearStock_clicked()
{
    clearFormStock();
    ui->searchBoxStock->clear();
    ui->stockTable->clearSelection();
    ui->searchBoxStock->setFocus();
}

void MainWindow::on_btnExportStockPDF_clicked()
{
    if (!exportPDFManager) return;
    exportPDFManager->exporterStockPDF(ui->stockTable, this);
}

void MainWindow::on_btnVocalStock_clicked()
{
    if (voiceStock)
        voiceStock->openVoiceDialog();
}

// =============================================================================
//  PRODUCTION
// =============================================================================

void MainWindow::updateRendementDisplay()
{
    double olive = ui->inputQuantiteOlive->value();
    double huile = ui->inputQuantiteHuile->value();
    if (olive > 0 && huile > 0)
        ui->inputRendement->setText(
            QString::number((huile / olive) * 100.0, 'f', 2) + " %");
    else
        ui->inputRendement->clear();
}

void MainWindow::refreshProductionTable()
{
    prod.afficher(ui->productionTable);
}

void MainWindow::clearFormProduction()
{
    prod.setId(0);

    ui->inputQuantiteOlive->blockSignals(true);
    ui->inputQuantiteHuile->blockSignals(true);

    ui->inputDate->setDate(QDate::currentDate());
    ui->inputQuantiteOlive->setValue(0.0);
    ui->inputQuantiteHuile->setValue(0.0);
    ui->inputRendement->clear();

    ui->inputQuantiteOlive->blockSignals(false);
    ui->inputQuantiteHuile->blockSignals(false);

    ui->inputReg->setCurrentIndex(0);
    ui->productionTable->clearSelection();
}

static QString regKeyFromComboText(const QString &text)
{
    int spaceIdx = text.indexOf(' ');
    if (spaceIdx > 0)
        return text.left(spaceIdx).trimmed().toLower();
    return text.trimmed().toLower();
}

static int findRegComboIndex(QComboBox *combo, const QString &key)
{
    for (int i = 0; i < combo->count(); ++i) {
        QString itemKey = regKeyFromComboText(combo->itemText(i));
        if (itemKey == key.trimmed().toLower())
            return i;
    }
    return 0;
}

void MainWindow::on_productionTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;
    int row = item->row();

    prod.setId(ui->productionTable->item(row, 0)->text().toInt());

    QDate date = QDate::fromString(
        ui->productionTable->item(row, 1)->text(), "dd/MM/yyyy");
    ui->inputDate->setDate(date.isValid() ? date : QDate::currentDate());

    auto stripUnit = [](const QString &s) -> double {
        QString clean = s;
        clean.remove(" kg").remove(" L").remove(" %");
        return clean.toDouble();
    };

    ui->inputQuantiteOlive->blockSignals(true);
    ui->inputQuantiteHuile->blockSignals(true);

    ui->inputQuantiteOlive->setValue(stripUnit(ui->productionTable->item(row, 2)->text()));
    ui->inputQuantiteHuile->setValue(stripUnit(ui->productionTable->item(row, 3)->text()));

    ui->inputQuantiteOlive->blockSignals(false);
    ui->inputQuantiteHuile->blockSignals(false);

    ui->inputRendement->setText(ui->productionTable->item(row, 4)->text());

    int id = prod.getId();
    QSqlQuery qReg;
    qReg.prepare("SELECT NVL(REG, '') AS REG FROM ZIT.PRODUCTION WHERE ID_PROD = :id");
    qReg.bindValue(":id", id);
    if (qReg.exec() && qReg.next()) {
        QString regVal = qReg.value("REG").toString().trimmed().toLower();
        ui->inputReg->setCurrentIndex(findRegComboIndex(ui->inputReg, regVal));
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        stat.calculerEtAfficher(
            ui->valueTotal,
            ui->valueOlives,
            ui->valueHuile,
            ui->valueRendement);

        QLayout *lay = ui->regionChartFrame->layout();
        if (lay) {
            while (lay->count() > 1) {
                QLayoutItem *it = lay->takeAt(lay->count() - 1);
                if (it->widget()) it->widget()->deleteLater();
                delete it;
            }
        }
        QChartView *chartView = stat.creerGraphiqueRegions();
        if (lay) lay->addWidget(chartView);
    }
}

void MainWindow::on_btnAddProduction_clicked()
{
    double olive = ui->inputQuantiteOlive->value();
    double huile = ui->inputQuantiteHuile->value();

    if (olive <= 0) {
        QMessageBox::warning(this, "Validation", "La quantité d'olives doit être supérieure à 0.");
        return;
    }
    if (huile <= 0) {
        QMessageBox::warning(this, "Validation", "La quantité d'huile doit être supérieure à 0.");
        return;
    }
    if (huile > olive) {
        QMessageBox::warning(this, "Validation", "La quantité d'huile ne peut pas dépasser la quantité d'olives.");
        return;
    }

    double huileCorrigee = huile * 0.916;
    double rendement     = (huileCorrigee / olive) * 100.0;
    QString regKey       = regKeyFromComboText(ui->inputReg->currentText());

    prod.setDateProd(ui->inputDate->date());
    prod.setQuantiteOlive(olive);
    prod.setQuantiteHuile(huileCorrigee);
    prod.setRendement(rendement);
    prod.setReg(regKey);

    if (prod.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Production ajoutée avec succès !");
        refreshProductionTable();
        clearFormProduction();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter la production.");
    }
}

void MainWindow::on_btnUpdateProduction_clicked()
{
    if (prod.getId() == 0) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une production dans le tableau.");
        return;
    }

    double olive = ui->inputQuantiteOlive->value();
    double huile = ui->inputQuantiteHuile->value();

    if (olive <= 0) {
        QMessageBox::warning(this, "Validation", "La quantité d'olives doit être supérieure à 0.");
        return;
    }
    if (huile <= 0) {
        QMessageBox::warning(this, "Validation", "La quantité d'huile doit être supérieure à 0.");
        return;
    }
    if (huile > olive) {
        QMessageBox::warning(this, "Validation", "La quantité d'huile ne peut pas dépasser la quantité d'olives.");
        return;
    }

    double huileCorrigee = huile * 0.916;
    double rendement     = (huileCorrigee / olive) * 100.0;
    QString regKey       = regKeyFromComboText(ui->inputReg->currentText());

    prod.setDateProd(ui->inputDate->date());
    prod.setQuantiteOlive(olive);
    prod.setQuantiteHuile(huileCorrigee);
    prod.setRendement(rendement);
    prod.setReg(regKey);

    if (prod.modifier()) {
        QMessageBox::information(this, "Succès", "✅ Production modifiée avec succès !");
        refreshProductionTable();
        clearFormProduction();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de modifier la production.");
    }
}

void MainWindow::on_btnDeleteProduction_clicked()
{
    if (prod.getId() == 0) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une production dans le tableau.");
        return;
    }
    auto reply = QMessageBox::question(this, "Confirmation",
                                       "Confirmer la suppression de cette production ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int idToDelete = prod.getId();
        if (prod.supprimer(idToDelete)) {
            QMessageBox::information(this, "Succès", "✅ Production supprimée !");
            refreshProductionTable();
            clearFormProduction();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer la production.");
        }
    }
}

void MainWindow::on_btnRefreshProduction_clicked()
{
    QMenu menu(this);
    menu.setStyleSheet(
        "QMenu { background-color: white; border: 2px solid #5d732c; border-radius: 6px; padding: 4px; }"
        "QMenu::item { padding: 10px 20px; font-size: 13px; color: #2d4a1f; font-weight: bold; }"
        "QMenu::item:selected { background-color: #ffd700; color: #2d4a1f; border-radius: 4px; }"
        "QMenu::separator { height: 1px; background: #5d732c; margin: 4px 8px; }");

    menu.addAction("📅  Date la plus récente",
                   [this]() { filterProd.filtrerParDateRecente(ui->productionTable); clearFormProduction(); });
    menu.addAction("🫒  Quantité d'olives (↓ décroissant)",
                   [this]() { filterProd.filtrerParOliveDecroissant(ui->productionTable); clearFormProduction(); });
    menu.addAction("🛢  Quantité d'huile (↓ décroissant)",
                   [this]() { filterProd.filtrerParHuileDecroissant(ui->productionTable); clearFormProduction(); });
    menu.addAction("📊  Rendement (↓ décroissant)",
                   [this]() { filterProd.filtrerParRendementDecroissant(ui->productionTable); clearFormProduction(); });
    menu.addSeparator();
    menu.addAction("🔄  Réinitialiser (ordre par ID)",
                   [this]() { clearFormProduction(); refreshProductionTable(); });

    menu.exec(QCursor::pos());
}

// ─────────────────────────────────────────────────────────────────────────────
//  on_btnSearchProduction_clicked
//  ← MODIFIÉ : délègue à RechProduction::rechercher()
//
//  Formats acceptés (définis dans rechproduction.cpp) :
//    • "150 kg"  ou  "150.5 KG"  → recherche par quantité d'olives
//    • "50 L"    ou  "50.5 l"    → recherche par quantité d'huile
//    • "04/06/2025"              → recherche par date (MM/DD/YYYY)
//  Si la barre est vide → restaure le tableau complet.
//  Si le format est invalide → RechProduction affiche une boîte de dialogue.
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::on_btnSearchProduction_clicked()
{
    QString terme = ui->searchBox->text().trimmed();

    // Barre vide → on affiche tout
    if (terme.isEmpty()) {
        refreshProductionTable();
        return;
    }

    // Déléguer au module de recherche
    rechProd.rechercher(terme, ui->productionTable);
}

// ─────────────────────────────────────────────────────────────────────────────
//  on_btnClearProduction_clicked
//  ← MODIFIÉ : efface la barre de recherche ET restaure le tableau complet
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::on_btnClearProduction_clicked()
{
    ui->searchBox->clear();
    clearFormProduction();
    refreshProductionTable();   // recharge toutes les productions depuis la DB
    ui->searchBox->setFocus();
}

void MainWindow::on_btnExportPDFProduction_clicked()
{
    pdfProd.exporterPDF(this);
}

void MainWindow::on_btnPredictProduction_clicked()
{
    double olive = ui->inputPredOlives->value();
    if (olive <= 0) {
        QMessageBox::warning(this, "Validation", "Veuillez entrer une quantité d'olives supérieure à 0.");
        return;
    }
    ui->btnPredictProduction->setEnabled(false);
    ui->btnPredictProduction->setText("⏳ Analyse en cours...");
    ui->valuePredRendement->setText("⏳ ...");
    ui->valuePredHuile->setText("L'IA analyse l'historique...");
    ui->predExplicationText->setText(
        "⏳ L'IA analyse les données historiques de production...\n"
        "Merci de patienter quelques secondes.");
    predectionProd.predire(olive);
}

void MainWindow::on_btnAnalyzeProduction_clicked()
{
    int seuil = ui->inputThreshold->value();
    ui->btnAnalyzeProduction->setEnabled(false);
    ui->btnAnalyzeProduction->setText("⏳ Analyse IA en cours...");
    ui->anomalyTable->setRowCount(0);
    ui->anomalyExplicationText->setText(
        "⏳ L'IA analyse toutes les productions...\n"
        "Merci de patienter quelques secondes.");
    detectionProd.analyser(seuil);
}

void MainWindow::onPredictionPrete(const ResultatPrediction &resultat)
{
    ui->btnPredictProduction->setEnabled(true);
    ui->btnPredictProduction->setText("🔮 Prédire");
    if (resultat.rendementPredit <= 0.0) {
        ui->valuePredRendement->setText("N/A");
        ui->valuePredHuile->setText("Huile estimée : N/A");
        ui->predExplicationText->setText(resultat.explication);
        return;
    }
    ui->valuePredRendement->setText(
        QString::number(resultat.rendementPredit, 'f', 2) + " %");
    ui->valuePredHuile->setText(
        QString("Huile estimée : %1 L").arg(QString::number(resultat.huileEstimee, 'f', 2)));
    ui->predExplicationText->setText(resultat.explication);
}

void MainWindow::onPredectionErreur(const QString &message)
{
    ui->btnPredictProduction->setEnabled(true);
    ui->btnPredictProduction->setText("🔮 Prédire");
    ui->valuePredRendement->setText("Erreur");
    ui->valuePredHuile->setText("---");
    ui->predExplicationText->setText("❌ Erreur : " + message);
}

void MainWindow::onAnalyseTerminee(const QList<ResultatDetection> &resultats)
{
    ui->btnAnalyzeProduction->setEnabled(true);
    ui->btnAnalyzeProduction->setText("🔍 Analyser");

    if (resultats.isEmpty()) return;

    ui->anomalyTable->setColumnCount(6);
    ui->anomalyTable->setHorizontalHeaderLabels(
        {"ID", "Date", "Rendement (%)", "Écart (%)", "Statut", "Notifier"});
    ui->anomalyTable->setRowCount(0);

    int row = 0;
    for (const ResultatDetection &r : resultats) {
        ui->anomalyTable->insertRow(row);

        ui->anomalyTable->setItem(row, 0, new QTableWidgetItem(QString::number(r.id)));
        ui->anomalyTable->setItem(row, 1, new QTableWidgetItem(r.date.toString("dd/MM/yyyy")));
        ui->anomalyTable->setItem(row, 2, new QTableWidgetItem(QString::number(r.rendement, 'f', 2) + " %"));
        ui->anomalyTable->setItem(row, 3, new QTableWidgetItem(QString::number(r.ecart, 'f', 2) + " %"));

        QTableWidgetItem *statutItem = new QTableWidgetItem(r.statut);
        statutItem->setTextAlignment(Qt::AlignCenter);
        statutItem->setForeground(r.estAnomalie ? QColor("#dc3545") : QColor("#28a745"));
        ui->anomalyTable->setItem(row, 4, statutItem);

        QTableWidgetItem *notifItem = new QTableWidgetItem(r.notifAffichee);
        notifItem->setTextAlignment(Qt::AlignCenter);
        if (r.notifAffichee == "oui") {
            notifItem->setForeground(QColor("#28a745"));
            QFont f = notifItem->font(); f.setBold(true); notifItem->setFont(f);
        } else if (r.notifAffichee == "non") {
            notifItem->setForeground(QColor("#fd7e14"));
            QFont f = notifItem->font(); f.setBold(true); notifItem->setFont(f);
        }
        ui->anomalyTable->setItem(row, 5, notifItem);

        for (int col = 0; col < 6; ++col)
            if (ui->anomalyTable->item(row, col))
                ui->anomalyTable->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        ++row;
    }
    ui->anomalyTable->resizeColumnsToContents();
}

void MainWindow::onDetectionExplicationPrete(const QString &explication)
{
    ui->anomalyExplicationText->setText(explication);
}

void MainWindow::onDetectionErreur(const QString &message)
{
    ui->btnAnalyzeProduction->setEnabled(true);
    ui->btnAnalyzeProduction->setText("🔍 Analyser");
    ui->anomalyTable->setRowCount(0);
    ui->anomalyExplicationText->setText("❌ Erreur : " + message);
}

// =============================================================================
//  PARTENAIRE
// =============================================================================

void MainWindow::chargerPartenaires()
{
    Partenaire p;
    remplirTablePartenaires(p.afficherTous());
}

void MainWindow::remplirTablePartenaires(const QList<Partenaire> &liste)
{
    QTableWidget *table = ui->partnersTable;
    table->setRowCount(0);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"ID", "Nom", "Email", "Téléphone", "Investissement", "Employé ID"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row = 0;
    for (const Partenaire &p : liste) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(p.getId())));
        table->setItem(row, 1, new QTableWidgetItem(p.getNom()));
        table->setItem(row, 2, new QTableWidgetItem(p.getEmail()));
        table->setItem(row, 3, new QTableWidgetItem(p.getTelephone()));
        table->setItem(row, 4, new QTableWidgetItem(p.getInvestissement()));
        table->setItem(row, 5, new QTableWidgetItem(p.getIdEmploye() > 0 ? QString::number(p.getIdEmploye()) : "-"));
        ++row;
    }
    table->resizeColumnsToContents();
}

void MainWindow::chargerEmployesComboBox()
{
    ui->employeComboBox->clear();
    ui->employeComboBox->addItem("-- Aucun --", 0);
    const auto employes = Partenaire::listerEmployes();
    for (const auto &emp : employes)
        ui->employeComboBox->addItem(emp.second, emp.first);
}

void MainWindow::viderFormulairePartenaire()
{
    ui->namepartenaireLineEdit->clear();
    ui->emailpartenaireLineEdit->clear();
    ui->phonepartenaireLineEdit->clear();
    ui->investissementpartenaireLineEdit->clear();
    ui->searchpartenaireLineEdit->clear();
    ui->employeComboBox->setCurrentIndex(0);
}

int MainWindow::idPartenaireSelectionne()
{
    QList<QTableWidgetItem*> sel = ui->partnersTable->selectedItems();
    if (sel.isEmpty()) return -1;
    int row = sel.first()->row();
    QTableWidgetItem *idItem = ui->partnersTable->item(row, 0);
    return idItem ? idItem->text().toInt() : -1;
}

bool MainWindow::validerEmail(const QString &email)
{
    if (email.isEmpty()) return true;
    QRegularExpression re(R"(^[a-zA-Z0-9._%+\-]+@[a-zA-Z0-9.\-]+\.[a-zA-Z]{2,}$)");
    return re.match(email).hasMatch();
}

bool MainWindow::validerTelephone(const QString &telephone)
{
    if (telephone.isEmpty()) return true;
    QRegularExpression re(R"(^\+?[0-9\s\-]{7,15}$)");
    return re.match(telephone).hasMatch();
}

void MainWindow::on_partnersTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;
    int row = item->row();
    ui->namepartenaireLineEdit->setText(ui->partnersTable->item(row, 1)->text());
    ui->emailpartenaireLineEdit->setText(ui->partnersTable->item(row, 2)->text());
    ui->phonepartenaireLineEdit->setText(ui->partnersTable->item(row, 3)->text());
    ui->investissementpartenaireLineEdit->setText(ui->partnersTable->item(row, 4)->text());
    QString idEmpStr = ui->partnersTable->item(row, 5)->text();
    int idEmp = (idEmpStr == "-") ? 0 : idEmpStr.toInt();
    for (int i = 0; i < ui->employeComboBox->count(); ++i) {
        if (ui->employeComboBox->itemData(i).toInt() == idEmp) {
            ui->employeComboBox->setCurrentIndex(i);
            break;
        }
    }
}

void MainWindow::on_addpartenaireButton_clicked()
{
    QString nom = ui->namepartenaireLineEdit->text().trimmed();
    QString email = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel = ui->phonepartenaireLineEdit->text().trimmed();
    QString investissement = ui->investissementpartenaireLineEdit->text().trimmed();
    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir Nom, Email et Téléphone."); return;
    }
    if (!validerEmail(email)) { QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide."); return; }
    if (!validerTelephone(tel)) { QMessageBox::warning(this, "Téléphone invalide", "Veuillez entrer un numéro de téléphone valide."); return; }
    int idEmploye = ui->employeComboBox->currentData().toInt();
    Partenaire p(0, nom, email, investissement, tel, idEmploye);
    if (p.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Partenaire ajouté avec succès !");
        chargerPartenaires(); viderFormulairePartenaire();
    } else QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le partenaire.");
}

void MainWindow::on_updatepartenaireButton_clicked()
{
    int id = idPartenaireSelectionne();
    if (id == -1) { QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un partenaire dans le tableau."); return; }
    QString nom = ui->namepartenaireLineEdit->text().trimmed();
    QString email = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel = ui->phonepartenaireLineEdit->text().trimmed();
    QString investissement = ui->investissementpartenaireLineEdit->text().trimmed();
    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty()) { QMessageBox::warning(this, "Champs manquants", "Veuillez remplir Nom, Email et Téléphone."); return; }
    if (!validerEmail(email)) { QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide."); return; }
    if (!validerTelephone(tel)) { QMessageBox::warning(this, "Téléphone invalide", "Veuillez entrer un numéro de téléphone valide."); return; }
    int idEmploye = ui->employeComboBox->currentData().toInt();
    Partenaire p(id, nom, email, investissement, tel, idEmploye);
    if (p.modifier()) {
        QMessageBox::information(this, "Succès", "✅ Partenaire modifié avec succès !");
        chargerPartenaires(); viderFormulairePartenaire();
    } else QMessageBox::critical(this, "Erreur", "Impossible de modifier le partenaire.");
}

void MainWindow::on_deletepartenaireButton_clicked()
{
    int id = idPartenaireSelectionne();
    if (id == -1) { QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un partenaire dans le tableau."); return; }
    auto reply = QMessageBox::question(this, "Confirmation", "Confirmer la suppression de ce partenaire ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Partenaire p; p.setId(id);
        if (p.supprimer()) {
            QMessageBox::information(this, "Succès", "✅ Partenaire supprimé !");
            chargerPartenaires(); viderFormulairePartenaire();
        } else QMessageBox::critical(this, "Erreur", "Impossible de supprimer le partenaire.");
    }
}

void MainWindow::on_filterpartenaireButton_clicked()
{
    remplirTablePartenaires(FiltrePartenaire::trierParInvestissementDecroissant());
}

void MainWindow::on_exportpartenaireButton_clicked()
{
    Partenaire p;
    ExporterPartenaire::exporterEnPDF(this, p.afficherTous());
}

void MainWindow::on_searchpartenaireButton_clicked()
{
    on_searchpartenaireLineEdit_textChanged(ui->searchpartenaireLineEdit->text());
}

void MainWindow::on_searchpartenaireLineEdit_textChanged(const QString &text)
{
    QString term = text.trimmed().toLower();
    if (term.isEmpty()) { chargerPartenaires(); return; }
    Partenaire p;
    QList<Partenaire> filtered;
    for (const Partenaire &pt : p.afficherTous())
        if (pt.getNom().toLower().contains(term) || pt.getTelephone().contains(term))
            filtered.append(pt);
    remplirTablePartenaires(filtered);
}

void MainWindow::on_tabWidgetPartenaire_currentChanged(int index)
{
    if (index == 1) {
        statPartenaire.calculerEtAfficher(ui->valueTotalPartenaires, ui->valueActifs, ui->investissementChartView);
    } else if (index == 2) {
        ui->mailingPartenairesListWidget->clear();
        for (const Partenaire &p : mailing.chargerPartenaires()) {
            QListWidgetItem *item = new QListWidgetItem(p.getNom() + "  <" + p.getEmail() + ">", ui->mailingPartenairesListWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, p.getId());
        }
    } else if (index == 3) {
        ui->reunionPartenairesListWidget->clear();
        for (const Partenaire &p : mailing.chargerPartenaires()) {
            QListWidgetItem *item = new QListWidgetItem(p.getNom() + "  <" + p.getEmail() + ">", ui->reunionPartenairesListWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setData(Qt::UserRole, p.getId());
        }
        ui->reunionCalendar->setSelectedDate(QDate::currentDate());
    }
}

void MainWindow::on_sendMailButton_clicked()
{
    QList<Partenaire> selectionnes;
    QList<Partenaire> tous = mailing.chargerPartenaires();
    for (int i = 0; i < ui->mailingPartenairesListWidget->count(); ++i) {
        QListWidgetItem *item = ui->mailingPartenairesListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            int id = item->data(Qt::UserRole).toInt();
            for (const Partenaire &p : tous) if (p.getId() == id) { selectionnes << p; break; }
        }
    }
    if (selectionnes.isEmpty()) { QMessageBox::warning(this, "Aucun destinataire", "Veuillez cocher au moins un partenaire."); return; }
    QString sujet = ui->subjectLineEdit->text().trimmed();
    QString message = ui->messageTextEdit->toPlainText().trimmed();
    if (sujet.isEmpty()) { QMessageBox::warning(this, "Sujet vide", "Veuillez saisir un sujet."); return; }
    if (message.isEmpty()) { QMessageBox::warning(this, "Message vide", "Veuillez saisir un message."); return; }
    QStringList echoues;
    int nb = mailing.envoyerEmailMultiple(selectionnes, sujet, message, echoues);
    if (echoues.isEmpty())
        QMessageBox::information(this, "Succès", QString("✅ %1 email(s) envoyé(s) avec succès !").arg(nb));
    else
        QMessageBox::warning(this, "Résultat partiel", QString("✅ %1 envoyé(s). ❌ Échecs :\n%2").arg(nb).arg(echoues.join("\n")));
    ui->subjectLineEdit->clear();
    ui->messageTextEdit->clear();
    for (int i = 0; i < ui->mailingPartenairesListWidget->count(); ++i)
        ui->mailingPartenairesListWidget->item(i)->setCheckState(Qt::Unchecked);
}

void MainWindow::on_reunionSendButton_clicked()
{
    QList<Partenaire> selectionnes;
    QList<Partenaire> tous = mailing.chargerPartenaires();
    for (int i = 0; i < ui->reunionPartenairesListWidget->count(); ++i) {
        QListWidgetItem *item = ui->reunionPartenairesListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            int id = item->data(Qt::UserRole).toInt();
            for (const Partenaire &p : tous) if (p.getId() == id) { selectionnes << p; break; }
        }
    }
    if (selectionnes.isEmpty()) { QMessageBox::warning(this, "Aucun invité", "Veuillez cocher au moins un partenaire à inviter."); return; }
    QDate date = ui->reunionCalendar->selectedDate();
    QTime heure = ui->reunionTimeEdit->time();
    QString lieu = ui->reunionLieuLineEdit->text().trimmed();
    QString objet = ui->reunionObjetTextEdit->toPlainText().trimmed();
    if (objet.isEmpty()) { QMessageBox::warning(this, "Objet vide", "Veuillez saisir l'objet de la réunion."); return; }
    QString sujet = QString("Invitation à une réunion — %1").arg(date.toString("dd/MM/yyyy"));
    QString message = QString("Bonjour,\n\nVous êtes invité(e) à une réunion organisée par ZitTech.\n\n📅 Date    : %1\n🕐 Heure   : %2\n%3📝 Objet   : %4\n\nMerci de confirmer votre présence.\n\nCordialement,\nZitTech Gestion")
                          .arg(date.toString("dddd dd MMMM yyyy")).arg(heure.toString("HH:mm"))
                          .arg(lieu.isEmpty() ? "" : QString("📍 Lieu    : %1\n").arg(lieu)).arg(objet);
    QStringList echoues;
    int nb = mailing.envoyerEmailMultiple(selectionnes, sujet, message, echoues);
    if (echoues.isEmpty())
        QMessageBox::information(this, "Invitations envoyées", QString("✅ %1 invitation(s) envoyée(s) avec succès !").arg(nb));
    else
        QMessageBox::warning(this, "Résultat partiel", QString("✅ %1 envoyée(s). ❌ Échecs :\n%2").arg(nb).arg(echoues.join("\n")));
    ui->reunionObjetTextEdit->clear();
    ui->reunionLieuLineEdit->clear();
    for (int i = 0; i < ui->reunionPartenairesListWidget->count(); ++i)
        ui->reunionPartenairesListWidget->item(i)->setCheckState(Qt::Unchecked);
}

// =============================================================================
//  CHATBOT
// =============================================================================

void MainWindow::on_chatbotSendButton_clicked()
{
    QString message = ui->chatbotInputLineEdit->text().trimmed();
    if (message.isEmpty()) return;
    ui->chatbotDisplayArea->append("<b style='color:#2d4a1f;'>Vous :</b> " + message.toHtmlEscaped());
    ui->chatbotInputLineEdit->clear();
    ui->chatbotSendButton->setEnabled(false);
    ui->chatbotSendButton->setText("⏳ En attente...");
    chatbot.envoyerMessage(message);
}

void MainWindow::onChatbotReponse(const QString &reponse)
{
    ui->chatbotDisplayArea->append("<b style='color:#b8860b;'>🤖 ChatBot :</b> " + reponse.toHtmlEscaped());
    ui->chatbotDisplayArea->append("");
    ui->chatbotSendButton->setEnabled(true);
    ui->chatbotSendButton->setText("📤 Envoyer");
    ui->chatbotInputLineEdit->setFocus();
}

void MainWindow::onChatbotErreur(const QString &erreur)
{
    ui->chatbotDisplayArea->append("<span style='color:#dc3545;'>⚠️ Erreur : " + erreur.toHtmlEscaped() + "</span>");
    ui->chatbotSendButton->setEnabled(true);
    ui->chatbotSendButton->setText("📤 Envoyer");
}

// =============================================================================
//  CLIENT
// =============================================================================

void MainWindow::refreshClientTable()
{
    clientObj.afficher(ui->clientTable);
}

void MainWindow::clearFormClient()
{
    selectedClientId = -1;
    ui->inputNomClient->clear();
    ui->inputPrenomClient->clear();
    ui->inputEmailClient->clear();
    ui->inputTelephoneClient->clear();
    ui->inputTypeClient->setCurrentIndex(0);
    ui->inputFeedbackClient->clear();
}

int MainWindow::idClientSelectionne()
{
    QList<QTableWidgetItem*> sel = ui->clientTable->selectedItems();
    if (sel.isEmpty()) return -1;
    int row = sel.first()->row();
    QTableWidgetItem *idItem = ui->clientTable->item(row, 0);
    return idItem ? idItem->text().toInt() : -1;
}

void MainWindow::on_clientTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;
    int row = item->row();
    selectedClientId = ui->clientTable->item(row, 0)->text().toInt();
    ui->inputNomClient->setText(ui->clientTable->item(row, 1)->text());
    ui->inputPrenomClient->setText(ui->clientTable->item(row, 2)->text());
    ui->inputEmailClient->setText(ui->clientTable->item(row, 3)->text());
    ui->inputTelephoneClient->setText(ui->clientTable->item(row, 4)->text());
    QString typeText = ui->clientTable->item(row, 5)->text();
    int idx = ui->inputTypeClient->findText(typeText);
    ui->inputTypeClient->setCurrentIndex(idx != -1 ? idx : 0);
    ui->inputFeedbackClient->setText(ui->clientTable->item(row, 6)->text());
}

void MainWindow::on_btnAddClient_clicked()
{
    QString nom = ui->inputNomClient->text().trimmed();
    QString prenom = ui->inputPrenomClient->text().trimmed();
    QString email = ui->inputEmailClient->text().trimmed();
    QString telephone = ui->inputTelephoneClient->text().trimmed();
    QString typeClient = ui->inputTypeClient->currentText();
    QString avis = ui->inputFeedbackClient->toPlainText().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) { QMessageBox::warning(this, "Champs manquants", "Veuillez remplir le nom et le prénom du client."); return; }
    if (!validerEmail(email)) { QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide."); return; }
    if (!validerTelephone(telephone)) { QMessageBox::warning(this, "Téléphone invalide", "Veuillez entrer un numéro de téléphone valide."); return; }
    Client c(0, nom, prenom, email, telephone, typeClient, avis);
    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Client ajouté avec succès !"); refreshClientTable(); clearFormClient();
    } else QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
}

void MainWindow::on_btnUpdateClient_clicked()
{
    if (selectedClientId == -1) { QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un client dans le tableau."); return; }
    QString nom = ui->inputNomClient->text().trimmed();
    QString prenom = ui->inputPrenomClient->text().trimmed();
    QString email = ui->inputEmailClient->text().trimmed();
    QString telephone = ui->inputTelephoneClient->text().trimmed();
    QString typeClient = ui->inputTypeClient->currentText();
    QString avis = ui->inputFeedbackClient->toPlainText().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) { QMessageBox::warning(this, "Champs manquants", "Veuillez remplir le nom et le prénom du client."); return; }
    if (!validerEmail(email)) { QMessageBox::warning(this, "Email invalide", "Veuillez entrer une adresse email valide."); return; }
    if (!validerTelephone(telephone)) { QMessageBox::warning(this, "Téléphone invalide", "Veuillez entrer un numéro de téléphone valide."); return; }
    Client c(selectedClientId, nom, prenom, email, telephone, typeClient, avis);
    if (c.modifier()) {
        QMessageBox::information(this, "Succès", "✅ Client modifié avec succès !"); refreshClientTable(); clearFormClient();
    } else QMessageBox::critical(this, "Erreur", "Impossible de modifier le client.");
}

void MainWindow::on_btnDeleteClient_clicked()
{
    if (selectedClientId == -1) { QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un client dans le tableau."); return; }
    auto reply = QMessageBox::question(this, "Confirmation", "Confirmer la suppression de ce client ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Client c; c.setId(selectedClientId);
        if (c.supprimer()) { QMessageBox::information(this, "Succès", "✅ Client supprimé !"); refreshClientTable(); clearFormClient(); }
        else QMessageBox::critical(this, "Erreur", "Impossible de supprimer le client.");
    }
}

void MainWindow::on_btnRefreshClient_clicked()
{
    ui->searchBoxClient->clear(); clearFormClient(); ui->clientTable->clearSelection(); refreshClientTable();
}

void MainWindow::on_btnSearchClient_clicked()
{
    QString term = ui->searchBoxClient->text().trimmed();
    if (term.isEmpty()) { refreshClientTable(); return; }
    ClientRecherche recherche;
    recherche.rechercherParNom(ui->clientTable, term);
}

void MainWindow::on_btnClearClient_clicked()
{
    clearFormClient(); ui->searchBoxClient->clear(); ui->clientTable->clearSelection(); ui->searchBoxClient->setFocus();
}

void MainWindow::on_btnExportClientPDF_clicked()
{
    QList<Client> clients = clientObj.afficherTous();
    if (clients.isEmpty()) { QMessageBox::warning(this, "Export PDF", "Aucun client à exporter."); return; }
    QString chemin = QFileDialog::getSaveFileName(this, "Exporter les clients en PDF",
                                                  "clients_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".pdf", "Fichiers PDF (*.pdf)");
    if (chemin.isEmpty()) return;
    if (!chemin.endsWith(".pdf", Qt::CaseInsensitive)) chemin += ".pdf";
    ClientExport exporter;
    exporter.exporterPDF(ui->clientTable, chemin);
    QMessageBox::information(this, "Export PDF", QString("Export terminé !\nFichier : %1").arg(chemin));
}

void MainWindow::on_btnTriClient_clicked()
{
    QMenu menu(this);
    menu.addAction("Par nom (A-Z)", [this]() { afficherClientsTable(ClientTri::trierParNom(clientObj.afficherTous(), true)); });
    menu.addAction("Par nom (Z-A)", [this]() { afficherClientsTable(ClientTri::trierParNom(clientObj.afficherTous(), false)); });
    menu.addAction("Par type client", [this]() { afficherClientsTable(ClientTri::trierParTypeClient(clientObj.afficherTous())); });
    menu.addAction("Par volume d'achat", [this]() { afficherClientsTable(ClientTri::trierParVolumeAchat()); });
    menu.addAction("Réinitialiser", [this]() { refreshClientTable(); });
    menu.exec(QCursor::pos());
}

void MainWindow::chargerGraphiquesStatsClients()
{
    auto clearLayout = [](QLayout *lay) {
        if (!lay) return;
        while (QLayoutItem *it = lay->takeAt(0)) { if (QWidget *w = it->widget()) w->deleteLater(); delete it; }
    };
    clearLayout(ui->verticalLayoutClientStatsType);
    clearLayout(ui->verticalLayoutClientStatsVolume);
    clearLayout(ui->verticalLayoutClientStatsEvolution);
    ClientStat stats;
    if (QChartView *v1 = stats.creerGraphiqueTypeClient()) ui->verticalLayoutClientStatsType->addWidget(v1, 1);
    if (QChartView *v2 = stats.creerGraphiqueVolumeAchat()) ui->verticalLayoutClientStatsVolume->addWidget(v2, 1);
    if (QChartView *v3 = stats.creerGraphiqueEvolutionMensuelle()) ui->verticalLayoutClientStatsEvolution->addWidget(v3, 1);
}

void MainWindow::on_tabWidgetClient_currentChanged(int index)
{
    if (index == 1) chargerGraphiquesStatsClients();
}

void MainWindow::on_btnHistoriqueClient_clicked()
{
    QList<QTableWidgetItem *> sel = ui->clientTable->selectedItems();
    if (sel.isEmpty()) { QMessageBox::warning(this, QStringLiteral("Historique d'achat"), QStringLiteral("Veuillez sélectionner un client dans le tableau.")); return; }
    const int row = sel.first()->row();
    QTableWidget *tbl = ui->clientTable;
    const int id = tbl->item(row, 0)->text().toInt();
    const QString nom    = tbl->item(row, 1) ? tbl->item(row, 1)->text() : QString();
    const QString prenom = tbl->item(row, 2) ? tbl->item(row, 2)->text() : QString();
    const QString type   = tbl->item(row, 5) ? tbl->item(row, 5)->text() : QString();
    QDialog dlg(this); dlg.setWindowTitle(QStringLiteral("Historique d'achat")); dlg.resize(980, 640);
    auto *mainL = new QVBoxLayout(&dlg); mainL->setContentsMargins(0,0,0,0); mainL->setSpacing(0);
    auto *banner = new QLabel(QStringLiteral("\U0001F4CB Historique d'achat — %1 %2").arg(nom, prenom));
    banner->setStyleSheet(QStringLiteral("background:#2d4a1f;color:white;padding:14px 20px;font-size:15px;font-weight:bold;")); mainL->addWidget(banner);
    auto *sub = new QLabel(QStringLiteral("Client ID : %1 | Type : %2").arg(id).arg(type));
    sub->setStyleSheet(QStringLiteral("background:#dff0d8;color:#2d4a1f;padding:8px 20px;")); mainL->addWidget(sub);
    auto *tabs = new QTabWidget;
    tabs->setStyleSheet(QStringLiteral("QTabWidget::pane{border:1px solid #5d732c;}QTabBar::tab{background:#dff0d8;padding:10px 16px;font-weight:bold;}QTabBar::tab:selected{background:#2d4a1f;color:white;}"));
    auto *tableAchats = new QTableWidget; tableAchats->setEditTriggers(QAbstractItemView::NoEditTriggers); tableAchats->setSelectionBehavior(QAbstractItemView::SelectRows);
    ClientHistorique hist; hist.afficherHistoriqueAchats(id, tableAchats);
    tabs->addTab(tableAchats, QStringLiteral("\U0001F4CB Liste des achats"));
    auto *resume = new QTextEdit; resume->setReadOnly(true); hist.afficherResumeAchats(id, resume);
    tabs->addTab(resume, QStringLiteral("\U0001F4CA Résumé")); mainL->addWidget(tabs, 1);
    auto *formFrame = new QFrame;
    formFrame->setStyleSheet(QStringLiteral("QFrame{background:#f8faf5;border-top:1px solid #5d732c;border-bottom:1px solid #c5d4a8;}QLabel#histFormTitle{font-weight:bold;color:#2d4a1f;}"));
    auto *formOuter = new QVBoxLayout(formFrame); formOuter->setContentsMargins(16,12,16,12); formOuter->setSpacing(8);
    auto *formTitle = new QLabel(QStringLiteral("Nouvel achat pour ce client")); formTitle->setObjectName(QStringLiteral("histFormTitle")); formOuter->addWidget(formTitle);
    auto *pathLbl = new QLabel(QStringLiteral("Carnet partagé :\n%1").arg(ClientHistorique::cheminFichierAchatsExternes()));
    pathLbl->setStyleSheet(QStringLiteral("color:#555;font-size:11px;")); pathLbl->setWordWrap(true); formOuter->addWidget(pathLbl);
    auto *formGrid = new QHBoxLayout; formGrid->setSpacing(10);
    auto *dateEdit = new QDateEdit(QDate::currentDate()); dateEdit->setCalendarPopup(true); dateEdit->setDisplayFormat(QStringLiteral("dd/MM/yyyy"));
    auto *produitEdit = new QLineEdit; produitEdit->setPlaceholderText(QStringLiteral("Ex. Huile extra vierge 5 L"));
    auto *spinQte = new QDoubleSpinBox; spinQte->setRange(0.01,1.0e7); spinQte->setDecimals(2); spinQte->setSuffix(QStringLiteral(" kg")); spinQte->setValue(1.0);
    auto *spinPu = new QDoubleSpinBox; spinPu->setRange(0.0,1.0e7); spinPu->setDecimals(2); spinPu->setSuffix(QStringLiteral(" DT")); spinPu->setValue(0.0);
    auto *labelTotal = new QLabel(QStringLiteral("0.00 DT")); labelTotal->setStyleSheet(QStringLiteral("font-weight:bold;color:#1b5e20;"));
    auto *labelSaison = new QLabel(ClientHistorique::saisonDepuisDate(dateEdit->date())); labelSaison->setStyleSheet(QStringLiteral("color:#2e7d32;"));
    auto addField = [&](const QString &t, QWidget *w) { auto *vb=new QVBoxLayout; auto *lb=new QLabel(t); lb->setStyleSheet(QStringLiteral("color:#555;font-size:11px;")); vb->addWidget(lb); vb->addWidget(w); formGrid->addLayout(vb,1); };
    addField(QStringLiteral("Date d'achat"),dateEdit); addField(QStringLiteral("Produit"),produitEdit); addField(QStringLiteral("Quantité"),spinQte); addField(QStringLiteral("Prix unitaire"),spinPu); addField(QStringLiteral("Total (auto)"),labelTotal); addField(QStringLiteral("Saison (auto)"),labelSaison);
    formOuter->addLayout(formGrid); mainL->addWidget(formFrame);
    auto refreshFormCalc = [=]() { labelTotal->setText(QStringLiteral("%1 DT").arg(spinQte->value()*spinPu->value(),0,'f',2)); labelSaison->setText(ClientHistorique::saisonDepuisDate(dateEdit->date())); };
    QObject::connect(spinQte, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &dlg, refreshFormCalc);
    QObject::connect(spinPu,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), &dlg, refreshFormCalc);
    QObject::connect(dateEdit, &QDateEdit::dateChanged, &dlg, refreshFormCalc);
    refreshFormCalc();
    auto *btnRow=new QHBoxLayout; btnRow->addStretch();
    auto *btnPdf=new QPushButton(QStringLiteral("\U0001F4C4 Exporter PDF")); btnPdf->setStyleSheet(QStringLiteral("background:#2d4a1f;color:white;padding:10px 18px;border-radius:6px;font-weight:bold;"));
    auto *btnAjouter=new QPushButton(QStringLiteral("➕ Ajouter")); btnAjouter->setStyleSheet(QStringLiteral("background:#ffd700;color:#2d4a1f;padding:10px 18px;border-radius:6px;font-weight:bold;border:2px solid #5d732c;"));
    auto *btnClose=new QPushButton(QStringLiteral("✖ Fermer")); btnClose->setStyleSheet(QStringLiteral("background:#2d4a1f;color:white;padding:10px 18px;border-radius:6px;font-weight:bold;"));
    btnRow->addWidget(btnPdf); btnRow->addWidget(btnAjouter); btnRow->addWidget(btnClose); mainL->addLayout(btnRow);
    QObject::connect(btnClose, &QPushButton::clicked, &dlg, &QDialog::accept);
    QObject::connect(btnPdf, &QPushButton::clicked, &dlg, [id,&dlg]() {
        QString chemin=QFileDialog::getSaveFileName(&dlg,QStringLiteral("Exporter l'historique en PDF"),QStringLiteral("historique_client_%1_%2.pdf").arg(id).arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")),QStringLiteral("Fichiers PDF (*.pdf)"));
        if(chemin.isEmpty())return; if(!chemin.endsWith(".pdf",Qt::CaseInsensitive))chemin+=".pdf";
        ClientPrevision exporteur; exporteur.exporterHistoriquePDF(id,chemin,&dlg);
    });
    QObject::connect(btnAjouter, &QPushButton::clicked, &dlg, [&]() {
        QString err;
        if(!hist.insererAchat(id,dateEdit->date(),produitEdit->text(),spinQte->value(),spinPu->value(),&err)){QMessageBox::warning(&dlg,QStringLiteral("Ajout impossible"),err);return;}
        hist.afficherHistoriqueAchats(id,tableAchats); hist.afficherResumeAchats(id,resume);
        produitEdit->clear(); spinQte->setValue(1.0); spinPu->setValue(0.0); dateEdit->setDate(QDate::currentDate()); refreshFormCalc();
    });
    dlg.exec();
}

void MainWindow::on_btnPrevisionClient_clicked()
{
    QDialog dlg(this); dlg.setWindowTitle(QStringLiteral("Prévisions de demande")); dlg.resize(1020, 720);
    auto *mainL=new QVBoxLayout(&dlg); mainL->setContentsMargins(0,0,0,0); mainL->setSpacing(0);
    auto *banner=new QLabel(QStringLiteral("✨ Prévisions de demande — ZitTech"));
    banner->setStyleSheet(QStringLiteral("background:#2d4a1f;color:white;padding:14px 20px;font-size:15px;font-weight:bold;")); mainL->addWidget(banner);
    const QString campagneCourante=ClientHistorique::campagneOleicoleAnnee(QDate::currentDate());
    const QString campagneSuivante=ClientHistorique::campagneOleicoleAnneeSuivante(campagneCourante);
    const QLocale fr(QLocale::French,QLocale::France);
    const QString moisProchain=fr.toString(QDate::currentDate().addMonths(1),QStringLiteral("MMMM yyyy"));
    auto *info=new QLabel; info->setWordWrap(true); info->setTextFormat(Qt::RichText);
    info->setText(QStringLiteral("<p><b>Campagne en cours :</b> %1</p><p><b>Campagne suivante projetée :</b> %2</p><p>Point d'attention : <b>%3</b></p>").arg(campagneCourante,campagneSuivante,moisProchain));
    info->setStyleSheet(QStringLiteral("background:#dff0d8;color:#2d4a1f;padding:14px 22px;font-size:13px;")); mainL->addWidget(info);
    ClientPrevision prev; QChartView *chart=prev.creerGraphiqueDeuxCampagnes();
    auto *scroll=new QScrollArea; scroll->setWidgetResizable(true); scroll->setFrameShape(QFrame::NoFrame);
    auto *chartHolder=new QWidget; auto *chartLay=new QVBoxLayout(chartHolder); chartLay->setContentsMargins(8,8,8,8); chartLay->addWidget(chart); scroll->setWidget(chartHolder); mainL->addWidget(scroll,1);
    auto *btnRow=new QHBoxLayout; btnRow->addStretch();
    auto *btnClose=new QPushButton(QStringLiteral("✖ Fermer")); btnClose->setStyleSheet(QStringLiteral("background:#2d4a1f;color:white;padding:10px 18px;border-radius:6px;font-weight:bold;"));
    btnRow->addWidget(btnClose); mainL->addLayout(btnRow);
    QObject::connect(btnClose,&QPushButton::clicked,&dlg,&QDialog::accept);
    dlg.exec();
}

void MainWindow::afficherClientsTable(const QList<Client> &clients)
{
    QTableWidget *table = ui->clientTable; table->setRowCount(0);
    int row = 0;
    for (const Client &c : clients) {
        table->insertRow(row);
        table->setItem(row,0,new QTableWidgetItem(QString::number(c.getId())));
        table->setItem(row,1,new QTableWidgetItem(c.getNom()));
        table->setItem(row,2,new QTableWidgetItem(c.getPrenom()));
        table->setItem(row,3,new QTableWidgetItem(c.getEmail()));
        table->setItem(row,4,new QTableWidgetItem(c.getTelephone()));
        table->setItem(row,5,new QTableWidgetItem(c.getTypeClient()));
        table->setItem(row,6,new QTableWidgetItem(c.getAvis()));
        row++;
    }
    table->resizeColumnsToContents();
}

// =============================================================================
//  EMPLOYÉ
// =============================================================================

void MainWindow::chargerEmployes() { EmployeSearch::chargerTout(ui->employeTable); }

void MainWindow::viderFormulaireEmploye()
{
    ui->inputIdEmploye->clear();
    ui->inputNomEmploye->clear();
    ui->inputPrenomEmploye->clear();
    ui->inputPosteEmploye->setCurrentIndex(0);
    ui->inputSalaireEmploye->setValue(0);
    ui->inputDateEmbaucheEmploye->setDate(QDate::currentDate()); // ← date système
}

void MainWindow::chargerStatistiquesEmployes()
{
    // ── Cacher les widgets du haut ────────────────────────────
    ui->statsLabelEmploye->setVisible(false);
    ui->cardTotalEmployes->setVisible(false);
    ui->cardOuvriers->setVisible(false);
    ui->cardTechniciens->setVisible(false);

    // ── Supprimer tous les spacers du layout ──────────────────
    QLayout *mainLay = ui->employeStatsTab->layout();
    if (mainLay) {
        for (int i = mainLay->count() - 1; i >= 0; i--) {
            QLayoutItem *item = mainLay->itemAt(i);
            if (item && item->spacerItem()) {
                mainLay->removeItem(item);
                delete item;
            }
        }
    }

    // ── Créer ou récupérer les onglets de graphiques ──────────
    QTabWidget *statTabs = ui->employeStatsTab->findChild<QTabWidget*>("statTabsEmploye");

    if (!statTabs) {
        statTabs = new QTabWidget(ui->employeStatsTab);
        statTabs->setObjectName("statTabsEmploye");
        statTabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        statTabs->setStyleSheet(
            "QTabWidget::pane { border: 2px solid #5d732c; border-radius: 8px; background: white; }"
            "QTabBar::tab { background: #dff0d8; color: #2d4a1f; padding: 10px 22px; "
            "               margin-right: 4px; border-top-left-radius: 6px; "
            "               border-top-right-radius: 6px; font-weight: bold; }"
            "QTabBar::tab:selected { background: #2d4a1f; color: white; }"
            "QTabBar::tab:hover:!selected { background: #c5e1a5; }");

        if (mainLay)
            mainLay->addWidget(statTabs);
    }

    while (statTabs->count() > 0)
        statTabs->removeTab(0);

    EmployeStats statsObj;

    QWidget *page1 = new QWidget;
    QVBoxLayout *l1 = new QVBoxLayout(page1);
    l1->setContentsMargins(4, 4, 4, 4);
    QChartView *chart1 = statsObj.creerGraphiqueRepartitionPostes();
    chart1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    l1->addWidget(chart1);
    statTabs->addTab(page1, "📊 Répartition par Poste");

    QWidget *page2 = new QWidget;
    QVBoxLayout *l2 = new QVBoxLayout(page2);
    l2->setContentsMargins(4, 4, 4, 4);
    QChartView *chart2 = statsObj.creerGraphiqueSalaires();
    chart2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    l2->addWidget(chart2);
    statTabs->addTab(page2, "💰 Salaires");

    QWidget *page3 = new QWidget;
    QVBoxLayout *l3 = new QVBoxLayout(page3);
    l3->setContentsMargins(4, 4, 4, 4);
    QChartView *chart3 = statsObj.creerGraphiqueAnciennete();
    chart3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    l3->addWidget(chart3);
    statTabs->addTab(page3, "📅 Ancienneté");
}

void MainWindow::on_btnAddEmploye_clicked()
{
    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();
    QString poste  = ui->inputPosteEmploye->currentText();

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir Nom et Prénom !");
        return;
    }

    Employe e(0, nom, prenom, poste,
              ui->inputSalaireEmploye->value(),
              ui->inputDateEmbaucheEmploye->date());

    if (poste == "Responsable") {

        QDialog dlgMdp(this);
        dlgMdp.setWindowTitle("Définir le mot de passe");
        dlgMdp.setFixedSize(420, 260);
        dlgMdp.setStyleSheet("background:white;");

        auto *vlay = new QVBoxLayout(&dlgMdp);
        vlay->setContentsMargins(30, 25, 30, 25);
        vlay->setSpacing(14);

        auto *title = new QLabel("🔐 Mot de passe pour ce Responsable");
        title->setStyleSheet("font-size:14px;font-weight:bold;color:#2d4a1f;");
        vlay->addWidget(title);

        auto *lblMdp = new QLabel("Mot de passe :");
        lblMdp->setStyleSheet("color:#2d4a1f;font-weight:bold;");
        vlay->addWidget(lblMdp);

        auto *edtMdp = new QLineEdit;
        edtMdp->setEchoMode(QLineEdit::Password);
        edtMdp->setPlaceholderText("Entrez le mot de passe...");
        edtMdp->setStyleSheet("padding:8px;border:2px solid #5d732c;border-radius:6px;");
        vlay->addWidget(edtMdp);

        auto *lblConf = new QLabel("Confirmer :");
        lblConf->setStyleSheet("color:#2d4a1f;font-weight:bold;");
        vlay->addWidget(lblConf);

        auto *edtConf = new QLineEdit;
        edtConf->setEchoMode(QLineEdit::Password);
        edtConf->setPlaceholderText("Confirmez le mot de passe...");
        edtConf->setStyleSheet("padding:8px;border:2px solid #5d732c;border-radius:6px;");
        vlay->addWidget(edtConf);

        auto *btnRow = new QHBoxLayout;
        auto *btnOk  = new QPushButton("✅ Valider");
        auto *btnAnn = new QPushButton("Annuler");
        btnOk->setStyleSheet(
            "background:#ffd700;color:#2d4a1f;border:none;"
            "padding:10px 20px;border-radius:6px;font-weight:bold;");
        btnAnn->setStyleSheet(
            "background:#dc3545;color:white;border:none;"
            "padding:10px 20px;border-radius:6px;font-weight:bold;");
        btnRow->addWidget(btnOk);
        btnRow->addWidget(btnAnn);
        vlay->addLayout(btnRow);

        connect(btnAnn, &QPushButton::clicked, &dlgMdp, &QDialog::reject);
        connect(btnOk,  &QPushButton::clicked, &dlgMdp, [&]() {
            if (edtMdp->text().length() < 4) {
                QMessageBox::warning(&dlgMdp, "MDP trop court",
                                     "Le mot de passe doit contenir au moins 4 caractères.");
                return;
            }
            if (edtMdp->text() != edtConf->text()) {
                QMessageBox::warning(&dlgMdp, "Erreur",
                                     "Les mots de passe ne correspondent pas.");
                edtConf->clear(); edtConf->setFocus();
                return;
            }
            dlgMdp.accept();
        });

        if (dlgMdp.exec() != QDialog::Accepted)
            return;

        QString mdp = edtMdp->text();

        if (!e.ajouterAvecMdp(mdp)) {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du responsable !");
            return;
        }

        int newId = e.getLastInsertedId();
        QString username = QString("resp_%1").arg(nom.toLower().remove(' '));

        QDialog dlgInfo(this);
        dlgInfo.setWindowTitle("Compte Responsable créé");
        dlgInfo.setFixedSize(460, 300);
        dlgInfo.setStyleSheet("background:white;");

        auto *vl2 = new QVBoxLayout(&dlgInfo);
        vl2->setContentsMargins(30, 25, 30, 25);
        vl2->setSpacing(12);

        auto *ico = new QLabel("✅  Responsable ajouté avec succès !");
        ico->setStyleSheet("font-size:14px;font-weight:bold;color:#2d4a1f;");
        vl2->addWidget(ico);

        auto *sep = new QFrame;
        sep->setFrameShape(QFrame::HLine);
        sep->setStyleSheet("color:#5d732c;");
        vl2->addWidget(sep);

        auto addRow = [&](const QString &lbl, const QString &val) {
            auto *hl  = new QHBoxLayout;
            auto *lb  = new QLabel(lbl);
            lb->setStyleSheet("font-weight:bold;color:#2d4a1f;min-width:130px;");
            auto *vl  = new QLabel(val);
            vl->setStyleSheet(
                "background:#f0f7e8;border:2px solid #5d732c;"
                "border-radius:5px;padding:6px 12px;"
                "font-size:13px;font-weight:bold;color:#2d4a1f;");
            vl->setTextInteractionFlags(Qt::TextSelectableByMouse);
            hl->addWidget(lb);
            hl->addWidget(vl, 1);
            vl2->addLayout(hl);
        };

        addRow("🆔  ID Employé :", QString::number(newId));
        addRow("👤  Nom d'utilisateur :", username);
        addRow("🔒  Mot de passe :", mdp);

        auto *note = new QLabel(
            "ℹ️  Conservez ces informations. Ce responsable peut\n"
            "    maintenant se connecter via l'écran de login.");
        note->setStyleSheet("color:#666;font-size:11px;");
        vl2->addWidget(note);

        auto *btnFerm = new QPushButton("✖ Fermer");
        btnFerm->setStyleSheet(
            "background:#2d4a1f;color:white;border:none;"
            "padding:10px 24px;border-radius:6px;font-weight:bold;");
        connect(btnFerm, &QPushButton::clicked, &dlgInfo, &QDialog::accept);
        vl2->addWidget(btnFerm, 0, Qt::AlignRight);

        QSqlQuery qUser;
        qUser.prepare(
            "UPDATE EMPLOYE SET MDP=:mdp WHERE ID_EMPLOYE=:id");
        qUser.bindValue(":mdp", mdp);
        qUser.bindValue(":id", newId);
        qUser.exec();

        dlgInfo.exec();

    } else {
        if (e.ajouter()) {
            QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
            return;
        }
    }

    chargerEmployes();
    viderFormulaireEmploye();
}

void MainWindow::on_btnUpdateEmploye_clicked()
{
    QString idStr=ui->inputIdEmploye->text().trimmed();
    if(idStr.isEmpty()){QMessageBox::warning(this,"Erreur","Sélectionnez un employé dans le tableau !");return;}
    QString nom=ui->inputNomEmploye->text().trimmed(); QString prenom=ui->inputPrenomEmploye->text().trimmed();
    if(nom.isEmpty()||prenom.isEmpty()){QMessageBox::warning(this,"Erreur","Veuillez remplir Nom et Prénom !");return;}
    Employe e(idStr.toInt(),nom,prenom,ui->inputPosteEmploye->currentText(),ui->inputSalaireEmploye->value(),ui->inputDateEmbaucheEmploye->date());
    if(e.modifier()){QMessageBox::information(this,"Succès","Employé modifié avec succès !");chargerEmployes();viderFormulaireEmploye();}
    else QMessageBox::critical(this,"Erreur","Échec de la modification !");
}

void MainWindow::on_btnDeleteEmploye_clicked()
{
    QString idStr=ui->inputIdEmploye->text().trimmed();
    if(idStr.isEmpty()){QMessageBox::warning(this,"Erreur","Sélectionnez un employé dans le tableau !");return;}
    if(QMessageBox::question(this,"Confirmation","Voulez-vous vraiment supprimer cet employé ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
        Employe e;
        if(e.supprimer(idStr.toInt())){QMessageBox::information(this,"Succès","Employé supprimé !");chargerEmployes();viderFormulaireEmploye();}
        else QMessageBox::critical(this,"Erreur","Échec de la suppression !");
    }
}

void MainWindow::on_btnRefreshEmploye_clicked(){chargerEmployes();viderFormulaireEmploye();}

void MainWindow::on_employeTable_clicked(const QModelIndex &index)
{
    int row=index.row();
    ui->inputIdEmploye->setText(ui->employeTable->item(row,0)->text());
    ui->inputNomEmploye->setText(ui->employeTable->item(row,1)->text());
    ui->inputPrenomEmploye->setText(ui->employeTable->item(row,2)->text());
    int idx=ui->inputPosteEmploye->findText(ui->employeTable->item(row,3)->text());
    if(idx>=0)ui->inputPosteEmploye->setCurrentIndex(idx);
    ui->inputSalaireEmploye->setValue(ui->employeTable->item(row,4)->text().toInt());
    QDate date=QDate::fromString(ui->employeTable->item(row,5)->text(),"dd/MM/yyyy");
    if(date.isValid())ui->inputDateEmbaucheEmploye->setDate(date);
}

void MainWindow::on_btnTriEmploye_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->setStyleSheet(
        "QMenu { background-color: white; border: 2px solid #5d732c; border-radius: 6px; padding: 4px; }"
        "QMenu::item { padding: 10px 20px; font-size: 13px; color: #2d4a1f; font-weight: bold; }"
        "QMenu::item:selected { background-color: #ffd700; color: #2d4a1f; border-radius: 4px; }"
        "QMenu::separator { height: 1px; background: #5d732c; margin: 4px 8px; }");

    menu->addAction("Par nom (A-Z)", [this]() {
        afficherEmployesTable(EmployeTri::trierParNom(EmployeTri::chargerTousLesEmployes(), true));
    });
    menu->addAction("Par nom (Z-A)", [this]() {
        afficherEmployesTable(EmployeTri::trierParNom(EmployeTri::chargerTousLesEmployes(), false));
    });
    menu->addAction("Par prénom (A-Z)", [this]() {
        afficherEmployesTable(EmployeTri::trierParPrenom(EmployeTri::chargerTousLesEmployes(), true));
    });
    menu->addAction("Par poste", [this]() {
        afficherEmployesTable(EmployeTri::trierParPoste(EmployeTri::chargerTousLesEmployes()));
    });
    menu->addAction("Par salaire (↑ croissant)", [this]() {
        afficherEmployesTable(EmployeTri::trierParSalaire(EmployeTri::chargerTousLesEmployes(), true));
    });
    menu->addAction("Par salaire (↓ décroissant)", [this]() {
        afficherEmployesTable(EmployeTri::trierParSalaire(EmployeTri::chargerTousLesEmployes(), false));
    });
    menu->addAction("Par date d'embauche (↑)", [this]() {
        afficherEmployesTable(EmployeTri::trierParDateEmbauche(EmployeTri::chargerTousLesEmployes(), true));
    });
    menu->addAction("Par date d'embauche (↓)", [this]() {
        afficherEmployesTable(EmployeTri::trierParDateEmbauche(EmployeTri::chargerTousLesEmployes(), false));
    });
    menu->addSeparator();
    menu->addAction("🔄 Réinitialiser", [this]() { chargerEmployes(); });

    QPushButton *btn = qobject_cast<QPushButton*>(
        ui->employeListTab->findChild<QPushButton*>("btnTriEmploye"));
    if (btn)
        menu->exec(btn->mapToGlobal(btn->rect().bottomLeft()));
    else
        menu->exec(QCursor::pos());
}

void MainWindow::afficherEmployesTable(const QList<Employe> &employes)
{
    QTableWidget *table = ui->employeTable;
    table->setRowCount(0);
    int row = 0;
    for (const Employe &e : employes) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(e.getId())));
        table->setItem(row, 1, new QTableWidgetItem(e.getNom()));
        table->setItem(row, 2, new QTableWidgetItem(e.getPrenom()));
        table->setItem(row, 3, new QTableWidgetItem(e.getPoste()));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(e.getSalaire())));
        table->setItem(row, 5, new QTableWidgetItem(e.getDateEmbauche().toString("dd/MM/yyyy")));
        row++;
    }
    table->resizeColumnsToContents();
}

void MainWindow::on_btnSearchEmploye_clicked(){EmployeSearch::filtrer(ui->employeTable,ui->searchBoxEmploye->text().trimmed());}
void MainWindow::on_btnClearEmploye_clicked(){ui->searchBoxEmploye->clear();chargerEmployes();viderFormulaireEmploye();}
void MainWindow::on_searchBoxEmploye_textChanged(const QString &text){EmployeSearch::filtrer(ui->employeTable,text);}
void MainWindow::on_tabWidgetEmploye_currentChanged(int index){if(index==1)chargerStatistiquesEmployes();}
void MainWindow::exporterEmployesPDF(){EmployePDF::exporter(ui->employeTable,this);}

// =============================================================================
//  MACHINE
// =============================================================================

void MainWindow::chargerMachines(){MachineSearch::chargerTout(ui->machineTable);}

void MainWindow::viderFormulaireMachine()
{
    ui->inputIdMachine->clear(); ui->inputTypeMachine->clear();
    ui->inputEtatMachine->setCurrentIndex(0);
    ui->inputDateMaintenance->setDate(QDate::currentDate());
    ui->inputDureeMachine->setValue(0);
}

void MainWindow::on_btnAddMachine_clicked()
{
    QString type=ui->inputTypeMachine->toPlainText().trimmed();
    if(type.isEmpty()){QMessageBox::warning(this,"Erreur","Veuillez saisir le type de la machine !");return;}
    Machine m(0,type,ui->inputEtatMachine->currentText(),ui->inputDateMaintenance->date(),ui->inputDureeMachine->value());
    if(m.ajouter()){QMessageBox::information(this,"Succès","Machine ajoutée avec succès !");chargerMachines();viderFormulaireMachine();}
    else QMessageBox::critical(this,"Erreur","Échec de l'ajout de la machine !");
}

void MainWindow::on_btnUpdateMachine_clicked()
{
    QString idStr=ui->inputIdMachine->text().trimmed();
    if(idStr.isEmpty()){QMessageBox::warning(this,"Erreur","Sélectionnez une machine dans le tableau !");return;}
    QString type=ui->inputTypeMachine->toPlainText().trimmed();
    if(type.isEmpty()){QMessageBox::warning(this,"Erreur","Veuillez saisir le type de la machine !");return;}
    Machine m(idStr.toInt(),type,ui->inputEtatMachine->currentText(),ui->inputDateMaintenance->date(),ui->inputDureeMachine->value());
    if(m.modifier()){QMessageBox::information(this,"Succès","Machine modifiée avec succès !");chargerMachines();viderFormulaireMachine();}
    else QMessageBox::critical(this,"Erreur","Échec de la modification de la machine !");
}

void MainWindow::on_btnDeleteMachine_clicked()
{
    QString idStr=ui->inputIdMachine->text().trimmed();
    if(idStr.isEmpty()){QMessageBox::warning(this,"Erreur","Sélectionnez une machine dans le tableau !");return;}
    if(QMessageBox::question(this,"Confirmation","Voulez-vous vraiment supprimer cette machine ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
        Machine m;
        if(m.supprimer(idStr.toInt())){QMessageBox::information(this,"Succès","Machine supprimée !");chargerMachines();viderFormulaireMachine();}
        else QMessageBox::critical(this,"Erreur","Échec de la suppression de la machine !");
    }
}

void MainWindow::on_btnRefreshMachine_clicked(){chargerMachines();viderFormulaireMachine();}

void MainWindow::on_machineTable_clicked(const QModelIndex &index)
{
    int row=index.row();
    ui->inputIdMachine->setText(ui->machineTable->item(row,0)->text());
    ui->inputTypeMachine->setText(ui->machineTable->item(row,1)->text());
    int idx=ui->inputEtatMachine->findText(ui->machineTable->item(row,2)->text());
    if(idx>=0)ui->inputEtatMachine->setCurrentIndex(idx);
    QDate date=QDate::fromString(ui->machineTable->item(row,3)->text(),"dd/MM/yyyy");
    if(date.isValid())ui->inputDateMaintenance->setDate(date);
    ui->inputDureeMachine->setValue(ui->machineTable->item(row,4)->text().toInt());
}

void MainWindow::on_btnSearchMachine_clicked(){MachineSearch::filtrer(ui->machineTable,ui->searchBoxMachine->text().trimmed());}
void MainWindow::on_btnClearMachine_clicked(){ui->searchBoxMachine->clear();chargerMachines();viderFormulaireMachine();}
void MainWindow::on_searchBoxMachine_textChanged(const QString &text){MachineSearch::filtrer(ui->machineTable,text);}

void MainWindow::on_btnExportMachinePDF_clicked()
{
    MachinePDF::exporter(ui->machineTable, this);
}

void MainWindow::on_btnTriMachine_clicked()
{
    QMenu menu(this);
    menu.addAction("Par ID (A-Z)", [this]() { MachineTri::trierParId(ui->machineTable, true); });
    menu.addAction("Par ID (Z-A)", [this]() { MachineTri::trierParId(ui->machineTable, false); });
    menu.addAction("Par type", [this]() { MachineTri::trierParType(ui->machineTable, true); });
    menu.addAction("Par état", [this]() { MachineTri::trierParEtat(ui->machineTable, true); });
    menu.addAction("Par date maintenance", [this]() { MachineTri::trierParDateMaintenance(ui->machineTable, true); });
    menu.addAction("Par durée", [this]() { MachineTri::trierParDuree(ui->machineTable, true); });
    menu.addAction("Réinitialiser", [this]() { chargerMachines(); });
    menu.exec(QCursor::pos());
}

void MainWindow::exporterMachinesPDF(){MachinePDF::exporter(ui->machineTable,this);}

// =============================================================================
//  JUMEAU NUMÉRIQUE (Digital Twin)
// =============================================================================

void MainWindow::on_btnDiagnosticMachine_clicked()
{
    if (!jumeau) return;
    ui->stackedWidget->setCurrentWidget(jumeau);
    jumeau->loadMachines();
    QModelIndexList sel = ui->machineTable->selectionModel()->selectedRows();
    if (!sel.isEmpty()) {
        int row = sel.first().row();
        QTableWidgetItem *idItem = ui->machineTable->item(row, 0);
        if (idItem)
            jumeau->selectMachine(idItem->text().toInt());
    }
}

// =============================================================================
//  RFID / ARDUINO
// =============================================================================

void MainWindow::on_btnConnectArduino_clicked()
{
    if (!rfidManager) return;

    // Liste les ports disponibles
    QStringList ports = rfidManager->availablePorts();

    if (ports.isEmpty()) {
        QMessageBox::warning(this, "❌ Aucun port",
                             "Aucun port série détecté.\n"
                             "Vérifiez que l'Arduino est bien branché en USB.");
        return;
    }

    // Dialogue de sélection du port
    QDialog dlg(this);
    dlg.setWindowTitle("Connexion Arduino");
    dlg.setFixedSize(360, 200);
    dlg.setStyleSheet("background:white;");

    auto *vlay = new QVBoxLayout(&dlg);
    vlay->setContentsMargins(24, 20, 24, 20);
    vlay->setSpacing(12);

    auto *title = new QLabel("🔌 Sélectionnez le port de l'Arduino");
    title->setStyleSheet("font-size:13px;font-weight:bold;color:#2d4a1f;");
    vlay->addWidget(title);

    auto *combo = new QComboBox;
    combo->addItems(ports);
    combo->setStyleSheet("padding:8px;border:2px solid #5d732c;border-radius:6px;");
    vlay->addWidget(combo);

    auto *btnRow = new QHBoxLayout;
    auto *btnOk  = new QPushButton("✅ Connecter");
    auto *btnAnn = new QPushButton("Annuler");
    btnOk->setStyleSheet(
        "background:#2d4a1f;color:white;border:none;"
        "padding:10px 20px;border-radius:6px;font-weight:bold;");
    btnAnn->setStyleSheet(
        "background:#6c757d;color:white;border:none;"
        "padding:10px 20px;border-radius:6px;font-weight:bold;");
    btnRow->addWidget(btnOk);
    btnRow->addWidget(btnAnn);
    vlay->addLayout(btnRow);

    connect(btnAnn, &QPushButton::clicked, &dlg, &QDialog::reject);
    connect(btnOk,  &QPushButton::clicked, &dlg, &QDialog::accept);

    if (dlg.exec() != QDialog::Accepted) return;

    QString portChoisi = combo->currentText();

    if (rfidManager->connectToArduino(portChoisi)) {
        QMessageBox::information(this, "✅ Connecté",
                                 "Arduino connecté sur " + portChoisi + " !\n"
                                                                        "Le scanner RFID est maintenant actif.");
    } else {
        QMessageBox::critical(this, "❌ Échec",
                              "Impossible de se connecter sur " + portChoisi + ".\n"
                                                                               "Vérifiez que le port n'est pas utilisé par un autre programme.");
    }
}
