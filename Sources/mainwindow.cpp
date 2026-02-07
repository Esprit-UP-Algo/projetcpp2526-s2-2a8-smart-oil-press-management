#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Désactiver les connexions automatiques de slots
    // (pour éviter les erreurs "undefined reference")

    // Page par défaut : Employés
    ui->stackedWidget->setCurrentWidget(ui->page);

    // ===== NAVIGATION =====

    connect(ui->btnEmploye, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->page);
    });

    connect(ui->btnEmployé, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
