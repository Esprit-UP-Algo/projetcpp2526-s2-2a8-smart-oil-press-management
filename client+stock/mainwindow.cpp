#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Créer les widgets pour chaque page
    clientWidget = new ClientWidget(this);
    stockWidget = new StockWidget(this);
    
    // Ajouter les widgets au StackedWidget
    ui->stackedWidget->addWidget(clientWidget);  // Index 0
    ui->stackedWidget->addWidget(stockWidget);   // Index 1
    
    // Afficher la page Client par défaut
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClient_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);  // Afficher la page Client
    ui->headerTitle->setText("Gestion des Clients");
}

void MainWindow::on_btnStock_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);  // Afficher la page Stock
    ui->headerTitle->setText("Gestion du Stock");
}

void MainWindow::on_btnEmploye_clicked()
{
    // À implémenter plus tard
    ui->headerTitle->setText("Gestion des Employés");
}

void MainWindow::on_btnMachine_clicked()
{
    // À implémenter plus tard
    ui->headerTitle->setText("Gestion des Machines");
}

void MainWindow::on_btnProduction_clicked()
{
    // À implémenter plus tard
    ui->headerTitle->setText("Gestion de la Production");
}

void MainWindow::on_btnCommande_clicked()
{
    // À implémenter plus tard
    ui->headerTitle->setText("Gestion des Commandes");
}
