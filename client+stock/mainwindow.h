#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientwidget.h"
#include "stockwidget.h"

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
    void on_btnClient_clicked();
    void on_btnStock_clicked();
    void on_btnEmploye_clicked();
    void on_btnMachine_clicked();
    void on_btnProduction_clicked();
    void on_btnCommande_clicked();

private:
    Ui::MainWindow *ui;
    ClientWidget *clientWidget;
    StockWidget *stockWidget;
};

#endif // MAINWINDOW_H
