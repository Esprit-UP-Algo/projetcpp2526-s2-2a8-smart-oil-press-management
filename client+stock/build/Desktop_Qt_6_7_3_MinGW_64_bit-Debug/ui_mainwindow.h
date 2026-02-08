/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QFrame *sidebar;
    QVBoxLayout *sidebarLayout;
    QLabel *logoLabel;
    QSpacerItem *spacerItem;
    QPushButton *btnEmploye;
    QPushButton *btnClient;
    QPushButton *btnStock;
    QPushButton *btnMachine;
    QPushButton *btnProduction;
    QPushButton *btnCommande;
    QSpacerItem *spacerItem1;
    QPushButton *btnSetting;
    QPushButton *btnLogout;
    QFrame *contentArea;
    QVBoxLayout *contentLayout;
    QFrame *headerFrame;
    QHBoxLayout *headerLayout;
    QLabel *headerTitle;
    QSpacerItem *spacerItem2;
    QLabel *userIconHeader;
    QStackedWidget *stackedWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 988);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logo.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"/* Main Widget */\n"
"QMainWindow#MainWindow {\n"
"    background: #f5f5f5;\n"
"}\n"
"\n"
"/* LEFT SIDEBAR */\n"
"QFrame#sidebar {\n"
"    background-color: #2d4a1f;\n"
"    border: none;\n"
"}\n"
"\n"
"/* Navigation Buttons */\n"
"QPushButton.navButton {\n"
"    background: #b39609;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 20px;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton.navButton:hover {\n"
"    background: #c9a80a;\n"
"}\n"
"\n"
"QPushButton.settingsButton {\n"
"    background: transparent;\n"
"    color: #b39609;\n"
"    border: none;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton.settingsButton:hover {\n"
"    color: #c9a80a;\n"
"}\n"
"\n"
"/* RIGHT PANEL */\n"
"QFrame#contentArea {\n"
"    background-color: #ffffff;\n"
"    border-left: 3px solid #5d732c;\n"
"}\n"
"\n"
"/* Header */\n"
"QFrame#headerFrame {\n"
"    background: #ffffff"
                        ";\n"
"    border: none;\n"
"    border-bottom: 3px solid #5d732c;\n"
"}\n"
"\n"
"QLabel#headerTitle {\n"
"    color: #2d4a1f;\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"}\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(200, 0));
        sidebar->setMaximumSize(QSize(200, 16777215));
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setSpacing(10);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(15, 15, 15, 15);
        logoLabel = new QLabel(sidebar);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(170, 110));
        logoLabel->setMaximumSize(QSize(180, 100));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(logoLabel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacerItem);

        btnEmploye = new QPushButton(sidebar);
        btnEmploye->setObjectName("btnEmploye");

        sidebarLayout->addWidget(btnEmploye);

        btnClient = new QPushButton(sidebar);
        btnClient->setObjectName("btnClient");

        sidebarLayout->addWidget(btnClient);

        btnStock = new QPushButton(sidebar);
        btnStock->setObjectName("btnStock");

        sidebarLayout->addWidget(btnStock);

        btnMachine = new QPushButton(sidebar);
        btnMachine->setObjectName("btnMachine");

        sidebarLayout->addWidget(btnMachine);

        btnProduction = new QPushButton(sidebar);
        btnProduction->setObjectName("btnProduction");

        sidebarLayout->addWidget(btnProduction);

        btnCommande = new QPushButton(sidebar);
        btnCommande->setObjectName("btnCommande");

        sidebarLayout->addWidget(btnCommande);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacerItem1);

        btnSetting = new QPushButton(sidebar);
        btnSetting->setObjectName("btnSetting");

        sidebarLayout->addWidget(btnSetting);

        btnLogout = new QPushButton(sidebar);
        btnLogout->setObjectName("btnLogout");

        sidebarLayout->addWidget(btnLogout);


        mainLayout->addWidget(sidebar);

        contentArea = new QFrame(centralwidget);
        contentArea->setObjectName("contentArea");
        contentLayout = new QVBoxLayout(contentArea);
        contentLayout->setSpacing(0);
        contentLayout->setObjectName("contentLayout");
        contentLayout->setContentsMargins(0, 0, 0, 0);
        headerFrame = new QFrame(contentArea);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setMinimumSize(QSize(0, 80));
        headerLayout = new QHBoxLayout(headerFrame);
        headerLayout->setSpacing(20);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(20, 20, 20, 20);
        headerTitle = new QLabel(headerFrame);
        headerTitle->setObjectName("headerTitle");

        headerLayout->addWidget(headerTitle);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(spacerItem2);

        userIconHeader = new QLabel(headerFrame);
        userIconHeader->setObjectName("userIconHeader");

        headerLayout->addWidget(userIconHeader);


        contentLayout->addWidget(headerFrame);

        stackedWidget = new QStackedWidget(contentArea);
        stackedWidget->setObjectName("stackedWidget");

        contentLayout->addWidget(stackedWidget);


        mainLayout->addWidget(contentArea);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZitTech - Gestion", nullptr));
        logoLabel->setText(QString());
        btnEmploye->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnEmploye->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        btnClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnClient->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        btnStock->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnStock->setText(QCoreApplication::translate("MainWindow", " Stock", nullptr));
        btnMachine->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnMachine->setText(QCoreApplication::translate("MainWindow", " Machines", nullptr));
        btnProduction->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnProduction->setText(QCoreApplication::translate("MainWindow", " Production", nullptr));
        btnCommande->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #b39609; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnCommande->setText(QCoreApplication::translate("MainWindow", " Partenaires", nullptr));
        btnSetting->setStyleSheet(QCoreApplication::translate("MainWindow", "background: transparent; color: #b39609; border: none; padding: 8px; text-align: left;", nullptr));
        btnSetting->setText(QCoreApplication::translate("MainWindow", "Param\303\250tres", nullptr));
        btnLogout->setStyleSheet(QCoreApplication::translate("MainWindow", "background: transparent; color: #b39609; border: none; padding: 8px; text-align: left;", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", " D\303\251connexion", nullptr));
        headerTitle->setText(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        userIconHeader->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 28px; color: #5d732c;", nullptr));
        userIconHeader->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
