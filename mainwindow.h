#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include "production.h"
#include "statproduction.h"
#include "Pdfproduction.h"
#include "partenaire.h"
#include "filtrepartenaire.h"
#include "exporterpartenaire.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ── Production ────────────────────────────────────────────────────────────
    void afficherProductions();
    void afficherStatistiques();

    // ── Partenaire ────────────────────────────────────────────────────────────
    void on_addpartenaireButton_clicked();
    void on_updatepartenaireButton_clicked();
    void on_deletepartenaireButton_clicked();
    void on_partnersTable_itemClicked(QTableWidgetItem *item);
    void on_filterpartenaireButton_clicked();
    void on_exportpartenaireButton_clicked();

private:
    Ui::MainWindow *ui;

    // ── Production objects ────────────────────────────────────────────────────
    Production    prod;
    StatProduction stat;
    PdfProduction  pdf;

    // ── Partenaire helpers ────────────────────────────────────────────────────
    void chargerPartenaires();
    void chargerEmployesComboBox();
    void remplirTable(const QList<Partenaire> &liste);
    void viderFormulaire();
    int  idSelectionne();

    // ── Validation ────────────────────────────────────────────────────────────
    bool validerEmail(const QString &email);
    bool validerTelephone(const QString &telephone);
};

#endif // MAINWINDOW_H
