/********************************************************************************
** Form generated from reading UI file 'huiledolive.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUILEDOLIVE_H
#define UI_HUILEDOLIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HuileDolive
{
public:
    QHBoxLayout *mainLayout;
    QFrame *sidebar;
    QVBoxLayout *sidebarLayout;
    QLabel *userIcon;
    QLabel *userName;
    QLabel *userRole;
    QSpacerItem *spacer1;
    QPushButton *btnAllSales;
    QHBoxLayout *statusLayout;
    QPushButton *btnPending;
    QPushButton *btnCompleted;
    QSpacerItem *spacer2;
    QPushButton *btnEmploye;
    QPushButton *btnClient;
    QPushButton *btnStock;
    QPushButton *btnMachine;
    QPushButton *btnProduction;
    QPushButton *btnCommande;
    QSpacerItem *spacer3;
    QLabel *bottomAvatar;
    QSpacerItem *spacer4;
    QPushButton *btnSetting;
    QPushButton *btnLogout;
    QFrame *clientPanel;
    QVBoxLayout *clientLayout;
    QLabel *clientPanelTitle;
    QLineEdit *searchBox;
    QListWidget *clientList;
    QFrame *contentArea;
    QVBoxLayout *contentLayout;
    QFrame *headerFrame;
    QHBoxLayout *headerLayout;
    QVBoxLayout *headerTextLayout;
    QLabel *headerTitle;
    QLabel *headerSubtitle;
    QSpacerItem *headerSpacer;
    QLabel *logoLabel;
    QFrame *infoCard;
    QVBoxLayout *infoLayout;
    QLabel *infoTitle;
    QListWidget *infoList;
    QFrame *statsCard;
    QVBoxLayout *statsLayout;
    QLabel *statsTitle;
    QListWidget *statsList;

    void setupUi(QWidget *HuileDolive)
    {
        if (HuileDolive->objectName().isEmpty())
            HuileDolive->setObjectName("HuileDolive");
        HuileDolive->resize(1400, 874);
        HuileDolive->setStyleSheet(QString::fromUtf8("/* Main Widget */\n"
"QWidget#HuileDolive { \n"
"    background: #f5f5f5;\n"
"}\n"
"\n"
"/* LEFT SIDEBAR - Navigation */\n"
"QFrame#sidebar {\n"
"    background-color: #2d4a1f;\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel#userName {\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#userRole {\n"
"    color: #c9c9c9;\n"
"    font-size: 12px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLabel#userIcon, QLabel#bottomAvatar {\n"
"    font-size: 32px;\n"
"    background: transparent;\n"
"    color: #d4af37;\n"
"}\n"
"\n"
"/* Navigation Buttons - OLIVE GREEN AND GOLD */\n"
"QPushButton#btnAllSales {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6B8E23, stop:1 #808000);\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 15px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton#btnAllSales:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x"
                        "2:1, y2:0, stop:0 #7fa92e, stop:1 #8d9310);\n"
"}\n"
"\n"
"QPushButton#btnPending, QPushButton#btnCompleted {\n"
"    background: transparent;\n"
"    color: white;\n"
"    border: 1px solid #6B8E23;\n"
"    padding: 6px 12px;\n"
"    border-radius: 12px;\n"
"    font-size: 11px;\n"
"}\n"
"\n"
"QPushButton#btnPending:hover, QPushButton#btnCompleted:hover {\n"
"    background: rgba(107, 142, 35, 0.2);\n"
"}\n"
"\n"
"QPushButton.navButton {\n"
"    background: #d4af37;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 15px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton#btnEmploye, QPushButton#btnClient, QPushButton#btnStock, QPushButton#btnMachine, QPushButton#btnProduction, QPushButton#btnCommande {\n"
"    background: #d4af37;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 15px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton#btnEmploye:hover, QPushButton#bt"
                        "nClient:hover, QPushButton#btnStock:hover, QPushButton#btnMachine:hover, QPushButton#btnProduction:hover, QPushButton#btnCommande:hover {\n"
"    background: #e6c041;\n"
"}\n"
"\n"
"QPushButton#btnSetting, QPushButton#btnLogout {\n"
"    background: transparent;\n"
"    color: #d4af37;\n"
"    border: none;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton#btnSetting:hover, QPushButton#btnLogout:hover {\n"
"    color: #e6c041;\n"
"}\n"
"\n"
"/* MIDDLE PANEL - Client List - OLIVE GREEN */\n"
"QFrame#clientPanel {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6B8E23, stop:1 #556B2F);\n"
"    border-right: 3px solid #d4af37;\n"
"}\n"
"\n"
"QLabel#clientPanelTitle {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QLineEdit#searchBox {\n"
"    padding: 10px 15px;\n"
"    border: 2px solid #d4af37;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"    font-size: 1"
                        "3px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QLineEdit#searchBox::placeholder {\n"
"    color: #888;\n"
"}\n"
"\n"
"QListWidget#clientList {\n"
"    background: rgba(255, 255, 255, 0.95);\n"
"    border: 2px solid #d4af37;\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QListWidget#clientList::item {\n"
"    padding: 12px;\n"
"    border-bottom: 1px solid #e0e0e0;\n"
"    border-radius: 6px;\n"
"    background: white;\n"
"    margin: 3px;\n"
"}\n"
"\n"
"QListWidget#clientList::item:hover {\n"
"    background: #fff4d6;\n"
"    border: 1px solid #d4af37;\n"
"}\n"
"\n"
"QListWidget#clientList::item:selected {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #d4af37, stop:1 #c9a02c);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border: 2px solid #b8941f;\n"
"}\n"
"\n"
"/* RIGHT PANEL */\n"
"QFrame#contentArea {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    font-size: 24px;\n"
"    font-wei"
                        "ght: bold;\n"
"    color: #556B2F;\n"
"}\n"
"\n"
"QLabel#logoLabel {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #d4af37;\n"
"}\n"
"\n"
"/* Info and Stats Cards */\n"
"QFrame#infoCard, QFrame#statsCard {\n"
"    background: #ffffff;\n"
"    border: 3px solid #d4af37;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"QLabel.cardTitle {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #556B2F;\n"
"    background: transparent;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QListWidget#infoList, QListWidget#statsList {\n"
"    background: #fefffe;\n"
"    border: 1px solid #e8e8e8;\n"
"    border-radius: 6px;\n"
"    padding: 8px;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QListWidget#infoList::item, QListWidget#statsList::item {\n"
"    padding: 10px;\n"
"    border-bottom: 1px solid #f5f5f5;\n"
"}\n"
"\n"
"/* Header Frame - OLIVE GREEN */\n"
"QFrame#headerFrame {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6B8E23, stop:1 #808000);\n"
"    bor"
                        "der-radius: 10px;\n"
"}\n"
"\n"
"QLabel#headerTitle {\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel#headerSubtitle {\n"
"    color: #d4af37;\n"
"    font-size: 14px;\n"
"}\n"
""));
        mainLayout = new QHBoxLayout(HuileDolive);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QFrame(HuileDolive);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(200, 0));
        sidebar->setMaximumSize(QSize(200, 16777215));
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setSpacing(10);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(15, 20, 15, 20);
        userIcon = new QLabel(sidebar);
        userIcon->setObjectName("userIcon");
        userIcon->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(userIcon);

        userName = new QLabel(sidebar);
        userName->setObjectName("userName");

        sidebarLayout->addWidget(userName);

        userRole = new QLabel(sidebar);
        userRole->setObjectName("userRole");

        sidebarLayout->addWidget(userRole);

        spacer1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacer1);

        btnAllSales = new QPushButton(sidebar);
        btnAllSales->setObjectName("btnAllSales");

        sidebarLayout->addWidget(btnAllSales);

        statusLayout = new QHBoxLayout();
        statusLayout->setObjectName("statusLayout");
        btnPending = new QPushButton(sidebar);
        btnPending->setObjectName("btnPending");

        statusLayout->addWidget(btnPending);

        btnCompleted = new QPushButton(sidebar);
        btnCompleted->setObjectName("btnCompleted");

        statusLayout->addWidget(btnCompleted);


        sidebarLayout->addLayout(statusLayout);

        spacer2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacer2);

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

        spacer3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacer3);

        bottomAvatar = new QLabel(sidebar);
        bottomAvatar->setObjectName("bottomAvatar");
        bottomAvatar->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(bottomAvatar);

        spacer4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacer4);

        btnSetting = new QPushButton(sidebar);
        btnSetting->setObjectName("btnSetting");

        sidebarLayout->addWidget(btnSetting);

        btnLogout = new QPushButton(sidebar);
        btnLogout->setObjectName("btnLogout");

        sidebarLayout->addWidget(btnLogout);


        mainLayout->addWidget(sidebar);

        clientPanel = new QFrame(HuileDolive);
        clientPanel->setObjectName("clientPanel");
        clientPanel->setMinimumSize(QSize(280, 0));
        clientPanel->setMaximumSize(QSize(280, 16777215));
        clientLayout = new QVBoxLayout(clientPanel);
        clientLayout->setSpacing(15);
        clientLayout->setObjectName("clientLayout");
        clientLayout->setContentsMargins(15, 20, 15, 20);
        clientPanelTitle = new QLabel(clientPanel);
        clientPanelTitle->setObjectName("clientPanelTitle");

        clientLayout->addWidget(clientPanelTitle);

        searchBox = new QLineEdit(clientPanel);
        searchBox->setObjectName("searchBox");

        clientLayout->addWidget(searchBox);

        clientList = new QListWidget(clientPanel);
        clientList->setObjectName("clientList");

        clientLayout->addWidget(clientList);


        mainLayout->addWidget(clientPanel);

        contentArea = new QFrame(HuileDolive);
        contentArea->setObjectName("contentArea");
        contentLayout = new QVBoxLayout(contentArea);
        contentLayout->setSpacing(20);
        contentLayout->setObjectName("contentLayout");
        contentLayout->setContentsMargins(25, 25, 25, 25);
        headerFrame = new QFrame(contentArea);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setMinimumSize(QSize(0, 80));
        headerFrame->setMaximumSize(QSize(16777215, 80));
        headerLayout = new QHBoxLayout(headerFrame);
        headerLayout->setSpacing(20);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(20, 15, 20, 15);
        headerTextLayout = new QVBoxLayout();
        headerTextLayout->setSpacing(5);
        headerTextLayout->setObjectName("headerTextLayout");
        headerTitle = new QLabel(headerFrame);
        headerTitle->setObjectName("headerTitle");

        headerTextLayout->addWidget(headerTitle);

        headerSubtitle = new QLabel(headerFrame);
        headerSubtitle->setObjectName("headerSubtitle");

        headerTextLayout->addWidget(headerSubtitle);


        headerLayout->addLayout(headerTextLayout);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        logoLabel = new QLabel(headerFrame);
        logoLabel->setObjectName("logoLabel");

        headerLayout->addWidget(logoLabel);


        contentLayout->addWidget(headerFrame);

        infoCard = new QFrame(contentArea);
        infoCard->setObjectName("infoCard");
        infoLayout = new QVBoxLayout(infoCard);
        infoLayout->setSpacing(12);
        infoLayout->setObjectName("infoLayout");
        infoLayout->setContentsMargins(20, 20, 20, 20);
        infoTitle = new QLabel(infoCard);
        infoTitle->setObjectName("infoTitle");
        infoTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #556B2F; background: transparent; padding: 10px;"));

        infoLayout->addWidget(infoTitle);

        infoList = new QListWidget(infoCard);
        infoList->setObjectName("infoList");
        infoList->setMinimumSize(QSize(0, 250));

        infoLayout->addWidget(infoList);


        contentLayout->addWidget(infoCard);

        statsCard = new QFrame(contentArea);
        statsCard->setObjectName("statsCard");
        statsLayout = new QVBoxLayout(statsCard);
        statsLayout->setSpacing(12);
        statsLayout->setObjectName("statsLayout");
        statsLayout->setContentsMargins(20, 20, 20, 20);
        statsTitle = new QLabel(statsCard);
        statsTitle->setObjectName("statsTitle");
        statsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; color: #556B2F; background: transparent; padding: 10px;"));

        statsLayout->addWidget(statsTitle);

        statsList = new QListWidget(statsCard);
        statsList->setObjectName("statsList");
        statsList->setMinimumSize(QSize(0, 250));

        statsLayout->addWidget(statsList);


        contentLayout->addWidget(statsCard);


        mainLayout->addWidget(contentArea);


        retranslateUi(HuileDolive);

        QMetaObject::connectSlotsByName(HuileDolive);
    } // setupUi

    void retranslateUi(QWidget *HuileDolive)
    {
        HuileDolive->setWindowTitle(QCoreApplication::translate("HuileDolive", "Presse Huile Olive", nullptr));
        userIcon->setText(QCoreApplication::translate("HuileDolive", "USER", nullptr));
        userName->setText(QCoreApplication::translate("HuileDolive", "bruce wayne", nullptr));
        userRole->setText(QCoreApplication::translate("HuileDolive", "@complexcode", nullptr));
        btnAllSales->setText(QCoreApplication::translate("HuileDolive", "All Sales", nullptr));
        btnPending->setText(QCoreApplication::translate("HuileDolive", "Pending", nullptr));
        btnCompleted->setText(QCoreApplication::translate("HuileDolive", "Completed", nullptr));
        btnEmploye->setText(QCoreApplication::translate("HuileDolive", "employe", nullptr));
        btnClient->setText(QCoreApplication::translate("HuileDolive", "client", nullptr));
        btnStock->setText(QCoreApplication::translate("HuileDolive", "stock", nullptr));
        btnMachine->setText(QCoreApplication::translate("HuileDolive", "machine", nullptr));
        btnProduction->setText(QCoreApplication::translate("HuileDolive", "production", nullptr));
        btnCommande->setText(QCoreApplication::translate("HuileDolive", "commande", nullptr));
        bottomAvatar->setText(QCoreApplication::translate("HuileDolive", "AVATAR", nullptr));
        btnSetting->setText(QCoreApplication::translate("HuileDolive", "Setting", nullptr));
        btnLogout->setText(QCoreApplication::translate("HuileDolive", "Log Out", nullptr));
        clientPanelTitle->setText(QCoreApplication::translate("HuileDolive", "Liste des machines", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("HuileDolive", "Rechercher...", nullptr));
        headerTitle->setText(QCoreApplication::translate("HuileDolive", "Presse a Huile d'Olive", nullptr));
        headerSubtitle->setText(QCoreApplication::translate("HuileDolive", "Gestion des machines", nullptr));
        logoLabel->setText(QCoreApplication::translate("HuileDolive", "EZYTech", nullptr));
        infoTitle->setText(QCoreApplication::translate("HuileDolive", "Informations du machine", nullptr));
        statsTitle->setText(QCoreApplication::translate("HuileDolive", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HuileDolive: public Ui_HuileDolive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUILEDOLIVE_H
