#include "mainwindow.h"
#include "ui_mainwindow.h"

// Modules métier
#include "employe.h"
#include "employe_search.h"
#include "employe_stats.h"
#include "employe_pdf.h"

#include "machine.h"
#include "machine_search.h"
#include "machine_pdf.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDate>

// ─────────────────────────────────────────────────────────────
//  Constructeur : connexions UI uniquement
// ─────────────────────────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ── Navigation entre pages ────────────────────────────────
    connect(ui->btnEmploye, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
        chargerEmployes();
    });
    connect(ui->btnClient,     &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageClient);     });
    connect(ui->btnStock,      &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageStock);      });
    connect(ui->btnMachine,    &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMachine);
        chargerMachines();
    });
    connect(ui->btnProduction, &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageProduction); });
    connect(ui->btnPartenaire, &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pagePartenaire); });

    // ── Recherche en temps réel ───────────────────────────────
    connect(ui->searchBoxEmploye, &QLineEdit::textChanged,
            this, &MainWindow::on_searchBoxEmploye_textChanged);

        connect(ui->searchBoxMachine, &QLineEdit::textChanged,
            this, &MainWindow::on_searchBoxMachine_textChanged);

    // ── Changement d'onglet Employé ───────────────────────────
    connect(ui->tabWidgetEmploye, &QTabWidget::currentChanged,
            this, &MainWindow::on_tabWidgetEmploye_currentChanged);

    // ── Clic sur une ligne du tableau ─────────────────────────
    connect(ui->employeTable, &QTableWidget::clicked,
            this, &MainWindow::on_employeTable_clicked);

        connect(ui->machineTable, &QTableWidget::clicked,
            this, &MainWindow::on_machineTable_clicked);

    // ── Bouton Export PDF (onglet Liste des Employés) ─────────
    QPushButton *exportBtn = ui->employeListTab->findChild<QPushButton*>("exportButton");
    if (exportBtn)
        connect(exportBtn, &QPushButton::clicked, this, &MainWindow::exporterEmployesPDF);

    // ── Bouton Export PDF (onglet Liste des Machines) ─────────
    QPushButton *exportMachineBtn = ui->machineListTab->findChild<QPushButton*>("exportButton");
    if (exportMachineBtn)
        connect(exportMachineBtn, &QPushButton::clicked, this, &MainWindow::exporterMachinesPDF);

    // ── Page de démarrage ─────────────────────────────────────
    ui->stackedWidget->setCurrentWidget(ui->pageProduction);
    chargerEmployes();
    chargerMachines();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─────────────────────────────────────────────────────────────
//  Helpers privés — délèguent aux modules métier
// ─────────────────────────────────────────────────────────────

void MainWindow::chargerEmployes()
{
    EmployeSearch::chargerTout(ui->employeTable);
}

void MainWindow::chargerMachines()
{
    MachineSearch::chargerTout(ui->machineTable);
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

void MainWindow::viderFormulaireMachine()
{
    ui->inputIdMachine->clear();
    ui->inputTypeMachine->clear();
    ui->inputEtatMachine->setCurrentIndex(0);
    ui->inputDateMaintenance->setDate(QDate::currentDate());
    ui->inputDureeMachine->setValue(0);
}

void MainWindow::chargerStatistiquesEmployes()
{
    EmployeStats::charger(ui->valueTotalEmployes,
                          ui->valueOuvriers,
                          ui->valueTechniciens);
}

// ─────────────────────────────────────────────────────────────
//  Slots — CRUD Employé
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
//  Slots — CRUD Machine
// ─────────────────────────────────────────────────────────────

void MainWindow::on_btnAddMachine_clicked()
{
    QString type = ui->inputTypeMachine->toPlainText().trimmed();
    if (type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le type de la machine !");
        return;
    }

    Machine m(0,
              type,
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

    Machine m(idStr.toInt(),
              type,
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

// ─────────────────────────────────────────────────────────────
//  Slots — Sélection ligne tableau → remplissage formulaire
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
//  Slots — Recherche
// ─────────────────────────────────────────────────────────────

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

// ─────────────────────────────────────────────────────────────
//  Slots — Statistiques
// ─────────────────────────────────────────────────────────────

void MainWindow::on_tabWidgetEmploye_currentChanged(int index)
{
    if (index == 1) chargerStatistiquesEmployes();
}

// ─────────────────────────────────────────────────────────────
//  Slot — Export PDF (délégué à EmployePDF)
// ─────────────────────────────────────────────────────────────

void MainWindow::exporterEmployesPDF()
{
    EmployePDF::exporter(ui->employeTable, this);
}

void MainWindow::exporterMachinesPDF()
{
    MachinePDF::exporter(ui->machineTable, this);
}

// ─────────────────────────────────────────────────────────────
//  Slots navigation (auto-connect Qt Designer, corps vides)
// ─────────────────────────────────────────────────────────────

void MainWindow::on_btnEmploye_clicked()    {}
void MainWindow::on_btnClient_clicked()     {}
void MainWindow::on_btnStock_clicked()      {}
void MainWindow::on_btnMachine_clicked()    {}
void MainWindow::on_btnProduction_clicked() {}
void MainWindow::on_btnPartenaire_clicked() {}
