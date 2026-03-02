#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "partenaire.h"
#include "connection.h"

#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>

// ═════════════════════════════════════════════════════════════════════════════
//  Constructeur / Destructeur
// ═════════════════════════════════════════════════════════════════════════════

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ── Connexion à la base de données ────────────────────────────────────────
    if (!Connection::instance()->createConnect()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "Impossible de se connecter à la base de données.");
    }

    // ── Navigation ────────────────────────────────────────────────────────────
    connect(ui->btnEmploye, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
    });
    connect(ui->btnClient, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageClient);
    });
    connect(ui->btnStock, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageStock);
    });
    connect(ui->btnMachine, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMachine);
    });
    connect(ui->btnProduction, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageProduction);
    });
    connect(ui->btnPartenaire, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pagePartenaire);
        chargerEmployesComboBox();
        chargerPartenaires();
    });

    // ── Configuration du tableau ──────────────────────────────────────────────
    ui->partnersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->partnersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->partnersTable->setAlternatingRowColors(true);
    ui->partnersTable->horizontalHeader()->setStretchLastSection(true);
    ui->partnersTable->verticalHeader()->setVisible(false);

    // ── Connexions boutons ────────────────────────────────────────────────────
    connect(ui->addpartenaireButton,    &QPushButton::clicked,
            this, &MainWindow::on_addpartenaireButton_clicked);
    connect(ui->deletepartenaireButton, &QPushButton::clicked,
            this, &MainWindow::on_deletepartenaireButton_clicked);
    connect(ui->partnersTable,          &QTableWidget::itemClicked,
            this, &MainWindow::on_partnersTable_itemClicked);

    // ── Page par défaut ───────────────────────────────────────────────────────
    ui->stackedWidget->setCurrentWidget(ui->pageProduction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ═════════════════════════════════════════════════════════════════════════════
//  Helpers privés
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::chargerPartenaires()
{
    Partenaire p;
    remplirTable(p.afficherTous());
}

// Charge la liste des employés dans le comboBox
// Chaque item affiche "ID - Nom Prénom" et stocke l'ID en userData
void MainWindow::chargerEmployesComboBox()
{
    ui->employeComboBox->clear();
    // Premier item vide (aucun employé sélectionné)
    ui->employeComboBox->addItem("-- Sélectionner un employé --", QVariant(0));

    const QList<QPair<int,QString>> employes = Partenaire::listerEmployes();
    for (const auto &emp : employes) {
        // Affichage : "ID - Nom Prénom"
        QString label = QString("%1 - %2").arg(emp.first).arg(emp.second);
        ui->employeComboBox->addItem(label, QVariant(emp.first));
    }
}

void MainWindow::remplirTable(const QList<Partenaire> &liste)
{
    ui->partnersTable->clearContents();
    ui->partnersTable->setRowCount(0);
    ui->partnersTable->setColumnCount(6);
    ui->partnersTable->setHorizontalHeaderLabels(
        {"Nom", "Email", "Téléphone", "Investissement", "Employé (ID)", "ID"});
    ui->partnersTable->setColumnHidden(5, true);  // colonne ID partenaire cachée

    for (const Partenaire &p : liste) {
        int row = ui->partnersTable->rowCount();
        ui->partnersTable->insertRow(row);
        ui->partnersTable->setItem(row, 0, new QTableWidgetItem(p.getNom()));
        ui->partnersTable->setItem(row, 1, new QTableWidgetItem(p.getEmail()));
        ui->partnersTable->setItem(row, 2, new QTableWidgetItem(p.getTelephone()));
        ui->partnersTable->setItem(row, 3, new QTableWidgetItem(p.getInvestissement()));

        // Colonne Employé : afficher "ID - Nom" si ID > 0, sinon vide
        QString employe;
        if (p.getIdEmploye() > 0) {
            // Chercher le nom dans le comboBox pour éviter une requête supplémentaire
            int idx = ui->employeComboBox->findData(QVariant(p.getIdEmploye()));
            if (idx > 0)
                employe = ui->employeComboBox->itemText(idx);
            else
                employe = QString::number(p.getIdEmploye());
        }
        ui->partnersTable->setItem(row, 4, new QTableWidgetItem(employe));
        ui->partnersTable->setItem(row, 5, new QTableWidgetItem(QString::number(p.getId())));
    }

    ui->partnersTable->resizeColumnsToContents();
}

void MainWindow::viderFormulaire()
{
    ui->namepartenaireLineEdit->clear();
    ui->emailpartenaireLineEdit->clear();
    ui->phonepartenaireLineEdit->clear();
    ui->investissementpartenaireLineEdit->clear();
    ui->employeComboBox->setCurrentIndex(0);
    ui->partnersTable->clearSelection();
}

int MainWindow::idSelectionne()
{
    QList<QTableWidgetItem*> items = ui->partnersTable->selectedItems();
    if (items.isEmpty()) return -1;

    int row = items.first()->row();
    QTableWidgetItem *idItem = ui->partnersTable->item(row, 5); // colonne ID (index 5)
    if (!idItem) return -1;

    return idItem->text().toInt();
}

// ═════════════════════════════════════════════════════════════════════════════
//  SLOT : Ajouter
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::on_addpartenaireButton_clicked()
{
    // ── Validation ────────────────────────────────────────────────────────────
    if (ui->namepartenaireLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Le nom est obligatoire.");
        return;
    }
    if (ui->emailpartenaireLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "L'email est obligatoire.");
        return;
    }
    if (ui->phonepartenaireLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Le téléphone est obligatoire.");
        return;
    }

    // ── Récupérer l'ID employé sélectionné dans le comboBox ──────────────────
    int idEmp = ui->employeComboBox->currentData().toInt(); // 0 si "-- Sélectionner --"

    // ── Création et insertion ─────────────────────────────────────────────────
    Partenaire p;
    p.setNom(           ui->namepartenaireLineEdit->text().trimmed());
    p.setEmail(         ui->emailpartenaireLineEdit->text().trimmed());
    p.setTelephone(     ui->phonepartenaireLineEdit->text().trimmed());
    p.setInvestissement(ui->investissementpartenaireLineEdit->text().trimmed());
    p.setIdEmploye(     idEmp);

    if (p.ajouter()) {
        QMessageBox::information(this, "Succès", "Partenaire ajouté avec succès !");
        viderFormulaire();
        chargerPartenaires();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le partenaire.");
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  SLOT : Supprimer
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::on_deletepartenaireButton_clicked()
{
    int id = idSelectionne();
    if (id == -1) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un partenaire dans le tableau.");
        return;
    }

    // Récupérer le nom pour la confirmation
    QString nom;
    QList<QTableWidgetItem*> items = ui->partnersTable->selectedItems();
    if (!items.isEmpty()) {
        QTableWidgetItem *nomItem = ui->partnersTable->item(items.first()->row(), 0);
        if (nomItem) nom = nomItem->text();
    }

    int rep = QMessageBox::question(
        this, "Confirmation",
        QString("Supprimer le partenaire « %1 » ?\nCette action est irréversible.").arg(nom),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (rep != QMessageBox::Yes) return;

    Partenaire p;
    p.setId(id);

    if (p.supprimer()) {
        QMessageBox::information(this, "Succès", "Partenaire supprimé avec succès !");
        viderFormulaire();
        chargerPartenaires();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de supprimer le partenaire.");
    }
}

// ═════════════════════════════════════════════════════════════════════════════
//  SLOT : Clic sur une ligne → remplir le formulaire
// ═════════════════════════════════════════════════════════════════════════════

void MainWindow::on_partnersTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    auto getText = [&](int col) -> QString {
        QTableWidgetItem *i = ui->partnersTable->item(row, col);
        return i ? i->text() : QString();
    };

    ui->namepartenaireLineEdit->setText(          getText(0));  // NOM
    ui->emailpartenaireLineEdit->setText(         getText(1));  // EMAIL
    ui->phonepartenaireLineEdit->setText(         getText(2));  // TELEPHONE
    ui->investissementpartenaireLineEdit->setText(getText(3));  // INVESTISSEMENT

    // Sélectionner l'employé correspondant dans le comboBox
    // La colonne 5 (cachée) contient l'ID partenaire, mais l'ID employé
    // est retrouvé depuis le texte de la colonne 4 ou via le comboBox
    QString empText = getText(4); // "ID - Nom Prénom" ou vide
    if (!empText.isEmpty()) {
        int idx = ui->employeComboBox->findText(empText);
        ui->employeComboBox->setCurrentIndex(idx > 0 ? idx : 0);
    } else {
        ui->employeComboBox->setCurrentIndex(0);
    }
}
