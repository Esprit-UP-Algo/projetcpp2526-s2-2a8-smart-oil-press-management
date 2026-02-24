#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ===== Navigation =====
    connect(ui->btnEmploye, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
        afficherEmployes();
        mettreAJourStatistiques();
    });
    connect(ui->btnClient,     &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageClient); });
    connect(ui->btnStock,      &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageStock); });
    connect(ui->btnMachine,    &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageMachine); });
    connect(ui->btnProduction, &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pageProduction); });
    connect(ui->btnPartenaire, &QPushButton::clicked, this, [this]() { ui->stackedWidget->setCurrentWidget(ui->pagePartenaire); });

    // ===== Boutons CRUD =====
    connect(ui->btnAddEmploye,    &QPushButton::clicked, this, &MainWindow::ajouterEmploye);
    connect(ui->btnUpdateEmploye, &QPushButton::clicked, this, &MainWindow::modifierEmploye);
    connect(ui->btnDeleteEmploye, &QPushButton::clicked, this, &MainWindow::supprimerEmploye);
    connect(ui->exportButton,     &QPushButton::clicked, this, &MainWindow::exporterPDF);

    connect(ui->employeTable, &QTableWidget::cellClicked,
            this, &MainWindow::remplirFormulaireEmploye);

    connect(ui->tabWidgetEmploye, &QTabWidget::currentChanged, this, [this](int index) {
        if (index == 1) mettreAJourStatistiques();
    });

    // ===== Cartes statistiques dynamiques =====
    QVBoxLayout *statsLayout = qobject_cast<QVBoxLayout*>(ui->employeStatsTab->layout());

    auto creerCarte = [](const QString &titre, const QString &couleur, QLabel *&valLabel) -> QFrame* {
        QFrame *card = new QFrame();
        card->setMinimumHeight(120);
        card->setStyleSheet("background: white; border: 2px solid #5d732c; border-radius: 10px;");
        QVBoxLayout *layout = new QVBoxLayout(card);
        QLabel *lTitre = new QLabel(titre);
        lTitre->setAlignment(Qt::AlignCenter);
        lTitre->setStyleSheet("font-size: 14px; color: #888; border: none;");
        valLabel = new QLabel("0");
        valLabel->setAlignment(Qt::AlignCenter);
        valLabel->setStyleSheet(QString("font-size: 32px; color: %1; font-weight: bold; border: none;").arg(couleur));
        layout->addWidget(lTitre);
        layout->addWidget(valLabel);
        return card;
    };

    QHBoxLayout *ligne2 = new QHBoxLayout();
    ligne2->setSpacing(15);
    ligne2->addWidget(creerCarte("Opérateurs",   "#007bff", labelNbOperateurs));
    ligne2->addWidget(creerCarte("Contrôleurs",  "#dc3545", labelNbControleurs));
    ligne2->addWidget(creerCarte("Responsables", "#6f42c1", labelNbResponsables));

    QHBoxLayout *ligne3 = new QHBoxLayout();
    ligne3->addWidget(creerCarte("💰 Salaire Moyen (DT)", "#2d4a1f", labelSalaireMoyen));

    int nb = statsLayout->count();
    statsLayout->insertLayout(nb - 1, ligne2);
    statsLayout->insertLayout(nb,     ligne3);

    // ===== Démarrage =====
    ui->stackedWidget->setCurrentWidget(ui->pageEmploye);
    afficherEmployes();
    mettreAJourStatistiques();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================================================
//  AFFICHER LES EMPLOYÉS
// ============================================================
void MainWindow::afficherEmployes()
{
    ui->employeTable->setRowCount(0);
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, SALAIRE, "
                  "TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') "
                  "FROM ZIT.EMPLOYE ORDER BY ID_EMPLOYE");
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        return;
    }
    int row = 0;
    while (query.next()) {
        ui->employeTable->insertRow(row);
        for (int col = 0; col < 6; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->employeTable->setItem(row, col, item);
        }
        row++;
    }
    ui->employeTable->resizeColumnsToContents();
}

// ============================================================
//  REMPLIR FORMULAIRE
// ============================================================
void MainWindow::remplirFormulaireEmploye(int row, int)
{
    if (row < 0 || row >= ui->employeTable->rowCount()) return;
    ui->inputIdEmploye->setText(ui->employeTable->item(row, 0)->text());
    ui->inputNomEmploye->setText(ui->employeTable->item(row, 1)->text());
    ui->inputPrenomEmploye->setText(ui->employeTable->item(row, 2)->text());
    int idx = ui->inputPosteEmploye->findText(ui->employeTable->item(row, 3)->text());
    if (idx >= 0) ui->inputPosteEmploye->setCurrentIndex(idx);
    ui->inputSalaireEmploye->setValue(ui->employeTable->item(row, 4)->text().toInt());
    QDate d = QDate::fromString(ui->employeTable->item(row, 5)->text(), "dd/MM/yyyy");
    if (d.isValid()) ui->inputDateEmbaucheEmploye->setDate(d);
}

// ============================================================
//  AJOUTER
// ============================================================
void MainWindow::ajouterEmploye()
{
    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();
    QString poste  = ui->inputPosteEmploye->currentText();
    int salaire    = ui->inputSalaireEmploye->value();
    QDate date     = ui->inputDateEmbaucheEmploye->date();

    if (nom.isEmpty())    { QMessageBox::warning(this, "Manquant", "Nom obligatoire.");    return; }
    if (prenom.isEmpty()) { QMessageBox::warning(this, "Manquant", "Prénom obligatoire."); return; }
    if (salaire <= 0)     { QMessageBox::warning(this, "Manquant", "Salaire > 0.");        return; }

    QSqlQuery q;
    q.prepare("INSERT INTO ZIT.EMPLOYE (NOM, PRENOM, POSTE, SALAIRE, DATE_EMBAUCHE) "
              "VALUES (:nom, :prenom, :poste, :salaire, TO_DATE(:date, 'DD/MM/YYYY'))");
    q.bindValue(":nom", nom); q.bindValue(":prenom", prenom); q.bindValue(":poste", poste);
    q.bindValue(":salaire", salaire); q.bindValue(":date", date.toString("dd/MM/yyyy"));

    if (q.exec()) {
        QMessageBox::information(this, "Succès", "Employé ajouté !");
        ui->inputIdEmploye->clear(); ui->inputNomEmploye->clear();
        ui->inputPrenomEmploye->clear(); ui->inputPosteEmploye->setCurrentIndex(0);
        ui->inputSalaireEmploye->setValue(0);
        ui->inputDateEmbaucheEmploye->setDate(QDate::currentDate());
        afficherEmployes(); mettreAJourStatistiques();
    } else {
        QMessageBox::critical(this, "Erreur", q.lastError().text());
    }
}

// ============================================================
//  MODIFIER
// ============================================================
void MainWindow::modifierEmploye()
{
    QString idStr = ui->inputIdEmploye->text().trimmed();
    if (idStr.isEmpty()) { QMessageBox::warning(this, "Sélection", "Sélectionnez un employé."); return; }

    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();
    QString poste  = ui->inputPosteEmploye->currentText();
    int salaire    = ui->inputSalaireEmploye->value();
    QDate date     = ui->inputDateEmbaucheEmploye->date();

    if (nom.isEmpty())    { QMessageBox::warning(this, "Manquant", "Nom obligatoire.");    return; }
    if (prenom.isEmpty()) { QMessageBox::warning(this, "Manquant", "Prénom obligatoire."); return; }
    if (salaire <= 0)     { QMessageBox::warning(this, "Manquant", "Salaire > 0.");        return; }

    if (QMessageBox::question(this, "Confirmation",
                              QString("Modifier ID %1 : %2 %3 ?").arg(idStr).arg(nom).arg(prenom),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;

    QSqlQuery q;
    q.prepare("UPDATE ZIT.EMPLOYE SET NOM=:nom, PRENOM=:prenom, POSTE=:poste, "
              "SALAIRE=:salaire, DATE_EMBAUCHE=TO_DATE(:date,'DD/MM/YYYY') WHERE ID_EMPLOYE=:id");
    q.bindValue(":nom", nom); q.bindValue(":prenom", prenom); q.bindValue(":poste", poste);
    q.bindValue(":salaire", salaire); q.bindValue(":date", date.toString("dd/MM/yyyy"));
    q.bindValue(":id", idStr.toInt());

    if (q.exec()) {
        QMessageBox::information(this, "Succès", "Employé modifié !");
        ui->inputIdEmploye->clear(); ui->inputNomEmploye->clear();
        ui->inputPrenomEmploye->clear(); ui->inputPosteEmploye->setCurrentIndex(0);
        ui->inputSalaireEmploye->setValue(0);
        ui->inputDateEmbaucheEmploye->setDate(QDate::currentDate());
        afficherEmployes(); mettreAJourStatistiques();
    } else {
        QMessageBox::critical(this, "Erreur", q.lastError().text());
    }
}

// ============================================================
//  SUPPRIMER
// ============================================================
void MainWindow::supprimerEmploye()
{
    QString idStr  = ui->inputIdEmploye->text().trimmed();
    QString nom    = ui->inputNomEmploye->text().trimmed();
    QString prenom = ui->inputPrenomEmploye->text().trimmed();

    if (idStr.isEmpty()) { QMessageBox::warning(this, "Sélection", "Sélectionnez un employé."); return; }

    if (QMessageBox::warning(this, "Confirmation",
                             QString("Supprimer ID %1 : %2 %3 ?\nAction irréversible !").arg(idStr).arg(nom).arg(prenom),
                             QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) return;

    QSqlQuery q;
    q.prepare("DELETE FROM ZIT.EMPLOYE WHERE ID_EMPLOYE = :id");
    q.bindValue(":id", idStr.toInt());

    if (q.exec()) {
        QMessageBox::information(this, "Succès", "Employé supprimé !");
        ui->inputIdEmploye->clear(); ui->inputNomEmploye->clear();
        ui->inputPrenomEmploye->clear(); ui->inputPosteEmploye->setCurrentIndex(0);
        ui->inputSalaireEmploye->setValue(0);
        ui->inputDateEmbaucheEmploye->setDate(QDate::currentDate());
        afficherEmployes(); mettreAJourStatistiques();
    } else {
        QMessageBox::critical(this, "Erreur", q.lastError().text());
    }
}

// ============================================================
//  STATISTIQUES
// ============================================================
void MainWindow::mettreAJourStatistiques()
{
    auto count = [](const QString &where) -> QString {
        QSqlQuery q;
        QString sql = "SELECT COUNT(*) FROM ZIT.EMPLOYE";
        if (!where.isEmpty()) sql += " WHERE " + where;
        return (q.exec(sql) && q.next()) ? q.value(0).toString() : "0";
    };

    ui->valueTotalEmployes->setText(count(""));
    ui->valueOuvriers->setText(count("UPPER(POSTE)='OUVRIER'"));
    ui->valueTechniciens->setText(count("UPPER(POSTE)='TECHNICIEN'"));
    labelNbOperateurs->setText(count("UPPER(POSTE)='OPÉRATEUR'"));
    labelNbControleurs->setText(count("UPPER(POSTE)='CONTRÔLEUR'"));
    labelNbResponsables->setText(count("UPPER(POSTE)='RESPONSABLE'"));

    QSqlQuery qSal;
    labelSalaireMoyen->setText(
        (qSal.exec("SELECT ROUND(AVG(SALAIRE),2) FROM ZIT.EMPLOYE") && qSal.next())
            ? qSal.value(0).toString() + " DT" : "0 DT"
        );
}

// ============================================================
//  EXPORTER PDF  — correction QRectF
// ============================================================
void MainWindow::exporterPDF()
{
    QString fichier = QFileDialog::getSaveFileName(
        this, "Exporter en PDF", "liste_employes.pdf", "PDF (*.pdf)"
        );
    if (fichier.isEmpty()) return;

    QPrinter imprimante(QPrinter::HighResolution);
    imprimante.setOutputFormat(QPrinter::PdfFormat);
    imprimante.setOutputFileName(fichier);
    imprimante.setPageOrientation(QPageLayout::Landscape);
    imprimante.setPageSize(QPageSize::A4);

    QPainter p;
    if (!p.begin(&imprimante)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    // ---- CORRECTION : utiliser QRectF au lieu de QRect ----
    QRectF page = imprimante.pageRect(QPrinter::DevicePixel);
    double W       = page.width();
    double H       = page.height();
    double margeH  = 60;
    double totalW  = W - 2 * margeH;

    // ---- EN-TÊTE ----
    p.setBrush(QColor("#2d4a1f"));
    p.setPen(Qt::NoPen);
    p.drawRect(QRectF(0, 0, W, 130));

    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 22, QFont::Bold));
    p.drawText(QRectF(margeH, 20, totalW, 60),
               Qt::AlignCenter, "ZitTech - Liste des Employés");

    p.setFont(QFont("Arial", 11));
    p.setPen(QColor("#ffd700"));
    p.drawText(QRectF(margeH, 78, totalW, 38),
               Qt::AlignCenter,
               QString("Exporté le : %1   |   Total : %2 employé(s)")
                   .arg(QDate::currentDate().toString("dd/MM/yyyy"))
                   .arg(ui->employeTable->rowCount()));

    // ---- TABLEAU ----
    QStringList entetes = {"ID", "Nom", "Prénom", "Poste", "Salaire (DT)", "Date Embauche"};
    QList<double> ratios = {0.07, 0.18, 0.18, 0.17, 0.17, 0.17};

    double y        = 160;
    double hLigne   = 45;
    double hEntete  = 52;

    // Largeurs colonnes
    QList<double> largeurs;
    for (double r : ratios) largeurs << totalW * r;

    // En-tête tableau
    p.setBrush(QColor("#5d732c"));
    p.setPen(Qt::NoPen);
    p.drawRect(QRectF(margeH, y, totalW, hEntete));

    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 12, QFont::Bold));
    double x = margeH;
    for (int i = 0; i < entetes.size(); i++) {
        p.drawText(QRectF(x + 8, y, largeurs[i] - 8, hEntete),
                   Qt::AlignVCenter | Qt::AlignLeft, entetes[i]);
        x += largeurs[i];
    }
    y += hEntete;

    double yDebutTableau = 160;

    // Lignes de données
    int nbLignes = ui->employeTable->rowCount();
    p.setFont(QFont("Arial", 11));

    for (int row = 0; row < nbLignes; row++) {
        // Nouvelle page si nécessaire
        if (y + hLigne > H - 80) {
            imprimante.newPage();
            y = 60;
            yDebutTableau = y;
            // Répéter en-tête
            p.setBrush(QColor("#5d732c"));
            p.setPen(Qt::NoPen);
            p.drawRect(QRectF(margeH, y, totalW, hEntete));
            p.setPen(Qt::white);
            p.setFont(QFont("Arial", 12, QFont::Bold));
            double xh = margeH;
            for (int i = 0; i < entetes.size(); i++) {
                p.drawText(QRectF(xh + 8, y, largeurs[i] - 8, hEntete),
                           Qt::AlignVCenter | Qt::AlignLeft, entetes[i]);
                xh += largeurs[i];
            }
            y += hEntete;
            p.setFont(QFont("Arial", 11));
        }

        // Fond alterné
        p.setBrush(row % 2 == 0 ? QColor("#f5f9f0") : Qt::white);
        p.setPen(QColor("#d0d8c8"));
        p.drawRect(QRectF(margeH, y, totalW, hLigne));

        // Données
        double xd = margeH;
        for (int col = 0; col < 6; col++) {
            QTableWidgetItem *item = ui->employeTable->item(row, col);
            QString texte = item ? item->text() : "-";

            if (col == 3) {
                if      (texte == "Ouvrier")    p.setPen(QColor("#856404"));
                else if (texte == "Technicien") p.setPen(QColor("#155724"));
                else if (texte == "Opérateur")  p.setPen(QColor("#004085"));
                else if (texte == "Contrôleur") p.setPen(QColor("#721c24"));
                else if (texte == "Responsable")p.setPen(QColor("#4a0072"));
                else                            p.setPen(QColor("#2d4a1f"));
                p.setFont(QFont("Arial", 11, QFont::Bold));
            } else {
                p.setPen(QColor("#2d4a1f"));
                p.setFont(QFont("Arial", 11));
            }

            p.drawText(QRectF(xd + 8, y, largeurs[col] - 8, hLigne),
                       Qt::AlignVCenter | Qt::AlignLeft, texte);
            xd += largeurs[col];
        }
        y += hLigne;
    }

    // Bordure du tableau
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor("#5d732c"));
    p.drawRect(QRectF(margeH, yDebutTableau, totalW, y - yDebutTableau));

    // ---- PIED DE PAGE ----
    p.setBrush(QColor("#f0f4ec"));
    p.setPen(Qt::NoPen);
    p.drawRect(QRectF(0, H - 60, W, 60));
    p.setPen(QColor("#5d732c"));
    p.setFont(QFont("Arial", 10));
    p.drawText(QRectF(margeH, H - 55, totalW, 50),
               Qt::AlignVCenter | Qt::AlignCenter,
               QString("ZitTech - Gestion de Production  |  %1 employé(s)").arg(nbLignes));

    p.end();

    QMessageBox::information(this, "Succès",
                             QString("✅ PDF exporté !\n\n📄 %1").arg(fichier));
}
