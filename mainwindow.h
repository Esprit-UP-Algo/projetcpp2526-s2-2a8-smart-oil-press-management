#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "machine.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void on_btnEmploye_clicked();
    void on_btnClient_clicked();
    void on_btnStock_clicked();
    void on_btnMachine_clicked();
    void on_btnProduction_clicked();
    void on_btnPartenaire_clicked();

    // CRUD Employé
    void on_btnAddEmploye_clicked();
    void on_btnUpdateEmploye_clicked();
    void on_btnDeleteEmploye_clicked();
    void on_btnRefreshEmploye_clicked();
    void on_employeTable_clicked(const QModelIndex &index);

    // Recherche Employé
    void on_btnSearchEmploye_clicked();
    void on_btnClearEmploye_clicked();
    void on_searchBoxEmploye_textChanged(const QString &text);

    // Statistiques - changement d'onglet
    void on_tabWidgetEmploye_currentChanged(int index);

    // Export PDF Employé
    void exporterEmployesPDF();

    // CRUD Machine
    void on_btnAddMachine_clicked();
    void on_btnUpdateMachine_clicked();
    void on_btnDeleteMachine_clicked();
    void on_btnRefreshMachine_clicked();
    void on_machineTable_clicked(const QModelIndex &index);

    // Recherche Machine
    void on_btnSearchMachine_clicked();
    void on_btnClearMachine_clicked();
    void on_searchBoxMachine_textChanged(const QString &text);

    // Export PDF Machine
    void exporterMachinesPDF();

private:
    Ui::MainWindow *ui;
    Employe emp;
    Machine mach;

    void chargerEmployes();
    void viderFormulaireEmploye();
    void chargerStatistiquesEmployes();

    void chargerMachines();
    void viderFormulaireMachine();
};

#endif // MAINWINDOW_H
