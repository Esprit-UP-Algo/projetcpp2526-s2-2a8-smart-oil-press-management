#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QTimer>
#include <QRegularExpression>
#include <QSqlQuery>

// ═════════════════════════════════════════════════════════════════════════════
//  CONSTRUCTOR
// ═════════════════════════════════════════════════════════════════════════════
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ─────────────────────────────────────────────────────────────────────────
    // NAVIGATION — Sidebar buttons → StackedWidget pages
    // ─────────────────────────────────────────────────────────────────────────
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
        afficherProductions();
    });
    connect(ui->btnPartenaire, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pagePartenaire);
        chargerPartenaires();
        chargerEmployesComboBox();
    });

    // ─────────────────────────────────────────────────────────────────────────
    // Default page
    // ─────────────────────────────────────────────────────────────────────────
    ui->stackedWidget->setCurrentWidget(ui->pageProduction);
    QTimer::singleShot(0, this, &MainWindow::afficherProductions);

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — Switch tabs: refresh stats on Statistiques tab
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
        if (index == 1)
            afficherStatistiques();
    });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — Auto-calculate rendement
    // ─────────────────────────────────────────────────────────────────────────
    auto calculateRendement = [this]() {
        double qteOlive = ui->inputQuantiteOlive->value();
        double qteHuile = ui->inputQuantiteHuile->value() * 0.916;
        if (qteOlive > 0 && qteHuile > 0)
            ui->inputRendement->setText(
                QString::number((qteHuile / qteOlive) * 100.0, 'f', 2) + " %");
        else
            ui->inputRendement->clear();
    };
    connect(ui->inputQuantiteOlive,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, calculateRendement);
    connect(ui->inputQuantiteHuile,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, calculateRendement);

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — Click table row → fill form
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->productionTable, &QTableWidget::itemClicked,
            this, [this](QTableWidgetItem *item) {
                int row = item->row();
                ui->productionTable->setProperty(
                    "selectedId",
                    ui->productionTable->item(row, 0)->text().toInt());

                QDate date = QDate::fromString(
                    ui->productionTable->item(row, 1)->text(), "dd/MM/yyyy");
                ui->inputDate->setDate(date.isValid() ? date : QDate::currentDate());

                QString oliveStr = ui->productionTable->item(row, 2)->text();
                oliveStr.remove(" kg");
                ui->inputQuantiteOlive->setValue(oliveStr.toDouble());

                QString huileStr = ui->productionTable->item(row, 3)->text();
                huileStr.remove(" L");
                ui->inputQuantiteHuile->setValue(huileStr.toDouble());

                QString rendStr = ui->productionTable->item(row, 4)->text();
                rendStr.remove(" %");
                ui->inputRendement->setText(rendStr + " %");
            });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — AJOUTER
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnAddProduction, &QPushButton::clicked, this, [this]() {
        double qteOlive = ui->inputQuantiteOlive->value();
        double qteHuile = ui->inputQuantiteHuile->value();

        if (qteOlive <= 0) {
            QMessageBox::warning(this, "Validation",
                                 "La quantité d'olives doit être supérieure à 0.");
            ui->inputQuantiteOlive->setFocus();
            return;
        }
        if (qteHuile <= 0) {
            QMessageBox::warning(this, "Validation",
                                 "La quantité d'huile doit être supérieure à 0.");
            ui->inputQuantiteHuile->setFocus();
            return;
        }
        if (qteHuile > qteOlive) {
            QMessageBox::warning(this, "Validation",
                                 "La quantité d'huile ne peut pas dépasser la quantité d'olives.");
            ui->inputQuantiteHuile->setFocus();
            return;
        }

        double rendement = (qteHuile / qteOlive) * 100.0;
        ui->inputRendement->setText(QString::number(rendement, 'f', 2) + " %");

        prod.setDateProd(ui->inputDate->date());
        prod.setQuantiteOlive(qteOlive);
        prod.setQuantiteHuile(qteHuile);
        prod.setRendement(rendement);

        if (prod.ajouter()) {
            QMessageBox::information(this, "Succès", "Production ajoutée avec succès !");
            ui->inputDate->setDate(QDate::currentDate());
            ui->inputQuantiteOlive->setValue(0.0);
            ui->inputQuantiteHuile->setValue(0.0);
            ui->inputRendement->clear();
            afficherProductions();
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Échec de l'ajout.\nVérifiez la connexion à la base de données.");
        }
    });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — MODIFIER
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnUpdateProduction, &QPushButton::clicked, this, [this]() {
        int selectedId = ui->productionTable->property("selectedId").toInt();
        if (selectedId <= 0) {
            QMessageBox::warning(this, "Sélection requise",
                                 "Veuillez sélectionner une production dans le tableau.");
            return;
        }

        double qteOlive = ui->inputQuantiteOlive->value();
        double qteHuile = ui->inputQuantiteHuile->value();

        if (qteOlive <= 0 || qteHuile <= 0 || qteHuile > qteOlive) {
            QMessageBox::warning(this, "Validation",
                                 "Vérifiez les valeurs saisies (quantités > 0, huile ≤ olives).");
            return;
        }

        double rendement = (qteHuile / qteOlive) * 100.0;
        prod.setId(selectedId);
        prod.setDateProd(ui->inputDate->date());
        prod.setQuantiteOlive(qteOlive);
        prod.setQuantiteHuile(qteHuile);
        prod.setRendement(rendement);

        if (prod.modifier()) {
            QMessageBox::information(this, "Succès", "Production modifiée avec succès !");
            ui->inputDate->setDate(QDate::currentDate());
            ui->inputQuantiteOlive->setValue(0.0);
            ui->inputQuantiteHuile->setValue(0.0);
            ui->inputRendement->clear();
            ui->productionTable->setProperty("selectedId", 0);
            afficherProductions();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la modification.");
        }
    });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — SUPPRIMER
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnDeleteProduction, &QPushButton::clicked, this, [this]() {
        int selectedId = ui->productionTable->property("selectedId").toInt();
        if (selectedId <= 0) {
            QMessageBox::warning(this, "Sélection requise",
                                 "Veuillez sélectionner une production dans le tableau.");
            return;
        }

        auto rep = QMessageBox::question(
            this, "Confirmation",
            QString("Supprimer la production ID %1 ?").arg(selectedId),
            QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::No) return;

        if (prod.supprimer(selectedId)) {
            QMessageBox::information(this, "Succès", "Production supprimée avec succès !");
            ui->inputDate->setDate(QDate::currentDate());
            ui->inputQuantiteOlive->setValue(0.0);
            ui->inputQuantiteHuile->setValue(0.0);
            ui->inputRendement->clear();
            ui->productionTable->setProperty("selectedId", 0);
            afficherProductions();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
        }
    });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — REFRESH
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnRefreshProduction, &QPushButton::clicked,
            this, &MainWindow::afficherProductions);

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — CLEAR form
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnClearProduction, &QPushButton::clicked, this, [this]() {
        ui->inputDate->setDate(QDate::currentDate());
        ui->inputQuantiteOlive->setValue(0.0);
        ui->inputQuantiteHuile->setValue(0.0);
        ui->inputRendement->clear();
        ui->productionTable->setProperty("selectedId", 0);
    });

    // ─────────────────────────────────────────────────────────────────────────
    // PRODUCTION — EXPORT PDF
    // ─────────────────────────────────────────────────────────────────────────
    connect(ui->btnExportPDFProduction, &QPushButton::clicked, this, [this]() {
        pdf.exporterPDF(this);
    });
}

// ═════════════════════════════════════════════════════════════════════════════
//  DESTRUCTOR
// ═════════════════════════════════════════════════════════════════════════════
MainWindow::~MainWindow()
{
    delete ui;
}

// ═════════════════════════════════════════════════════════════════════════════
//  PRODUCTION — Methods
// ═════════════════════════════════════════════════════════════════════════════
void MainWindow::afficherProductions()
{
    prod.afficher(ui->productionTable);
}

void MainWindow::afficherStatistiques()
{
    stat.calculerEtAfficher(
        ui->valueTotal,
        ui->valueOlives,
        ui->valueHuile,
        ui->valueRendement
        );
}

// ═════════════════════════════════════════════════════════════════════════════
//  PARTENAIRE — Private helpers
// ═════════════════════════════════════════════════════════════════════════════

// Charge tous les partenaires depuis la DB et les affiche dans le tableau
void MainWindow::chargerPartenaires()
{
    Partenaire p;
    remplirTable(p.afficherTous());
}

// Remplit le tableau à partir d'une liste quelconque (utilisé aussi par filtre)
// Colonnes UI : 0=Nom  1=Email  2=Téléphone  3=Type(Investissement)  4=Statut(EmployéID)
// L'ID du partenaire est stocké en UserRole sur la colonne 0 (invisible)
void MainWindow::remplirTable(const QList<Partenaire> &liste)
{
    ui->partnersTable->setRowCount(0);

    for (const Partenaire &p : liste) {
        int row = ui->partnersTable->rowCount();
        ui->partnersTable->insertRow(row);

        // col 0 — Nom (+ ID caché en UserRole)
        QTableWidgetItem *itemNom = new QTableWidgetItem(p.getNom());
        itemNom->setData(Qt::UserRole, p.getId());
        ui->partnersTable->setItem(row, 0, itemNom);

        // col 1 — Email
        ui->partnersTable->setItem(row, 1,
                                   new QTableWidgetItem(p.getEmail()));

        // col 2 — Téléphone
        ui->partnersTable->setItem(row, 2,
                                   new QTableWidgetItem(p.getTelephone()));

        // col 3 — Investissement (header "Type" dans l'UI)
        ui->partnersTable->setItem(row, 3,
                                   new QTableWidgetItem(p.getInvestissement()));

        // col 4 — Employé ID (header "Statut" dans l'UI)
        ui->partnersTable->setItem(row, 4,
                                   new QTableWidgetItem(
                                       p.getIdEmploye() > 0 ? QString::number(p.getIdEmploye()) : "-"));

        // Rendre toutes les cellules non-éditables
        for (int col = 0; col < ui->partnersTable->columnCount(); ++col) {
            if (ui->partnersTable->item(row, col))
                ui->partnersTable->item(row, col)->setFlags(
                    Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    }
    ui->partnersTable->resizeColumnsToContents();
}

// Charge la combo des employés depuis la DB
void MainWindow::chargerEmployesComboBox()
{
    ui->employeComboBox->clear();
    ui->employeComboBox->addItem("-- Aucun --", 0);

    const auto employes = Partenaire::listerEmployes();
    for (const auto &emp : employes)
        ui->employeComboBox->addItem(emp.second, emp.first);
}

// Remet le formulaire partenaire à blanc
void MainWindow::viderFormulaire()
{
    ui->namepartenaireLineEdit->clear();
    ui->emailpartenaireLineEdit->clear();
    ui->phonepartenaireLineEdit->clear();
    ui->investissementpartenaireLineEdit->clear();
    ui->employeComboBox->setCurrentIndex(0);
    ui->partnersTable->setProperty("selectedPartenaire", 0);
}

// Retourne l'ID du partenaire sélectionné dans le tableau
int MainWindow::idSelectionne()
{
    return ui->partnersTable->property("selectedPartenaire").toInt();
}

// Validation email basique (contient @ et .)
bool MainWindow::validerEmail(const QString &email)
{
    QRegularExpression re(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
    return re.match(email).hasMatch();
}

// Validation téléphone : 8 chiffres minimum
bool MainWindow::validerTelephone(const QString &tel)
{
    QRegularExpression re(R"(^\+?[\d\s\-]{8,15}$)");
    return re.match(tel).hasMatch();
}

// ═════════════════════════════════════════════════════════════════════════════
//  PARTENAIRE — Slots (déclarés avec on_ → auto-connect via setupUi)
// ═════════════════════════════════════════════════════════════════════════════

// ── Clic sur une ligne du tableau → remplir le formulaire ────────────────────
void MainWindow::on_partnersTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    // Récupérer l'ID depuis le UserRole de la colonne 0
    int id = ui->partnersTable->item(row, 0)->data(Qt::UserRole).toInt();
    ui->partnersTable->setProperty("selectedPartenaire", id);

    // col 0 = Nom
    ui->namepartenaireLineEdit->setText(
        ui->partnersTable->item(row, 0)->text());
    // col 1 = Email
    ui->emailpartenaireLineEdit->setText(
        ui->partnersTable->item(row, 1)->text());
    // col 2 = Téléphone
    ui->phonepartenaireLineEdit->setText(
        ui->partnersTable->item(row, 2)->text());
    // col 3 = Investissement
    ui->investissementpartenaireLineEdit->setText(
        ui->partnersTable->item(row, 3)->text());

    // col 4 = Employé ID — sélectionner dans la combo
    QString idEmpStr = ui->partnersTable->item(row, 4)->text();
    int idEmp = (idEmpStr == "-") ? 0 : idEmpStr.toInt();
    for (int i = 0; i < ui->employeComboBox->count(); ++i) {
        if (ui->employeComboBox->itemData(i).toInt() == idEmp) {
            ui->employeComboBox->setCurrentIndex(i);
            break;
        }
    }
}

// ── AJOUTER ──────────────────────────────────────────────────────────────────
void MainWindow::on_addpartenaireButton_clicked()
{
    QString nom    = ui->namepartenaireLineEdit->text().trimmed();
    QString email  = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel    = ui->phonepartenaireLineEdit->text().trimmed();
    QString invest = ui->investissementpartenaireLineEdit->text().trimmed();
    int     idEmp  = ui->employeComboBox->currentData().toInt();

    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty() || invest.isEmpty()) {
        QMessageBox::warning(this, "Champs requis",
                             "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "L'adresse email n'est pas valide.");
        ui->emailpartenaireLineEdit->setFocus();
        return;
    }
    if (!validerTelephone(tel)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone n'est pas valide (min. 8 chiffres).");
        ui->phonepartenaireLineEdit->setFocus();
        return;
    }

    Partenaire p(0, nom, email, invest, tel, idEmp);
    if (p.ajouter()) {
        QMessageBox::information(this, "Succès", "Partenaire ajouté avec succès !");
        viderFormulaire();
        chargerPartenaires();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du partenaire.");
    }
}

// ── MODIFIER ──────────────────────────────────────────────────────────────────
void MainWindow::on_updatepartenaireButton_clicked()
{
    int id = idSelectionne();
    if (id <= 0) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un partenaire dans le tableau.");
        return;
    }

    QString nom    = ui->namepartenaireLineEdit->text().trimmed();
    QString email  = ui->emailpartenaireLineEdit->text().trimmed();
    QString tel    = ui->phonepartenaireLineEdit->text().trimmed();
    QString invest = ui->investissementpartenaireLineEdit->text().trimmed();
    int     idEmp  = ui->employeComboBox->currentData().toInt();

    if (nom.isEmpty() || email.isEmpty() || tel.isEmpty() || invest.isEmpty()) {
        QMessageBox::warning(this, "Champs requis",
                             "Veuillez remplir tous les champs obligatoires.");
        return;
    }
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             "L'adresse email n'est pas valide.");
        ui->emailpartenaireLineEdit->setFocus();
        return;
    }
    if (!validerTelephone(tel)) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Le numéro de téléphone n'est pas valide.");
        ui->phonepartenaireLineEdit->setFocus();
        return;
    }

    Partenaire p(id, nom, email, invest, tel, idEmp);
    if (p.modifier()) {
        QMessageBox::information(this, "Succès", "Partenaire modifié avec succès !");
        viderFormulaire();
        chargerPartenaires();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

// ── SUPPRIMER ─────────────────────────────────────────────────────────────────
void MainWindow::on_deletepartenaireButton_clicked()
{
    int id = idSelectionne();
    if (id <= 0) {
        QMessageBox::warning(this, "Sélection requise",
                             "Veuillez sélectionner un partenaire dans le tableau.");
        return;
    }

    auto rep = QMessageBox::question(
        this, "Confirmation",
        QString("Supprimer le partenaire ID %1 ?").arg(id),
        QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::No) return;

    Partenaire p;
    p.setId(id);
    if (p.supprimer()) {
        QMessageBox::information(this, "Succès", "Partenaire supprimé avec succès !");
        viderFormulaire();
        chargerPartenaires();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
    }
}

// ── FILTRER (tri par investissement décroissant) ───────────────────────────────
void MainWindow::on_filterpartenaireButton_clicked()
{
    QList<Partenaire> liste = FiltrePartenaire::trierParInvestissementDecroissant();
    if (liste.isEmpty()) {
        QMessageBox::information(this, "Filtre",
                                 "Aucun partenaire trouvé ou erreur lors du filtre.");
        return;
    }
    remplirTable(liste);
}

// ── EXPORTER PDF ──────────────────────────────────────────────────────────────
void MainWindow::on_exportpartenaireButton_clicked()
{
    // Exporter ce qui est actuellement affiché dans le tableau
    QList<Partenaire> liste;
    for (int row = 0; row < ui->partnersTable->rowCount(); ++row) {
        // ID stocké en UserRole sur col 0
        int     id     = ui->partnersTable->item(row, 0)->data(Qt::UserRole).toInt();
        QString nom    = ui->partnersTable->item(row, 0)->text();
        QString email  = ui->partnersTable->item(row, 1)->text();
        QString tel    = ui->partnersTable->item(row, 2)->text();
        QString invest = ui->partnersTable->item(row, 3)->text();
        QString empStr = ui->partnersTable->item(row, 4)->text();
        int     idEmp  = (empStr == "-") ? 0 : empStr.toInt();

        liste.append(Partenaire(id, nom, email, invest, tel, idEmp));
    }

    if (liste.isEmpty()) {
        QMessageBox::warning(this, "Export PDF",
                             "Le tableau est vide, rien à exporter.");
        return;
    }

    ExporterPartenaire::exporterEnPDF(this, liste);
}
