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

// ── Stock module ──────────────────────────────────────────────
#include "stock.h"
#include "recherche.h"
#include "exportpdf.h"
#include "statistiques.h"
#include "estimation.h"

// ── Production module ─────────────────────────────────────────
#include "production.h"
#include "Statproduction.h"
#include "Pdfproduction.h"

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

// ── Machine module ────────────────────────────────────────────
#include "machine.h"
#include "machine_search.h"
#include "machine_pdf.h"

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

    // ── Production ────────────────────────────────────────────
    // FIX: dedicated slot replaces the two inline lambdas so that
    //      blockSignals() in clearFormProduction() can suppress it.
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
    void on_btnPredictProduction_clicked();
    void on_btnAnalyzeProduction_clicked();

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

    // ── Machine ───────────────────────────────────────────────
    void on_btnAddMachine_clicked();
    void on_btnUpdateMachine_clicked();
    void on_btnDeleteMachine_clicked();
    void on_btnRefreshMachine_clicked();
    void on_machineTable_clicked(const QModelIndex &index);
    void on_btnSearchMachine_clicked();
    void on_btnClearMachine_clicked();
    void on_searchBoxMachine_textChanged(const QString &text);
    void exporterMachinesPDF();

private:
    Ui::MainWindow *ui;
    QSqlDatabase    db;

    // ── Stock managers ────────────────────────────────────────
    Stock         *stockManager        = nullptr;
    Recherche     *rechercheManager    = nullptr;
    ExportPDF     *exportPDFManager    = nullptr;
    Statistiques  *statistiquesManager = nullptr;
    Estimation    *estimationManager   = nullptr;
    int            selectedStockId     = -1;

    void clearFormStock();
    void refreshStockTable();

    // ── Production objects ────────────────────────────────────
    Production     prod;
    StatProduction stat;
    PdfProduction  pdfProd;

    void refreshProductionTable();
    void clearFormProduction();   // uses blockSignals — see .cpp

    // ── Partenaire helpers ────────────────────────────────────
    void chargerPartenaires();
    void chargerEmployesComboBox();
    void remplirTablePartenaires(const QList<Partenaire> &liste);
    void viderFormulairePartenaire();
    int  idPartenaireSelectionne();
    Mailing mailing;
    ChatBot chatbot;

    StatistiquePartenaire statPartenaire;

    // ── Client helpers ────────────────────────────────────────
    Client clientObj;
    int    selectedClientId = -1;

    void refreshClientTable();
    void clearFormClient();
    int  idClientSelectionne();
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
    void afficherClientsTable(const QList<Client> &clients);

    // ── Employé helpers ───────────────────────────────────────
    Employe emp;

    void chargerEmployes();
    void viderFormulaireEmploye();
    void chargerStatistiquesEmployes();

    // ── Machine helpers ───────────────────────────────────────
    Machine mach;

    void chargerMachines();
    void viderFormulaireMachine();
};

#endif // MAINWINDOW_H
