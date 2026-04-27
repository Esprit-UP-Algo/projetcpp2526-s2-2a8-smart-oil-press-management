#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QRegularExpression>
#include <QMenu>
#include <QCursor>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

// ── Stock module ──────────────────────────────────────────────
#include "stock.h"
#include "recherche.h"
#include "exportpdf.h"
#include "statistiques.h"
#include "estimation.h"
#include "voicematieres.h"           // ← Module commande vocale stock

// ── Production module ─────────────────────────────────────────
#include "production.h"
#include "Statproduction.h"
#include "Pdfproduction.h"
#include "detectionprod.h"
#include "predectionprod.h"
#include "filterproduction.h"
#include "rechproduction.h"

// ── Arduino integration (Production module) ───────────────────
#include "arduino_zittech.h"   // Arduino Uno — anomaly notification

// ── Partenaire module ─────────────────────────────────────────
#include "partenaire.h"
#include "filtrepartenaire.h"
#include "exporterpartenaire.h"
#include "statistique_partenaire.h"
#include "mailing.h"
#include "chatbot.h"

// ── Client module ─────────────────────────────────────────────
#include "client.h"
#include "client_tri.h"
#include "client_recherche.h"
#include "client_export.h"
#include "client_stat.h"
#include "client_historique.h"
#include "client_prevision.h"

// ── Employé module ────────────────────────────────────────────
#include "employe.h"
#include "employe_search.h"
#include "employe_stats.h"
#include "employe_pdf.h"
#include "employe_tri.h"

// ── Machine module ────────────────────────────────────────────
#include "machine.h"
#include "machine_search.h"
#include "machine_pdf.h"

// ── Jumeau Numérique (Digital Twin) ───────────────────────────
#include "jumeaunumerique.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDatabase(const QSqlDatabase &database);

private slots:

    // ── LOGIN ─────────────────────────────────────────────────
    void onLoginClicked();
    void onForgotPasswordClicked();
    void onResetPasswordClicked();
    void onReturnToLoginClicked();

    // ── Navigation ────────────────────────────────────────────
    void on_btnEmploye_clicked();
    void on_btnClient_clicked();
    void on_btnStock_clicked();
    void on_btnMachine_clicked();
    void on_btnProduction_clicked();
    void on_btnPartenaire_clicked();

    // ── Stock ─────────────────────────────────────────────────
    void on_stockTable_itemClicked(QTableWidgetItem *item);
    void on_btnAddStock_clicked();
    void on_btnUpdateStock_clicked();
    void on_btnDeleteStock_clicked();
    void on_btnRefreshStock_clicked();
    void on_btnSearchStock_clicked();
    void on_btnClearStock_clicked();
    void on_btnExportStockPDF_clicked();
    void on_tabWidgetStock_currentChanged(int index);
    void on_btnCalculerEstimation_clicked();
    void on_btnVocalStock_clicked();         // ← Slot pour le bouton vocal stock

    // ── Production ────────────────────────────────────────────
    void updateRendementDisplay();
    void on_productionTable_itemClicked(QTableWidgetItem *item);
    void on_btnAddProduction_clicked();
    void on_btnUpdateProduction_clicked();
    void on_btnDeleteProduction_clicked();
    void on_btnRefreshProduction_clicked();
    void on_btnSearchProduction_clicked();
    void on_btnClearProduction_clicked();
    void on_btnExportPDFProduction_clicked();
    void on_tabWidget_currentChanged(int index);

    // ── Production AI ─────────────────────────────────────────
    void on_btnPredictProduction_clicked();
    void on_btnAnalyzeProduction_clicked();
    void onAnalyseTerminee(const QList<ResultatDetection> &resultats);
    void onDetectionExplicationPrete(const QString &explication);
    void onDetectionErreur(const QString &message);
    void onPredictionPrete(const ResultatPrediction &resultat);
    void onPredectionErreur(const QString &message);

    // ── Production Arduino ────────────────────────────────────
    void onArduinoIdConfirmed(int confirmedId);
    void onArduinoIdInvalid(int typedId);
    void onArduinoSerialError(const QString &message);

    // ── Partenaire ────────────────────────────────────────────
    void on_partnersTable_itemClicked(QTableWidgetItem *item);
    void on_addpartenaireButton_clicked();
    void on_updatepartenaireButton_clicked();
    void on_deletepartenaireButton_clicked();
    void on_searchpartenaireButton_clicked();
    void on_searchpartenaireLineEdit_textChanged(const QString &text);
    void on_filterpartenaireButton_clicked();
    void on_exportpartenaireButton_clicked();
    void on_tabWidgetPartenaire_currentChanged(int index);
    void on_sendMailButton_clicked();
    void on_reunionSendButton_clicked();

    // ── ChatBot ───────────────────────────────────────────────
    void on_chatbotSendButton_clicked();
    void onChatbotReponse(const QString &reponse);
    void onChatbotErreur(const QString &erreur);

    // ── Client ────────────────────────────────────────────────
    void on_clientTable_itemClicked(QTableWidgetItem *item);
    void on_btnAddClient_clicked();
    void on_btnUpdateClient_clicked();
    void on_btnDeleteClient_clicked();
    void on_btnRefreshClient_clicked();
    void on_btnSearchClient_clicked();
    void on_btnClearClient_clicked();
    void on_btnExportClientPDF_clicked();
    void on_btnTriClient_clicked();
    void on_btnHistoriqueClient_clicked();
    void on_btnPrevisionClient_clicked();
    void on_tabWidgetClient_currentChanged(int index);

    // ── Employé ───────────────────────────────────────────────
    void on_btnAddEmploye_clicked();
    void on_btnUpdateEmploye_clicked();
    void on_btnDeleteEmploye_clicked();
    void on_btnRefreshEmploye_clicked();
    void on_employeTable_clicked(const QModelIndex &index);
    void on_btnSearchEmploye_clicked();
    void on_btnClearEmploye_clicked();
    void on_searchBoxEmploye_textChanged(const QString &text);
    void on_tabWidgetEmploye_currentChanged(int index);
    void exporterEmployesPDF();
    void on_btnTriEmploye_clicked();
    void afficherEmployesTable(const QList<Employe> &employes);

    // ── Machine ───────────────────────────────────────────────
    void on_btnAddMachine_clicked();
    void on_btnUpdateMachine_clicked();
    void on_btnDeleteMachine_clicked();
    void on_btnRefreshMachine_clicked();
    void on_machineTable_clicked(const QModelIndex &index);
    void on_btnSearchMachine_clicked();
    void on_btnClearMachine_clicked();
    void on_searchBoxMachine_textChanged(const QString &text);
    void on_btnTriMachine_clicked();
    void on_btnExportMachinePDF_clicked();
    void exporterMachinesPDF();

    // ── Jumeau Numérique ──────────────────────────────────────
    void on_btnDiagnosticMachine_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase    db;

    // ── Login helpers ─────────────────────────────────────────
    bool validateLogin(const QString &username, const QString &password);
    bool validatePasswordReset(const QString &username,
                               const QString &newPassword,
                               const QString &confirmPassword);
    void clearLoginFields();
    void clearResetFields();
    void applyLoginStyles();
    void showMessage(const QString &title,
                     const QString &message,
                     QMessageBox::Icon icon);

    // ── Stock managers ────────────────────────────────────────
    Stock         *stockManager        = nullptr;
    Recherche     *rechercheManager    = nullptr;
    ExportPDF     *exportPDFManager    = nullptr;
    Statistiques  *statistiquesManager = nullptr;
    Estimation    *estimationManager   = nullptr;
    VoiceMatieres *voiceStock          = nullptr;  // ← Manager vocal stock
    int            selectedStockId     = -1;

    void clearFormStock();
    void refreshStockTable();

    // ── Production ────────────────────────────────────────────
    Production       prod;
    StatProduction   stat;
    PdfProduction    pdfProd;
    DetectionProd    detectionProd;
    PredectionProd   predectionProd;
    FilterProduction filterProd;
    RechProduction   rechProd;

    // ── Arduino (Production module) ───────────────────────────
    ArduinoZitTech arduinoZitTech;

    void sendAnomalyIdsToArduino(const QList<ResultatDetection> &resultats);
    bool updateNotifInDatabase(int productionId);
    void refreshNotifCellInTable(int productionId);

    void refreshProductionTable();
    void clearFormProduction();

    // ── Partenaire ────────────────────────────────────────────
    Mailing               mailing;
    ChatBot               chatbot;
    StatistiquePartenaire statPartenaire;

    void chargerPartenaires();
    void chargerEmployesComboBox();
    void remplirTablePartenaires(const QList<Partenaire> &liste);
    void viderFormulairePartenaire();
    int  idPartenaireSelectionne();

    // ── Client ────────────────────────────────────────────────
    Client clientObj;
    int    selectedClientId = -1;

    void refreshClientTable();
    void clearFormClient();
    int  idClientSelectionne();
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    void afficherClientsTable(const QList<Client> &clients);
    void chargerGraphiquesStatsClients();

    // ── Employé ───────────────────────────────────────────────
    Employe emp;

    void chargerEmployes();
    void viderFormulaireEmploye();
    void chargerStatistiquesEmployes();

    // ── Machine ───────────────────────────────────────────────
    Machine mach;

    void chargerMachines();
    void viderFormulaireMachine();

    // ── Jumeau Numérique (Digital Twin) ───────────────────────
    JumauNumerique *jumeau = nullptr;
};

#endif // MAINWINDOW_H
