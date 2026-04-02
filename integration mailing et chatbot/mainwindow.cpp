#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QDateTime>
#include <QPushButton>

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
    connect(ui->btnAddStock,           &QPushButton::clicked, this, &MainWindow::on_btnAddStock_clicked);
    connect(ui->btnUpdateStock,        &QPushButton::clicked, this, &MainWindow::on_btnUpdateStock_clicked);
    connect(ui->btnDeleteStock,        &QPushButton::clicked, this, &MainWindow::on_btnDeleteStock_clicked);
    connect(ui->btnRefreshStock,       &QPushButton::clicked, this, &MainWindow::on_btnRefreshStock_clicked);
    connect(ui->btnSearchStock,        &QPushButton::clicked, this, &MainWindow::on_btnSearchStock_clicked);
    connect(ui->btnClearStock,         &QPushButton::clicked, this, &MainWindow::on_btnClearStock_clicked);
    connect(ui->btnExportStockPDF,     &QPushButton::clicked, this, &MainWindow::on_btnExportStockPDF_clicked);
    connect(ui->btnCalculerEstimation, &QPushButton::clicked, this, &MainWindow::on_btnCalculerEstimation_clicked);

    connect(ui->stockTable,     &QTableWidget::itemClicked,  this, &MainWindow::on_stockTable_itemClicked);
    connect(ui->searchBoxStock, &QLineEdit::returnPressed,   this, &MainWindow::on_btnSearchStock_clicked);
    connect(ui->tabWidgetStock, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetStock_currentChanged);

    // =========================================================
    //  Production connections
    // =========================================================
    connect(ui->btnAddProduction,       &QPushButton::clicked, this, &MainWindow::on_btnAddProduction_clicked);
    connect(ui->btnUpdateProduction,    &QPushButton::clicked, this, &MainWindow::on_btnUpdateProduction_clicked);
    connect(ui->btnDeleteProduction,    &QPushButton::clicked, this, &MainWindow::on_btnDeleteProduction_clicked);
    connect(ui->btnRefreshProduction,   &QPushButton::clicked, this, &MainWindow::on_btnRefreshProduction_clicked);
    connect(ui->btnSearchProduction,    &QPushButton::clicked, this, &MainWindow::on_btnSearchProduction_clicked);
    connect(ui->btnClearProduction,     &QPushButton::clicked, this, &MainWindow::on_btnClearProduction_clicked);
    connect(ui->btnExportPDFProduction, &QPushButton::clicked, this, &MainWindow::on_btnExportPDFProduction_clicked);
    connect(ui->btnPredictProduction,   &QPushButton::clicked, this, &MainWindow::on_btnPredictProduction_clicked);
    connect(ui->btnAnalyzeProduction,   &QPushButton::clicked, this, &MainWindow::on_btnAnalyzeProduction_clicked);

    connect(ui->productionTable, &QTableWidget::itemClicked,  this, &MainWindow::on_productionTable_itemClicked);
    connect(ui->tabWidget,       &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

    // ─────────────────────────────────────────────────────────
    // FIX: rendement auto-calculation
    // We use a dedicated slot (updateRendementDisplay) instead
    // of lambdas so that blockSignals() in clearFormProduction()
    // actually suppresses these during form reset.
    // ─────────────────────────────────────────────────────────
    connect(ui->inputQuantiteOlive,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateRendementDisplay);

    connect(ui->inputQuantiteHuile,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateRendementDisplay);

    // =========================================================
    //  Partenaire connections
    // =========================================================
    connect(ui->addpartenaireButton,    &QPushButton::clicked, this, &MainWindow::on_addpartenaireButton_clicked);
    connect(ui->updatepartenaireButton, &QPushButton::clicked, this, &MainWindow::on_updatepartenaireButton_clicked);
    connect(ui->deletepartenaireButton, &QPushButton::clicked, this, &MainWindow::on_deletepartenaireButton_clicked);
    connect(ui->searchpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_searchpartenaireButton_clicked);
    connect(ui->filterpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_filterpartenaireButton_clicked);
    connect(ui->exportpartenaireButton, &QPushButton::clicked, this, &MainWindow::on_exportpartenaireButton_clicked);

    connect(ui->partnersTable,            &QTableWidget::itemClicked,  this, &MainWindow::on_partnersTable_itemClicked);
    connect(ui->searchpartenaireLineEdit, &QLineEdit::returnPressed,   this, &MainWindow::on_searchpartenaireButton_clicked);
    connect(ui->searchpartenaireLineEdit, &QLineEdit::textChanged,     this, &MainWindow::on_searchpartenaireLineEdit_textChanged);
    connect(ui->tabWidgetPartenaire,      &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetPartenaire_currentChanged);
    connect(ui->sendMailButton, &QPushButton::clicked,this, &MainWindow::on_sendMailButton_clicked);

    // ── ChatBot connections ───────────────────────────────────────────────────
    connect(ui->chatbotSendButton, &QPushButton::clicked,
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
    connect(ui->btnAddClient,       &QPushButton::clicked, this, &MainWindow::on_btnAddClient_clicked);
    connect(ui->btnUpdateClient,    &QPushButton::clicked, this, &MainWindow::on_btnUpdateClient_clicked);
    connect(ui->btnDeleteClient,    &QPushButton::clicked, this, &MainWindow::on_btnDeleteClient_clicked);
    connect(ui->btnRefreshClient,   &QPushButton::clicked, this, &MainWindow::on_btnRefreshClient_clicked);
    connect(ui->btnSearchClient,    &QPushButton::clicked, this, &MainWindow::on_btnSearchClient_clicked);
    connect(ui->btnClearClient,     &QPushButton::clicked, this, &MainWindow::on_btnClearClient_clicked);
    connect(ui->btnExportClientPDF, &QPushButton::clicked, this, &MainWindow::on_btnExportClientPDF_clicked);
    connect(ui->btnTriClient,       &QPushButton::clicked, this, &MainWindow::on_btnTriClient_clicked);

    connect(ui->clientTable,     &QTableWidget::itemClicked,  this, &MainWindow::on_clientTable_itemClicked);
    connect(ui->searchBoxClient, &QLineEdit::returnPressed,   this, &MainWindow::on_btnSearchClient_clicked);
    connect(ui->tabWidgetClient, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidgetClient_currentChanged);

    // =========================================================
    //  Employé connections
    // =========================================================
    connect(ui->btnAddEmploye,     &QPushButton::clicked, this, &MainWindow::on_btnAddEmploye_clicked);
    connect(ui->btnUpdateEmploye,  &QPushButton::clicked, this, &MainWindow::on_btnUpdateEmploye_clicked);
    connect(ui->btnDeleteEmploye,  &QPushButton::clicked, this, &MainWindow::on_btnDeleteEmploye_clicked);
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
    connect(ui->btnAddMachine,     &QPushButton::clicked, this, &MainWindow::on_btnAddMachine_clicked);
    connect(ui->btnUpdateMachine,  &QPushButton::clicked, this, &MainWindow::on_btnUpdateMachine_clicked);
    connect(ui->btnDeleteMachine,  &QPushButton::clicked, this, &MainWindow::on_btnDeleteMachine_clicked);
    connect(ui->btnRefreshMachine, &QPushButton::clicked, this, &MainWindow::on_btnRefreshMachine_clicked);

    connect(ui->machineTable,     &QTableWidget::clicked,  this, &MainWindow::on_machineTable_clicked);
    connect(ui->searchBoxMachine, &QLineEdit::textChanged, this, &MainWindow::on_searchBoxMachine_textChanged);

    QPushButton *exportMachineBtn = ui->machineListTab->findChild<QPushButton*>("exportButton");
    if (exportMachineBtn)
        connect(exportMachineBtn, &QPushButton::clicked, this, &MainWindow::exporterMachinesPDF);

    // =========================================================
    //  Initial state
    // =========================================================
    ui->stackedWidget->setCurrentWidget(ui->pageProduction);
    ui->inputDate->setDate(QDate::currentDate());

    chargerEmployes();
    chargerMachines();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────────────────────
//  setDatabase — called from main() after DB is open
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setDatabase(const QSqlDatabase &database)
{
    this->db            = database;
    stockManager        = new Stock(db, this);
    rechercheManager    = new Recherche(db, this);
    exportPDFManager    = new ExportPDF(this);
    statistiquesManager = new Statistiques(db, this);
    estimationManager   = new Estimation(db, this);

    refreshProductionTable();
    refreshClientTable();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Navigation stubs
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::on_btnEmploye_clicked()    {}
void MainWindow::on_btnClient_clicked()     {}
void MainWindow::on_btnStock_clicked()      {}
void MainWindow::on_btnMachine_clicked()    {}
void MainWindow::on_btnProduction_clicked() {}
void MainWindow::on_btnPartenaire_clicked() {}

// ═════════════════════════════════════════════════════════════════════════════
//  STOCK
// ═════════════════════════════════════════════════════════════════════════════

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
            ui->valueTotalStocks,
            ui->valueAlertStocks,
            ui->valueTotalQuantite,
            ui->valueMoyenneQuantite,
            ui->valueStockMax,
            ui->valueStockMin,
            ui->valueNbOrigines,
            ui->valueStockCritique
            );
    }
    else if (index == 2 && estimationManager) {
        estimationManager->calculerEstimation(
            ui->spinTauxRendement->value(),
            ui->tableEstimation,
            ui->valueTotalOlives,
            ui->valueHuileEstimee,
            ui->valueRendementMoyen,
            ui->valueStocksInsuffisants
            );
    }
}

void MainWindow::on_btnCalculerEstimation_clicked()
{
    if (!estimationManager) return;
    double taux = ui->spinTauxRendement->value();
    if (taux <= 0) {
        QMessageBox::warning(this, "Taux invalide",
                             "Le taux de rendement doit être supérieur à 0%.");
        return;
    }
    estimationManager->calculerEstimation(
        taux,
        ui->tableEstimation,
        ui->valueTotalOlives,
        ui->valueHuileEstimee,
        ui->valueRendementMoyen,
        ui->valueStocksInsuffisants
        );
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
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un stock dans le tableau pour le modifier.");
        return;
    }
    stockManager->updateStock(
        selectedStockId,
        ui->inputTypeStock->currentText(),
        ui->inputQuantiteStock->value(),
        ui->inputSeuilStock->value(),
        ui->inputOrigineStock->text().trimmed(),
        ui->stockTable);
    clearFormStock();
}

void MainWindow::on_btnDeleteStock_clicked()
{
    if (!stockManager) return;
    if (selectedStockId == -1) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un stock dans le tableau pour le supprimer.");
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
    rechercheManager->rechercherStock(
        ui->searchBoxStock->text().trimmed(),
        ui->stockTable);
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

// ═════════════════════════════════════════════════════════════════════════════
//  PRODUCTION
// ═════════════════════════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────────────────────────
// FIX: dedicated slot for rendement display update.
// This is connected to both spinboxes. blockSignals() in clearFormProduction()
// suppresses it during reset, preventing any spurious second insert.
// ─────────────────────────────────────────────────────────────────────────────
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

// ─────────────────────────────────────────────────────────────────────────────
// FIX: blockSignals on both spinboxes BEFORE resetting their values.
// This is the core fix — it prevents valueChanged from firing during
// the reset, which was causing the ghost second insert.
// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::clearFormProduction()
{
    prod.setId(0);

    // Block spinbox signals so the valueChanged → updateRendementDisplay chain
    // does NOT fire while we reset values to 0, preventing any accidental re-use
    // of stale prod data.
    ui->inputQuantiteOlive->blockSignals(true);
    ui->inputQuantiteHuile->blockSignals(true);

    ui->inputDate->setDate(QDate::currentDate());
    ui->inputQuantiteOlive->setValue(0.0);
    ui->inputQuantiteHuile->setValue(0.0);
    ui->inputRendement->clear();

    ui->inputQuantiteOlive->blockSignals(false);
    ui->inputQuantiteHuile->blockSignals(false);

    ui->productionTable->clearSelection();
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

    // Block signals while populating so the rendement lambda doesn't fire
    // with partial data (olive set but huile not yet)
    ui->inputQuantiteOlive->blockSignals(true);
    ui->inputQuantiteHuile->blockSignals(true);

    ui->inputQuantiteOlive->setValue(stripUnit(ui->productionTable->item(row, 2)->text()));
    ui->inputQuantiteHuile->setValue(stripUnit(ui->productionTable->item(row, 3)->text()));

    ui->inputQuantiteOlive->blockSignals(false);
    ui->inputQuantiteHuile->blockSignals(false);

    // Now update rendement display once with both values set correctly
    ui->inputRendement->setText(ui->productionTable->item(row, 4)->text());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        stat.calculerEtAfficher(
            ui->valueTotal,
            ui->valueOlives,
            ui->valueHuile,
            ui->valueRendement
            );
    }
}

void MainWindow::on_btnAddProduction_clicked()
{
    double olive = ui->inputQuantiteOlive->value();
    double huile = ui->inputQuantiteHuile->value();

    // ── Validation ───────────────────────────────────────────
    if (olive <= 0) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'olives doit être supérieure à 0.");
        return;
    }
    if (huile <= 0) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'huile doit être supérieure à 0.");
        return;
    }
    if (huile > olive) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'huile ne peut pas dépasser la quantité d'olives.");
        return;
    }

    // ── Apply density conversion and calculate rendement ─────
    double huileCorrigee = huile * 0.916;
    double rendement     = (huileCorrigee / olive) * 100.0;

    prod.setDateProd(ui->inputDate->date());
    prod.setQuantiteOlive(olive);
    prod.setQuantiteHuile(huileCorrigee);
    prod.setRendement(rendement);

    if (prod.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Production ajoutée avec succès !");
        refreshProductionTable();
        // FIX: clearFormProduction() uses blockSignals — safe to call here
        clearFormProduction();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter la production.");
    }
}

void MainWindow::on_btnUpdateProduction_clicked()
{
    if (prod.getId() == 0) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une production dans le tableau.");
        return;
    }

    double olive = ui->inputQuantiteOlive->value();
    double huile = ui->inputQuantiteHuile->value();

    if (olive <= 0) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'olives doit être supérieure à 0.");
        return;
    }
    if (huile <= 0) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'huile doit être supérieure à 0.");
        return;
    }
    if (huile > olive) {
        QMessageBox::warning(this, "Validation",
                             "La quantité d'huile ne peut pas dépasser la quantité d'olives.");
        return;
    }

    double huileCorrigee = huile * 0.916;
    double rendement     = (huileCorrigee / olive) * 100.0;

    prod.setDateProd(ui->inputDate->date());
    prod.setQuantiteOlive(olive);
    prod.setQuantiteHuile(huileCorrigee);
    prod.setRendement(rendement);

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
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner une production dans le tableau.");
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
    clearFormProduction();
    refreshProductionTable();
}

void MainWindow::on_btnSearchProduction_clicked()
{
    // Unhide all rows (search logic can be extended here)
    for (int row = 0; row < ui->productionTable->rowCount(); ++row)
        ui->productionTable->setRowHidden(row, false);
}

void MainWindow::on_btnClearProduction_clicked()
{
    for (int row = 0; row < ui->productionTable->rowCount(); ++row)
        ui->productionTable->setRowHidden(row, false);
    clearFormProduction();
}

void MainWindow::on_btnExportPDFProduction_clicked()
{
    pdfProd.exporterPDF(this);
}

void MainWindow::on_btnPredictProduction_clicked()
{
    double olive = ui->inputPredOlives->value();

    QSqlQuery q;
    q.exec("SELECT NVL(AVG(RENDEMENT), 0) FROM ZIT.PRODUCTION");
    double avgRend = 0.0;
    if (q.next()) avgRend = q.value(0).toDouble();

    double huileEstimee = olive * (avgRend / 100.0);

    ui->valuePredRendement->setText(QString::number(avgRend, 'f', 2) + "%");
    ui->valuePredHuile->setText(
        QString("Huile estimée : %1 L").arg(QString::number(huileEstimee, 'f', 2)));
}

void MainWindow::on_btnAnalyzeProduction_clicked()
{
    int threshold = ui->inputThreshold->value();

    QSqlQuery q;
    q.exec("SELECT NVL(AVG(RENDEMENT), 0) FROM ZIT.PRODUCTION");
    double avgRend = 0.0;
    if (q.next()) avgRend = q.value(0).toDouble();

    QSqlQuery q2;
    q2.exec("SELECT ID_PROD, DATE_PROD, RENDEMENT FROM ZIT.PRODUCTION ORDER BY ID_PROD");

    ui->anomalyTable->setRowCount(0);
    int row = 0;
    while (q2.next()) {
        double rend  = q2.value(2).toDouble();
        double ecart = qAbs(rend - avgRend);
        bool   isAno = ecart > threshold;

        ui->anomalyTable->insertRow(row);
        ui->anomalyTable->setItem(row, 0,
                                  new QTableWidgetItem(q2.value(0).toString()));
        ui->anomalyTable->setItem(row, 1,
                                  new QTableWidgetItem(
                                      q2.value(1).toDate().toString("dd/MM/yyyy")));
        ui->anomalyTable->setItem(row, 2,
                                  new QTableWidgetItem(
                                      QString::number(rend,  'f', 2) + " %"));
        ui->anomalyTable->setItem(row, 3,
                                  new QTableWidgetItem(
                                      QString::number(ecart, 'f', 2) + " %"));

        QTableWidgetItem *statItem =
            new QTableWidgetItem(isAno ? "⚠️ Anomalie" : "✅ Normal");
        if (isAno) statItem->setForeground(QColor("#dc3545"));
        ui->anomalyTable->setItem(row, 4, statItem);
        ++row;
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  PARTENAIRE
// ═════════════════════════════════════════════════════════════════════════════

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
    table->setHorizontalHeaderLabels(
        {"ID", "Nom", "Email", "Téléphone", "Investissement", "Employé ID"});
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
        table->setItem(row, 5, new QTableWidgetItem(
                                   p.getIdEmploye() > 0
                                       ? QString::number(p.getIdEmploye()) : "-"));
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
    QString nom            = ui->namepartenaireLineEdit->text().trimmed();
    QString email          = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel            = ui->phonepartenaireLineEdit->text().trimmed();
    QString investissement = ui->investissementpartenaireLineEdit->text().trimmed();

    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir Nom, Email et Téléphone.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "Veuillez entrer une adresse email valide.");
        return;
    }
    if (!validerTelephone(tel)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Veuillez entrer un numéro de téléphone valide (7–15 chiffres).");
        return;
    }

    int idEmploye = ui->employeComboBox->currentData().toInt();
    Partenaire p(0, nom, email, investissement, tel, idEmploye);
    if (p.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Partenaire ajouté avec succès !");
        chargerPartenaires();
        viderFormulairePartenaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le partenaire.");
    }
}

void MainWindow::on_updatepartenaireButton_clicked()
{
    int id = idPartenaireSelectionne();
    if (id == -1) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un partenaire dans le tableau.");
        return;
    }

    QString nom            = ui->namepartenaireLineEdit->text().trimmed();
    QString email          = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel            = ui->phonepartenaireLineEdit->text().trimmed();
    QString investissement = ui->investissementpartenaireLineEdit->text().trimmed();

    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir Nom, Email et Téléphone.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "Veuillez entrer une adresse email valide.");
        return;
    }
    if (!validerTelephone(tel)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Veuillez entrer un numéro de téléphone valide.");
        return;
    }

    int idEmploye = ui->employeComboBox->currentData().toInt();
    Partenaire p(id, nom, email, investissement, tel, idEmploye);
    if (p.modifier()) {
        QMessageBox::information(this, "Succès", "✅ Partenaire modifié avec succès !");
        chargerPartenaires();
        viderFormulairePartenaire();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de modifier le partenaire.");
    }
}

void MainWindow::on_deletepartenaireButton_clicked()
{
    int id = idPartenaireSelectionne();
    if (id == -1) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un partenaire dans le tableau.");
        return;
    }

    auto reply = QMessageBox::question(this, "Confirmation",
                                       "Confirmer la suppression de ce partenaire ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Partenaire p;
        p.setId(id);
        if (p.supprimer()) {
            QMessageBox::information(this, "Succès", "✅ Partenaire supprimé !");
            chargerPartenaires();
            viderFormulairePartenaire();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer le partenaire.");
        }
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
    on_searchpartenaireLineEdit_textChanged(
        ui->searchpartenaireLineEdit->text());
}

void MainWindow::on_searchpartenaireLineEdit_textChanged(const QString &text)
{
    QString term = text.trimmed().toLower();
    if (term.isEmpty()) {
        chargerPartenaires();
        return;
    }

    Partenaire p;
    QList<Partenaire> filtered;
    for (const Partenaire &pt : p.afficherTous()) {
        if (pt.getNom().toLower().contains(term)
            || pt.getTelephone().contains(term)) {
            filtered.append(pt);
        }
    }
    remplirTablePartenaires(filtered);
}

void MainWindow::on_tabWidgetPartenaire_currentChanged(int index)
{
    if (index == 1) {
        // Onglet Statistiques
        statPartenaire.calculerEtAfficher(
            ui->valueTotalPartenaires,
            ui->valueActifs
            );
    }
    else if (index == 2) {
        // Onglet Mailing — remplir la liste des partenaires
        ui->mailingPartenaireComboBox->clear();
        for (const Partenaire &p : mailing.chargerPartenaires()) {
            ui->mailingPartenaireComboBox->addItem(
                p.getNom() + "  <" + p.getEmail() + ">",
                p.getId()
                );
        }
    }
}
void MainWindow::on_sendMailButton_clicked()
{
    // Récupérer l'ID du partenaire sélectionné
    int idPartenaire = ui->mailingPartenaireComboBox->currentData().toInt();
    if (idPartenaire <= 0) {
        QMessageBox::warning(this, "Aucun partenaire",
                             "Veuillez sélectionner un partenaire.");
        return;
    }

    QString sujet   = ui->subjectLineEdit->text().trimmed();
    QString message = ui->messageTextEdit->toPlainText().trimmed();

    if (sujet.isEmpty()) {
        QMessageBox::warning(this, "Sujet vide",
                             "Veuillez saisir un sujet.");
        return;
    }
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Message vide",
                             "Veuillez saisir un message.");
        return;
    }

    // Retrouver le partenaire complet par son ID
    Partenaire cible;
    for (const Partenaire &p : mailing.chargerPartenaires()) {
        if (p.getId() == idPartenaire) { cible = p; break; }
    }

    if (mailing.envoyerEmail(cible, sujet, message)) {
        QMessageBox::information(this, "Succès",
                                 "✅ Email envoyé à " + cible.getNom() + " !");
        ui->subjectLineEdit->clear();
        ui->messageTextEdit->clear();
    } else {
        QMessageBox::critical(this, "Échec de l'envoi",
                              mailing.erreurMessage());
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  CHATBOT
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::on_chatbotSendButton_clicked()
{
    QString message = ui->chatbotInputLineEdit->text().trimmed();
    if (message.isEmpty()) return;

    // Afficher le message de l'utilisateur dans la zone d'échanges
    ui->chatbotDisplayArea->append(
        "<b style='color:#2d4a1f;'>Vous :</b> " + message.toHtmlEscaped()
        );

    // Vider le champ de saisie et désactiver le bouton pendant l'attente
    ui->chatbotInputLineEdit->clear();
    ui->chatbotSendButton->setEnabled(false);
    ui->chatbotSendButton->setText("⏳ En attente...");

    // Envoyer à l'API Groq (asynchrone)
    chatbot.envoyerMessage(message);
}

void MainWindow::onChatbotReponse(const QString &reponse)
{
    // Afficher la réponse du chatbot
    ui->chatbotDisplayArea->append(
        "<b style='color:#b8860b;'>🤖 ChatBot :</b> " + reponse.toHtmlEscaped()
        );
    ui->chatbotDisplayArea->append(""); // ligne vide pour aérer

    // Réactiver le bouton
    ui->chatbotSendButton->setEnabled(true);
    ui->chatbotSendButton->setText("📤 Envoyer");
    ui->chatbotInputLineEdit->setFocus();
}

void MainWindow::onChatbotErreur(const QString &erreur)
{
    ui->chatbotDisplayArea->append(
        "<span style='color:#dc3545;'>⚠️ Erreur : " + erreur.toHtmlEscaped() + "</span>"
        );

    // Réactiver le bouton
    ui->chatbotSendButton->setEnabled(true);
    ui->chatbotSendButton->setText("📤 Envoyer");
}
// ═════════════════════════════════════════════════════════════════════════════

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
    QString nom        = ui->inputNomClient->text().trimmed();
    QString prenom     = ui->inputPrenomClient->text().trimmed();
    QString email      = ui->inputEmailClient->text().trimmed();
    QString telephone  = ui->inputTelephoneClient->text().trimmed();
    QString typeClient = ui->inputTypeClient->currentText();
    QString avis       = ui->inputFeedbackClient->toPlainText().trimmed();

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir le nom et le prénom du client.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "Veuillez entrer une adresse email valide.");
        return;
    }
    if (!validerTelephone(telephone)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Veuillez entrer un numéro de téléphone valide.");
        return;
    }

    Client c(0, nom, prenom, email, telephone, typeClient, avis);
    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Client ajouté avec succès !");
        refreshClientTable();
        clearFormClient();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
    }
}

void MainWindow::on_btnUpdateClient_clicked()
{
    if (selectedClientId == -1) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un client dans le tableau.");
        return;
    }

    QString nom        = ui->inputNomClient->text().trimmed();
    QString prenom     = ui->inputPrenomClient->text().trimmed();
    QString email      = ui->inputEmailClient->text().trimmed();
    QString telephone  = ui->inputTelephoneClient->text().trimmed();
    QString typeClient = ui->inputTypeClient->currentText();
    QString avis       = ui->inputFeedbackClient->toPlainText().trimmed();

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants",
                             "Veuillez remplir le nom et le prénom du client.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "Veuillez entrer une adresse email valide.");
        return;
    }
    if (!validerTelephone(telephone)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Veuillez entrer un numéro de téléphone valide.");
        return;
    }

    Client c(selectedClientId, nom, prenom, email, telephone, typeClient, avis);
    if (c.modifier()) {
        QMessageBox::information(this, "Succès", "✅ Client modifié avec succès !");
        refreshClientTable();
        clearFormClient();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de modifier le client.");
    }
}

void MainWindow::on_btnDeleteClient_clicked()
{
    if (selectedClientId == -1) {
        QMessageBox::warning(this, "Aucune sélection",
                             "Veuillez sélectionner un client dans le tableau.");
        return;
    }

    auto reply = QMessageBox::question(this, "Confirmation",
                                       "Confirmer la suppression de ce client ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Client c;
        c.setId(selectedClientId);
        if (c.supprimer()) {
            QMessageBox::information(this, "Succès", "✅ Client supprimé !");
            refreshClientTable();
            clearFormClient();
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer le client.");
        }
    }
}

void MainWindow::on_btnRefreshClient_clicked()
{
    ui->searchBoxClient->clear();
    clearFormClient();
    ui->clientTable->clearSelection();
    refreshClientTable();
}

void MainWindow::on_btnSearchClient_clicked()
{
    QString term = ui->searchBoxClient->text().trimmed();
    if (term.isEmpty()) {
        refreshClientTable();
        return;
    }
    ClientRecherche recherche;
    recherche.rechercherParNom(ui->clientTable, term);
}

void MainWindow::on_btnClearClient_clicked()
{
    clearFormClient();
    ui->searchBoxClient->clear();
    ui->clientTable->clearSelection();
    ui->searchBoxClient->setFocus();
}

void MainWindow::on_btnExportClientPDF_clicked()
{
    QList<Client> clients = clientObj.afficherTous();
    if (clients.isEmpty()) {
        QMessageBox::warning(this, "Export PDF", "Aucun client à exporter.");
        return;
    }

    QString chemin = QFileDialog::getSaveFileName(
        this,
        "Exporter les clients en PDF",
        "clients_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".pdf",
        "Fichiers PDF (*.pdf)"
        );
    if (chemin.isEmpty()) return;
    if (!chemin.endsWith(".pdf", Qt::CaseInsensitive)) chemin += ".pdf";

    ClientExport exporter;
    exporter.exporterPDF(ui->clientTable, chemin);

    QMessageBox::information(this, "Export PDF",
                             QString("Export terminé !\nFichier : %1").arg(chemin));
}

void MainWindow::on_btnTriClient_clicked()
{
    QMenu menu(this);
    menu.addAction("Par nom (A-Z)", [this]() {
        afficherClientsTable(ClientTri::trierParNom(clientObj.afficherTous(), true));
    });
    menu.addAction("Par nom (Z-A)", [this]() {
        afficherClientsTable(ClientTri::trierParNom(clientObj.afficherTous(), false));
    });
    menu.addAction("Par type client", [this]() {
        afficherClientsTable(ClientTri::trierParTypeClient(clientObj.afficherTous()));
    });
    menu.addAction("Par volume d'achat", [this]() {
        afficherClientsTable(ClientTri::trierParVolumeAchat());
    });
    menu.addAction("Réinitialiser", [this]() {
        refreshClientTable();
    });
    menu.exec(QCursor::pos());
}

void MainWindow::on_tabWidgetClient_currentChanged(int index)
{
    if (index == 1) {
        ClientStat stats;
        stats.updateStats(ui->valueTotalClients,
                          ui->valueParticuliers,
                          ui->valueEntreprises);
    }
}

void MainWindow::afficherClientsTable(const QList<Client> &clients)
{
    QTableWidget *table = ui->clientTable;
    table->setRowCount(0);
    int row = 0;
    for (const Client &c : clients) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(c.getId())));
        table->setItem(row, 1, new QTableWidgetItem(c.getNom()));
        table->setItem(row, 2, new QTableWidgetItem(c.getPrenom()));
        table->setItem(row, 3, new QTableWidgetItem(c.getEmail()));
        table->setItem(row, 4, new QTableWidgetItem(c.getTelephone()));
        table->setItem(row, 5, new QTableWidgetItem(c.getTypeClient()));
        table->setItem(row, 6, new QTableWidgetItem(c.getAvis()));
        row++;
    }
    table->resizeColumnsToContents();
}

// ═════════════════════════════════════════════════════════════════════════════
//  EMPLOYÉ
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::chargerEmployes()
{
    EmployeSearch::chargerTout(ui->employeTable);
}

void MainWindow::viderFormulaireEmploye()
{
    ui->inputIdEmploye->clear();
    ui->inputNomEmploye->clear();
    ui->inputPrenomEmploye->clear();
    ui->inputPosteEmploye->setCurrentIndex(0);
    ui->inputSalaireEmploye->setValue(0);
    ui->inputDateEmbaucheEmploye->setDate(QDate(2000, 1, 1));
}

void MainWindow::chargerStatistiquesEmployes()
{
    EmployeStats::charger(ui->valueTotalEmployes,
                          ui->valueOuvriers,
                          ui->valueTechniciens);
}

void MainWindow::on_btnAddEmploye_clicked()
{
    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir Nom et Prénom !");
        return;
    }

    Employe e(0, nom, prenom,
              ui->inputPosteEmploye->currentText(),
              ui->inputSalaireEmploye->value(),
              ui->inputDateEmbaucheEmploye->date());

    if (e.ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        chargerEmployes();
        viderFormulaireEmploye();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_btnUpdateEmploye_clicked()
{
    QString idStr = ui->inputIdEmploye->text().trimmed();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé dans le tableau !");
        return;
    }

    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir Nom et Prénom !");
        return;
    }

    Employe e(idStr.toInt(), nom, prenom,
              ui->inputPosteEmploye->currentText(),
              ui->inputSalaireEmploye->value(),
              ui->inputDateEmbaucheEmploye->date());

    if (e.modifier()) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès !");
        chargerEmployes();
        viderFormulaireEmploye();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_btnDeleteEmploye_clicked()
{
    QString idStr = ui->inputIdEmploye->text().trimmed();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez un employé dans le tableau !");
        return;
    }

    if (QMessageBox::question(this, "Confirmation",
                              "Voulez-vous vraiment supprimer cet employé ?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        Employe e;
        if (e.supprimer(idStr.toInt())) {
            QMessageBox::information(this, "Succès", "Employé supprimé !");
            chargerEmployes();
            viderFormulaireEmploye();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
        }
    }
}

void MainWindow::on_btnRefreshEmploye_clicked()
{
    chargerEmployes();
    viderFormulaireEmploye();
}

void MainWindow::on_employeTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    ui->inputIdEmploye->setText(ui->employeTable->item(row, 0)->text());
    ui->inputNomEmploye->setText(ui->employeTable->item(row, 1)->text());
    ui->inputPrenomEmploye->setText(ui->employeTable->item(row, 2)->text());

    int idx = ui->inputPosteEmploye->findText(ui->employeTable->item(row, 3)->text());
    if (idx >= 0) ui->inputPosteEmploye->setCurrentIndex(idx);

    ui->inputSalaireEmploye->setValue(ui->employeTable->item(row, 4)->text().toInt());

    QDate date = QDate::fromString(ui->employeTable->item(row, 5)->text(), "dd/MM/yyyy");
    if (date.isValid()) ui->inputDateEmbaucheEmploye->setDate(date);
}

void MainWindow::on_btnSearchEmploye_clicked()
{
    EmployeSearch::filtrer(ui->employeTable, ui->searchBoxEmploye->text().trimmed());
}

void MainWindow::on_btnClearEmploye_clicked()
{
    ui->searchBoxEmploye->clear();
    chargerEmployes();
    viderFormulaireEmploye();
}

void MainWindow::on_searchBoxEmploye_textChanged(const QString &text)
{
    EmployeSearch::filtrer(ui->employeTable, text);
}

void MainWindow::on_tabWidgetEmploye_currentChanged(int index)
{
    if (index == 1) chargerStatistiquesEmployes();
}

void MainWindow::exporterEmployesPDF()
{
    EmployePDF::exporter(ui->employeTable, this);
}

// ═════════════════════════════════════════════════════════════════════════════
//  MACHINE
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::chargerMachines()
{
    MachineSearch::chargerTout(ui->machineTable);
}

void MainWindow::viderFormulaireMachine()
{
    ui->inputIdMachine->clear();
    ui->inputTypeMachine->clear();
    ui->inputEtatMachine->setCurrentIndex(0);
    ui->inputDateMaintenance->setDate(QDate::currentDate());
    ui->inputDureeMachine->setValue(0);
}

void MainWindow::on_btnAddMachine_clicked()
{
    QString type = ui->inputTypeMachine->toPlainText().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le type de la machine !");
        return;
    }

    Machine m(0, type,
              ui->inputEtatMachine->currentText(),
              ui->inputDateMaintenance->date(),
              ui->inputDureeMachine->value());

    if (m.ajouter()) {
        QMessageBox::information(this, "Succès", "Machine ajoutée avec succès !");
        chargerMachines();
        viderFormulaireMachine();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la machine !");
    }
}

void MainWindow::on_btnUpdateMachine_clicked()
{
    QString idStr = ui->inputIdMachine->text().trimmed();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez une machine dans le tableau !");
        return;
    }

    QString type = ui->inputTypeMachine->toPlainText().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le type de la machine !");
        return;
    }

    Machine m(idStr.toInt(), type,
              ui->inputEtatMachine->currentText(),
              ui->inputDateMaintenance->date(),
              ui->inputDureeMachine->value());

    if (m.modifier()) {
        QMessageBox::information(this, "Succès", "Machine modifiée avec succès !");
        chargerMachines();
        viderFormulaireMachine();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la machine !");
    }
}

void MainWindow::on_btnDeleteMachine_clicked()
{
    QString idStr = ui->inputIdMachine->text().trimmed();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez une machine dans le tableau !");
        return;
    }

    if (QMessageBox::question(this, "Confirmation",
                              "Voulez-vous vraiment supprimer cette machine ?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        Machine m;
        if (m.supprimer(idStr.toInt())) {
            QMessageBox::information(this, "Succès", "Machine supprimée !");
            chargerMachines();
            viderFormulaireMachine();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de la machine !");
        }
    }
}

void MainWindow::on_btnRefreshMachine_clicked()
{
    chargerMachines();
    viderFormulaireMachine();
}

void MainWindow::on_machineTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    ui->inputIdMachine->setText(ui->machineTable->item(row, 0)->text());
    ui->inputTypeMachine->setText(ui->machineTable->item(row, 1)->text());

    int idx = ui->inputEtatMachine->findText(ui->machineTable->item(row, 2)->text());
    if (idx >= 0) ui->inputEtatMachine->setCurrentIndex(idx);

    QDate date = QDate::fromString(ui->machineTable->item(row, 3)->text(), "dd/MM/yyyy");
    if (date.isValid()) ui->inputDateMaintenance->setDate(date);

    ui->inputDureeMachine->setValue(ui->machineTable->item(row, 4)->text().toInt());
}

void MainWindow::on_btnSearchMachine_clicked()
{
    MachineSearch::filtrer(ui->machineTable, ui->searchBoxMachine->text().trimmed());
}

void MainWindow::on_btnClearMachine_clicked()
{
    ui->searchBoxMachine->clear();
    chargerMachines();
    viderFormulaireMachine();
}

void MainWindow::on_searchBoxMachine_textChanged(const QString &text)
{
    MachineSearch::filtrer(ui->machineTable, text);
}

void MainWindow::exporterMachinesPDF()
{
    MachinePDF::exporter(ui->machineTable, this);
}
