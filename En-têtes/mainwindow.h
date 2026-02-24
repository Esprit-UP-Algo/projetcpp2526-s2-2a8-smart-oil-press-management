#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDate>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void afficherEmployes();
    void ajouterEmploye();
    void modifierEmploye();
    void supprimerEmploye();
    void remplirFormulaireEmploye(int row, int column);
    void mettreAJourStatistiques();
    void exporterPDF();

private:
    Ui::MainWindow *ui;

    QLabel *labelNbOperateurs;
    QLabel *labelNbControleurs;
    QLabel *labelNbResponsables;
    QLabel *labelSalaireMoyen;
};

#endif // MAINWINDOW_H
