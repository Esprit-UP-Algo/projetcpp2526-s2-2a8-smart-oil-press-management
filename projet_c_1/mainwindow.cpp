#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecter les boutons de navigation aux pages du StackedWidget
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
    });

    // Afficher la page Production par défaut au démarrage
    ui->stackedWidget->setCurrentWidget(ui->pageProduction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
