#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "partenaire.h"

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
    void on_addpartenaireButton_clicked();
    void on_deletepartenaireButton_clicked();
    void on_partnersTable_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;

    void chargerPartenaires();
    void chargerEmployesComboBox();       // ← nouveau
    void remplirTable(const QList<Partenaire> &liste);
    void viderFormulaire();
    int  idSelectionne();
};

#endif // MAINWINDOW_H
