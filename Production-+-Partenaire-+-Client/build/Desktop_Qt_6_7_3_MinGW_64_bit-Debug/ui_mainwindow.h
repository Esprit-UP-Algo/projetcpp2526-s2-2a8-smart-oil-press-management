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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
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
    QLabel *label;
    QSpacerItem *spacerItem;
    QPushButton *btnEmploye;
    QPushButton *btnClient;
    QPushButton *btnStock;
    QPushButton *btnMachine;
    QPushButton *btnProduction;
    QPushButton *btnPartenaire;
    QSpacerItem *spacerItem1;
    QPushButton *btnSetting;
    QPushButton *btnLogout;
    QStackedWidget *stackedWidget;
    QWidget *pageEmploye;
    QVBoxLayout *verticalLayout_2;
    QFrame *headerFrameEmploye;
    QHBoxLayout *horizontalLayout_2;
    QLabel *headerTitleEmploye;
    QSpacerItem *horizontalSpacer_2;
    QLabel *userIconHeaderEmploye;
    QLabel *placeholderEmploye;
    QWidget *pageClient;
    QVBoxLayout *verticalLayout_3;
    QFrame *headerFrameClient;
    QHBoxLayout *horizontalLayout_3;
    QLabel *headerTitleClient;
    QSpacerItem *horizontalSpacer_3;
    QLabel *userIconHeaderClient;
    QTabWidget *tabWidgetClient;
    QWidget *clientListTab;
    QVBoxLayout *tab1Layout;
    QHBoxLayout *searchLayout;
    QPushButton *btnRefreshClient;
    QPushButton *btnClearClient;
    QLineEdit *searchBoxClient;
    QPushButton *btnSearchClient;
    QHBoxLayout *splitLayoutClient;
    QTableWidget *clientTable;
    QFrame *formPanelClient;
    QVBoxLayout *formLayoutClient;
    QLabel *labelFormTitleClient;
    QLabel *labelIdClient;
    QLineEdit *inputIdClient;
    QLabel *labelNomClient;
    QLineEdit *inputNomClient;
    QLabel *labelPrenomClient;
    QLineEdit *inputPrenomClient;
    QLabel *labelEmailClient;
    QLineEdit *inputEmailClient;
    QLabel *labelTelephoneClient;
    QLineEdit *inputTelephoneClient;
    QLabel *labelTypeClient;
    QComboBox *inputTypeClient;
    QLabel *labelFeedbackClient;
    QTextEdit *inputFeedbackClient;
    QSpacerItem *spacerItem2;
    QHBoxLayout *formButtonsClient;
    QPushButton *btnAddClient;
    QPushButton *btnUpdateClient;
    QPushButton *btnDeleteClient;
    QWidget *clientStatsTab;
    QVBoxLayout *tab2LayoutClient;
    QLabel *statsLabelClient;
    QHBoxLayout *statsCardsLayoutClient;
    QFrame *cardTotalClients;
    QVBoxLayout *vboxLayout;
    QLabel *labelTotalClients;
    QLabel *valueTotalClients;
    QFrame *cardParticuliers;
    QVBoxLayout *vboxLayout1;
    QLabel *labelParticuliers;
    QLabel *valueParticuliers;
    QFrame *cardEntreprises;
    QVBoxLayout *vboxLayout2;
    QLabel *labelEntreprises;
    QLabel *valueEntreprises;
    QSpacerItem *spacerItem3;
    QWidget *pageStock;
    QVBoxLayout *verticalLayout_4;
    QFrame *headerFrameStock;
    QHBoxLayout *horizontalLayout_4;
    QLabel *headerTitleStock;
    QSpacerItem *horizontalSpacer_4;
    QLabel *userIconHeaderStock;
    QLabel *placeholderStock;
    QWidget *pageMachine;
    QVBoxLayout *verticalLayout_5;
    QFrame *headerFrameMachine;
    QHBoxLayout *horizontalLayout_5;
    QLabel *headerTitleMachine;
    QSpacerItem *horizontalSpacer_5;
    QLabel *userIconHeaderMachine;
    QLabel *placeholderMachine;
    QWidget *pageProduction;
    QVBoxLayout *contentLayout;
    QFrame *headerFrame;
    QHBoxLayout *headerLayout;
    QLabel *headerTitle;
    QSpacerItem *spacerItem4;
    QLabel *userIconHeader;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *tab1Layout1;
    QHBoxLayout *searchLayout1;
    QPushButton *btnRefresh;
    QPushButton *btnClear;
    QLineEdit *searchBox;
    QPushButton *btnSearch;
    QPushButton *btnExportPDF;
    QHBoxLayout *splitLayout;
    QTableWidget *productionTable;
    QFrame *formPanel;
    QVBoxLayout *formLayout;
    QLabel *labelFormTitle;
    QLabel *labelDate;
    QDateEdit *inputDate;
    QLabel *labelQuantiteOlive;
    QDoubleSpinBox *inputQuantiteOlive;
    QLabel *labelQuantiteHuile;
    QDoubleSpinBox *inputQuantiteHuile;
    QLabel *labelRendement;
    QLineEdit *inputRendement;
    QSpacerItem *spacerItem5;
    QHBoxLayout *formButtons;
    QPushButton *btnAdd;
    QPushButton *btnUpdate;
    QPushButton *btnDelete;
    QWidget *tab2;
    QVBoxLayout *tab2Layout;
    QLabel *statsTitle;
    QHBoxLayout *statsCards;
    QFrame *cardTotal;
    QVBoxLayout *vboxLayout3;
    QLabel *labelTotal;
    QLabel *valueTotal;
    QFrame *cardOlives;
    QVBoxLayout *vboxLayout4;
    QLabel *labelOlives;
    QLabel *valueOlives;
    QFrame *cardHuile;
    QVBoxLayout *vboxLayout5;
    QLabel *labelHuile;
    QLabel *valueHuile;
    QFrame *cardRendement;
    QVBoxLayout *vboxLayout6;
    QLabel *labelRendement1;
    QLabel *valueRendement;
    QSpacerItem *spacerItem6;
    QWidget *tab3;
    QVBoxLayout *tab3Layout;
    QLabel *predTitle;
    QFrame *predFrame;
    QVBoxLayout *predLayout;
    QHBoxLayout *hboxLayout;
    QLabel *labelPredInput;
    QDoubleSpinBox *inputPredOlives;
    QPushButton *btnPredict;
    QFrame *predResult;
    QVBoxLayout *vboxLayout7;
    QLabel *valuePredRendement;
    QLabel *valuePredHuile;
    QSpacerItem *spacerItem7;
    QWidget *tab4;
    QVBoxLayout *tab4Layout;
    QLabel *anomalyTitle;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnAnalyze;
    QSpacerItem *spacerItem8;
    QLabel *labelThreshold;
    QSpinBox *inputThreshold;
    QTableWidget *anomalyTable;
    QWidget *pagePartenaire;
    QVBoxLayout *verticalLayout_6;
    QFrame *headerFramePartenaire;
    QHBoxLayout *horizontalLayout_6;
    QLabel *headerTitlePartenaire;
    QSpacerItem *horizontalSpacer_6;
    QLabel *userIconHeaderPartenaire;
    QTabWidget *tabWidgetPartenaire;
    QWidget *partnersListTab;
    QVBoxLayout *vboxLayout8;
    QHBoxLayout *hboxLayout2;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *exportButton;
    QPushButton *filterButton;
    QHBoxLayout *hboxLayout3;
    QTableWidget *partnersTable;
    QFrame *formFramePartenaire;
    QVBoxLayout *vboxLayout9;
    QLabel *formTitleLabel;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QLabel *statusLabel;
    QComboBox *statusComboBox;
    QSpacerItem *spacerItem9;
    QHBoxLayout *hboxLayout4;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QWidget *statsTab;
    QVBoxLayout *vboxLayout10;
    QLabel *statsHeaderLabel;
    QHBoxLayout *statsCardsLayout;
    QFrame *cardTotalPartenaires;
    QVBoxLayout *vboxLayout11;
    QLabel *labelTotalPartenaires;
    QLabel *valueTotalPartenaires;
    QFrame *cardActifs;
    QVBoxLayout *vboxLayout12;
    QLabel *labelActifs;
    QLabel *valueActifs;
    QFrame *cardInactifs;
    QVBoxLayout *vboxLayout13;
    QLabel *labelInactifs;
    QLabel *valueInactifs;
    QSpacerItem *spacerItem10;
    QWidget *mailingTab;
    QVBoxLayout *vboxLayout14;
    QLabel *mailingHeaderLabel;
    QFrame *mailingFrame;
    QVBoxLayout *vboxLayout15;
    QLabel *subjectLabel;
    QLineEdit *subjectLineEdit;
    QLabel *messageLabel;
    QTextEdit *messageTextEdit;
    QPushButton *sendMailButton;
    QSpacerItem *spacerItem11;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 1018);
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
"QLabel#userIcon {\n"
"    font-size: 32px;\n"
"    background: transparent;\n"
"    color: #ffd700;\n"
"}\n"
"\n"
"/* Navigation Buttons */\n"
"QPushButton.navButton {\n"
"    background: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border: none;\n"
"    padding: 12px 20px;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton.navButton:hover {\n"
"    background: #ffed4e;\n"
"}\n"
"\n"
"QPushButton.settingsButton {\n"
"    background: transparent;\n"
"    color: #ffd700;\n"
"    bo"
                        "rder: none;\n"
"    padding: 8px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"}\n"
"\n"
"QPushButton.settingsButton:hover {\n"
"    color: #ffed4e;\n"
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
"    background: #ffffff;\n"
"    border: none;\n"
"    border-bottom: 3px solid #5d732c;\n"
"}\n"
"\n"
"QLabel#headerTitle {\n"
"    color: #2d4a1f;\n"
"    font-size: 28px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel#headerIcon {\n"
"    color: #5d732c;\n"
"    font-size: 32px;\n"
"}\n"
"\n"
"/* Tab Widget */\n"
"QTabWidget::pane {\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"    top: -2px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #f0f0f0;\n"
"    color: #2d4a1f;\n"
"    padding: 12px 30px;\n"
"    margin-right: 5px;\n"
"    border-top-left-radius: 8px;\n"
"    border-top-right-radius: 8px;\n"
"    font-s"
                        "ize: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #ffd700;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #ffed4e;\n"
"}\n"
"\n"
"/* Search Box */\n"
"QLineEdit#searchBox {\n"
"    padding: 10px 15px;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    background: white;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"/* Action Buttons */\n"
"QPushButton.actionButton {\n"
"    background: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border: none;\n"
"    padding: 10px 15px;\n"
"    border-radius: 6px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton.actionButton:hover {\n"
"    background: #ffed4e;\n"
"}\n"
"\n"
"QPushButton#btnDelete {\n"
"    background: #dc3545;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#btnDelete:hover {\n"
"    background: #c82333;\n"
"}\n"
"\n"
"/* Table */\n"
"QTableWidget {\n"
"    background: white;\n"
"    border: 2px solid #5d732c;\n"
"  "
                        "  border-radius: 8px;\n"
"    gridline-color: #e0e0e0;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background: #ffd700;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background: #5d732c;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"/* Form Panel */\n"
"QFrame#formPanel {\n"
"    background: white;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QLabel.formLabel {\n"
"    color: #2d4a1f;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLineEdit.formInput,\n"
"QComboBox.formInput,\n"
"QSpinBox.formInput,\n"
"QDoubleSpinBox.formInput,\n"
"QDateEdit.formInput {\n"
"    padding: 8px 12px;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    background: white;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"/* Form Buttons */\n"
"QPushButton.formButton {\n"
"    back"
                        "ground: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border: none;\n"
"    padding: 12px 30px;\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton.formButton:hover {\n"
"    background: #ffed4e;\n"
"}\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setObjectName("mainLayout");
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumSize(QSize(200, 0));
        sidebar->setMaximumSize(QSize(200, 16777215));
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setSpacing(10);
        sidebarLayout->setObjectName("sidebarLayout");
        logoLabel = new QLabel(sidebar);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(160, 90));
        logoLabel->setMaximumSize(QSize(180, 110));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/resources/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(logoLabel);

        label = new QLabel(sidebar);
        label->setObjectName("label");

        sidebarLayout->addWidget(label);

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

        btnPartenaire = new QPushButton(sidebar);
        btnPartenaire->setObjectName("btnPartenaire");

        sidebarLayout->addWidget(btnPartenaire);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacerItem1);

        btnSetting = new QPushButton(sidebar);
        btnSetting->setObjectName("btnSetting");

        sidebarLayout->addWidget(btnSetting);

        btnLogout = new QPushButton(sidebar);
        btnLogout->setObjectName("btnLogout");

        sidebarLayout->addWidget(btnLogout);


        mainLayout->addWidget(sidebar);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageEmploye = new QWidget();
        pageEmploye->setObjectName("pageEmploye");
        verticalLayout_2 = new QVBoxLayout(pageEmploye);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        headerFrameEmploye = new QFrame(pageEmploye);
        headerFrameEmploye->setObjectName("headerFrameEmploye");
        headerFrameEmploye->setMinimumSize(QSize(0, 80));
        headerFrameEmploye->setStyleSheet(QString::fromUtf8("background: #ffffff; border: none; border-bottom: 3px solid #5d732c;"));
        horizontalLayout_2 = new QHBoxLayout(headerFrameEmploye);
        horizontalLayout_2->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        headerTitleEmploye = new QLabel(headerFrameEmploye);
        headerTitleEmploye->setObjectName("headerTitleEmploye");
        headerTitleEmploye->setStyleSheet(QString::fromUtf8("color: #2d4a1f; font-size: 28px; font-weight: bold;"));

        horizontalLayout_2->addWidget(headerTitleEmploye);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        userIconHeaderEmploye = new QLabel(headerFrameEmploye);
        userIconHeaderEmploye->setObjectName("userIconHeaderEmploye");
        userIconHeaderEmploye->setStyleSheet(QString::fromUtf8("font-size: 28px; color: #5d732c;"));

        horizontalLayout_2->addWidget(userIconHeaderEmploye);


        verticalLayout_2->addWidget(headerFrameEmploye);

        placeholderEmploye = new QLabel(pageEmploye);
        placeholderEmploye->setObjectName("placeholderEmploye");
        placeholderEmploye->setStyleSheet(QString::fromUtf8("font-size: 18px; color: #888; padding: 50px;"));
        placeholderEmploye->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(placeholderEmploye);

        stackedWidget->addWidget(pageEmploye);
        pageClient = new QWidget();
        pageClient->setObjectName("pageClient");
        verticalLayout_3 = new QVBoxLayout(pageClient);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        headerFrameClient = new QFrame(pageClient);
        headerFrameClient->setObjectName("headerFrameClient");
        headerFrameClient->setMinimumSize(QSize(0, 80));
        headerFrameClient->setStyleSheet(QString::fromUtf8("background: #ffffff; border: none; border-bottom: 3px solid #5d732c;"));
        horizontalLayout_3 = new QHBoxLayout(headerFrameClient);
        horizontalLayout_3->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        headerTitleClient = new QLabel(headerFrameClient);
        headerTitleClient->setObjectName("headerTitleClient");
        headerTitleClient->setStyleSheet(QString::fromUtf8("color: #2d4a1f; font-size: 28px; font-weight: bold;"));

        horizontalLayout_3->addWidget(headerTitleClient);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        userIconHeaderClient = new QLabel(headerFrameClient);
        userIconHeaderClient->setObjectName("userIconHeaderClient");
        userIconHeaderClient->setStyleSheet(QString::fromUtf8("font-size: 28px; color: #5d732c;"));

        horizontalLayout_3->addWidget(userIconHeaderClient);


        verticalLayout_3->addWidget(headerFrameClient);

        tabWidgetClient = new QTabWidget(pageClient);
        tabWidgetClient->setObjectName("tabWidgetClient");
        clientListTab = new QWidget();
        clientListTab->setObjectName("clientListTab");
        tab1Layout = new QVBoxLayout(clientListTab);
        tab1Layout->setSpacing(15);
        tab1Layout->setContentsMargins(20, 20, 20, 20);
        tab1Layout->setObjectName("tab1Layout");
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        btnRefreshClient = new QPushButton(clientListTab);
        btnRefreshClient->setObjectName("btnRefreshClient");

        searchLayout->addWidget(btnRefreshClient);

        btnClearClient = new QPushButton(clientListTab);
        btnClearClient->setObjectName("btnClearClient");

        searchLayout->addWidget(btnClearClient);

        searchBoxClient = new QLineEdit(clientListTab);
        searchBoxClient->setObjectName("searchBoxClient");

        searchLayout->addWidget(searchBoxClient);

        btnSearchClient = new QPushButton(clientListTab);
        btnSearchClient->setObjectName("btnSearchClient");

        searchLayout->addWidget(btnSearchClient);


        tab1Layout->addLayout(searchLayout);

        splitLayoutClient = new QHBoxLayout();
        splitLayoutClient->setSpacing(15);
        splitLayoutClient->setObjectName("splitLayoutClient");
        clientTable = new QTableWidget(clientListTab);
        if (clientTable->columnCount() < 6)
            clientTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        clientTable->setObjectName("clientTable");

        splitLayoutClient->addWidget(clientTable);

        formPanelClient = new QFrame(clientListTab);
        formPanelClient->setObjectName("formPanelClient");
        formPanelClient->setMinimumSize(QSize(350, 0));
        formPanelClient->setMaximumSize(QSize(400, 16777215));
        formLayoutClient = new QVBoxLayout(formPanelClient);
        formLayoutClient->setSpacing(12);
        formLayoutClient->setContentsMargins(20, 20, 20, 20);
        formLayoutClient->setObjectName("formLayoutClient");
        labelFormTitleClient = new QLabel(formPanelClient);
        labelFormTitleClient->setObjectName("labelFormTitleClient");
        labelFormTitleClient->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayoutClient->addWidget(labelFormTitleClient);

        labelIdClient = new QLabel(formPanelClient);
        labelIdClient->setObjectName("labelIdClient");

        formLayoutClient->addWidget(labelIdClient);

        inputIdClient = new QLineEdit(formPanelClient);
        inputIdClient->setObjectName("inputIdClient");
        inputIdClient->setReadOnly(true);

        formLayoutClient->addWidget(inputIdClient);

        labelNomClient = new QLabel(formPanelClient);
        labelNomClient->setObjectName("labelNomClient");

        formLayoutClient->addWidget(labelNomClient);

        inputNomClient = new QLineEdit(formPanelClient);
        inputNomClient->setObjectName("inputNomClient");

        formLayoutClient->addWidget(inputNomClient);

        labelPrenomClient = new QLabel(formPanelClient);
        labelPrenomClient->setObjectName("labelPrenomClient");

        formLayoutClient->addWidget(labelPrenomClient);

        inputPrenomClient = new QLineEdit(formPanelClient);
        inputPrenomClient->setObjectName("inputPrenomClient");

        formLayoutClient->addWidget(inputPrenomClient);

        labelEmailClient = new QLabel(formPanelClient);
        labelEmailClient->setObjectName("labelEmailClient");

        formLayoutClient->addWidget(labelEmailClient);

        inputEmailClient = new QLineEdit(formPanelClient);
        inputEmailClient->setObjectName("inputEmailClient");

        formLayoutClient->addWidget(inputEmailClient);

        labelTelephoneClient = new QLabel(formPanelClient);
        labelTelephoneClient->setObjectName("labelTelephoneClient");

        formLayoutClient->addWidget(labelTelephoneClient);

        inputTelephoneClient = new QLineEdit(formPanelClient);
        inputTelephoneClient->setObjectName("inputTelephoneClient");

        formLayoutClient->addWidget(inputTelephoneClient);

        labelTypeClient = new QLabel(formPanelClient);
        labelTypeClient->setObjectName("labelTypeClient");

        formLayoutClient->addWidget(labelTypeClient);

        inputTypeClient = new QComboBox(formPanelClient);
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->setObjectName("inputTypeClient");

        formLayoutClient->addWidget(inputTypeClient);

        labelFeedbackClient = new QLabel(formPanelClient);
        labelFeedbackClient->setObjectName("labelFeedbackClient");

        formLayoutClient->addWidget(labelFeedbackClient);

        inputFeedbackClient = new QTextEdit(formPanelClient);
        inputFeedbackClient->setObjectName("inputFeedbackClient");
        inputFeedbackClient->setMinimumSize(QSize(0, 60));
        inputFeedbackClient->setMaximumSize(QSize(16777215, 80));

        formLayoutClient->addWidget(inputFeedbackClient);

        spacerItem2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayoutClient->addItem(spacerItem2);

        formButtonsClient = new QHBoxLayout();
        formButtonsClient->setSpacing(8);
        formButtonsClient->setObjectName("formButtonsClient");
        btnAddClient = new QPushButton(formPanelClient);
        btnAddClient->setObjectName("btnAddClient");
        btnAddClient->setMinimumSize(QSize(0, 40));

        formButtonsClient->addWidget(btnAddClient);

        btnUpdateClient = new QPushButton(formPanelClient);
        btnUpdateClient->setObjectName("btnUpdateClient");
        btnUpdateClient->setMinimumSize(QSize(0, 40));

        formButtonsClient->addWidget(btnUpdateClient);

        btnDeleteClient = new QPushButton(formPanelClient);
        btnDeleteClient->setObjectName("btnDeleteClient");
        btnDeleteClient->setMinimumSize(QSize(0, 40));

        formButtonsClient->addWidget(btnDeleteClient);


        formLayoutClient->addLayout(formButtonsClient);


        splitLayoutClient->addWidget(formPanelClient);


        tab1Layout->addLayout(splitLayoutClient);

        tabWidgetClient->addTab(clientListTab, QString());
        clientStatsTab = new QWidget();
        clientStatsTab->setObjectName("clientStatsTab");
        tab2LayoutClient = new QVBoxLayout(clientStatsTab);
        tab2LayoutClient->setSpacing(20);
        tab2LayoutClient->setContentsMargins(20, 20, 20, 20);
        tab2LayoutClient->setObjectName("tab2LayoutClient");
        statsLabelClient = new QLabel(clientStatsTab);
        statsLabelClient->setObjectName("statsLabelClient");
        statsLabelClient->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tab2LayoutClient->addWidget(statsLabelClient);

        statsCardsLayoutClient = new QHBoxLayout();
        statsCardsLayoutClient->setObjectName("statsCardsLayoutClient");
        cardTotalClients = new QFrame(clientStatsTab);
        cardTotalClients->setObjectName("cardTotalClients");
        cardTotalClients->setMinimumSize(QSize(0, 120));
        vboxLayout = new QVBoxLayout(cardTotalClients);
        vboxLayout->setObjectName("vboxLayout");
        labelTotalClients = new QLabel(cardTotalClients);
        labelTotalClients->setObjectName("labelTotalClients");
        labelTotalClients->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout->addWidget(labelTotalClients);

        valueTotalClients = new QLabel(cardTotalClients);
        valueTotalClients->setObjectName("valueTotalClients");
        valueTotalClients->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout->addWidget(valueTotalClients);


        statsCardsLayoutClient->addWidget(cardTotalClients);

        cardParticuliers = new QFrame(clientStatsTab);
        cardParticuliers->setObjectName("cardParticuliers");
        cardParticuliers->setMinimumSize(QSize(0, 120));
        vboxLayout1 = new QVBoxLayout(cardParticuliers);
        vboxLayout1->setObjectName("vboxLayout1");
        labelParticuliers = new QLabel(cardParticuliers);
        labelParticuliers->setObjectName("labelParticuliers");
        labelParticuliers->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout1->addWidget(labelParticuliers);

        valueParticuliers = new QLabel(cardParticuliers);
        valueParticuliers->setObjectName("valueParticuliers");
        valueParticuliers->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout1->addWidget(valueParticuliers);


        statsCardsLayoutClient->addWidget(cardParticuliers);

        cardEntreprises = new QFrame(clientStatsTab);
        cardEntreprises->setObjectName("cardEntreprises");
        cardEntreprises->setMinimumSize(QSize(0, 120));
        vboxLayout2 = new QVBoxLayout(cardEntreprises);
        vboxLayout2->setObjectName("vboxLayout2");
        labelEntreprises = new QLabel(cardEntreprises);
        labelEntreprises->setObjectName("labelEntreprises");
        labelEntreprises->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout2->addWidget(labelEntreprises);

        valueEntreprises = new QLabel(cardEntreprises);
        valueEntreprises->setObjectName("valueEntreprises");
        valueEntreprises->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout2->addWidget(valueEntreprises);


        statsCardsLayoutClient->addWidget(cardEntreprises);


        tab2LayoutClient->addLayout(statsCardsLayoutClient);

        spacerItem3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        tab2LayoutClient->addItem(spacerItem3);

        tabWidgetClient->addTab(clientStatsTab, QString());

        verticalLayout_3->addWidget(tabWidgetClient);

        stackedWidget->addWidget(pageClient);
        pageStock = new QWidget();
        pageStock->setObjectName("pageStock");
        verticalLayout_4 = new QVBoxLayout(pageStock);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        headerFrameStock = new QFrame(pageStock);
        headerFrameStock->setObjectName("headerFrameStock");
        headerFrameStock->setMinimumSize(QSize(0, 80));
        headerFrameStock->setStyleSheet(QString::fromUtf8("background: #ffffff; border: none; border-bottom: 3px solid #5d732c;"));
        horizontalLayout_4 = new QHBoxLayout(headerFrameStock);
        horizontalLayout_4->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        headerTitleStock = new QLabel(headerFrameStock);
        headerTitleStock->setObjectName("headerTitleStock");
        headerTitleStock->setStyleSheet(QString::fromUtf8("color: #2d4a1f; font-size: 28px; font-weight: bold;"));

        horizontalLayout_4->addWidget(headerTitleStock);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        userIconHeaderStock = new QLabel(headerFrameStock);
        userIconHeaderStock->setObjectName("userIconHeaderStock");
        userIconHeaderStock->setStyleSheet(QString::fromUtf8("font-size: 28px; color: #5d732c;"));

        horizontalLayout_4->addWidget(userIconHeaderStock);


        verticalLayout_4->addWidget(headerFrameStock);

        placeholderStock = new QLabel(pageStock);
        placeholderStock->setObjectName("placeholderStock");
        placeholderStock->setStyleSheet(QString::fromUtf8("font-size: 18px; color: #888; padding: 50px;"));
        placeholderStock->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(placeholderStock);

        stackedWidget->addWidget(pageStock);
        pageMachine = new QWidget();
        pageMachine->setObjectName("pageMachine");
        verticalLayout_5 = new QVBoxLayout(pageMachine);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        headerFrameMachine = new QFrame(pageMachine);
        headerFrameMachine->setObjectName("headerFrameMachine");
        headerFrameMachine->setMinimumSize(QSize(0, 80));
        headerFrameMachine->setStyleSheet(QString::fromUtf8("background: #ffffff; border: none; border-bottom: 3px solid #5d732c;"));
        horizontalLayout_5 = new QHBoxLayout(headerFrameMachine);
        horizontalLayout_5->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        headerTitleMachine = new QLabel(headerFrameMachine);
        headerTitleMachine->setObjectName("headerTitleMachine");
        headerTitleMachine->setStyleSheet(QString::fromUtf8("color: #2d4a1f; font-size: 28px; font-weight: bold;"));

        horizontalLayout_5->addWidget(headerTitleMachine);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        userIconHeaderMachine = new QLabel(headerFrameMachine);
        userIconHeaderMachine->setObjectName("userIconHeaderMachine");
        userIconHeaderMachine->setStyleSheet(QString::fromUtf8("font-size: 28px; color: #5d732c;"));

        horizontalLayout_5->addWidget(userIconHeaderMachine);


        verticalLayout_5->addWidget(headerFrameMachine);

        placeholderMachine = new QLabel(pageMachine);
        placeholderMachine->setObjectName("placeholderMachine");
        placeholderMachine->setStyleSheet(QString::fromUtf8("font-size: 18px; color: #888; padding: 50px;"));
        placeholderMachine->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(placeholderMachine);

        stackedWidget->addWidget(pageMachine);
        pageProduction = new QWidget();
        pageProduction->setObjectName("pageProduction");
        contentLayout = new QVBoxLayout(pageProduction);
        contentLayout->setSpacing(0);
        contentLayout->setContentsMargins(0, 0, 0, 0);
        contentLayout->setObjectName("contentLayout");
        headerFrame = new QFrame(pageProduction);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setMinimumSize(QSize(0, 80));
        headerLayout = new QHBoxLayout(headerFrame);
        headerLayout->setSpacing(20);
        headerLayout->setContentsMargins(20, 20, 20, 20);
        headerLayout->setObjectName("headerLayout");
        headerTitle = new QLabel(headerFrame);
        headerTitle->setObjectName("headerTitle");

        headerLayout->addWidget(headerTitle);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(spacerItem4);

        userIconHeader = new QLabel(headerFrame);
        userIconHeader->setObjectName("userIconHeader");

        headerLayout->addWidget(userIconHeader);


        contentLayout->addWidget(headerFrame);

        tabWidget = new QTabWidget(pageProduction);
        tabWidget->setObjectName("tabWidget");
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        tab1Layout1 = new QVBoxLayout(tab1);
        tab1Layout1->setSpacing(15);
        tab1Layout1->setContentsMargins(20, 20, 20, 20);
        tab1Layout1->setObjectName("tab1Layout1");
        searchLayout1 = new QHBoxLayout();
        searchLayout1->setSpacing(10);
        searchLayout1->setObjectName("searchLayout1");
        btnRefresh = new QPushButton(tab1);
        btnRefresh->setObjectName("btnRefresh");

        searchLayout1->addWidget(btnRefresh);

        btnClear = new QPushButton(tab1);
        btnClear->setObjectName("btnClear");

        searchLayout1->addWidget(btnClear);

        searchBox = new QLineEdit(tab1);
        searchBox->setObjectName("searchBox");

        searchLayout1->addWidget(searchBox);

        btnSearch = new QPushButton(tab1);
        btnSearch->setObjectName("btnSearch");

        searchLayout1->addWidget(btnSearch);

        btnExportPDF = new QPushButton(tab1);
        btnExportPDF->setObjectName("btnExportPDF");

        searchLayout1->addWidget(btnExportPDF);


        tab1Layout1->addLayout(searchLayout1);

        splitLayout = new QHBoxLayout();
        splitLayout->setSpacing(15);
        splitLayout->setObjectName("splitLayout");
        productionTable = new QTableWidget(tab1);
        if (productionTable->columnCount() < 5)
            productionTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        productionTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        productionTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        productionTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        productionTable->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        productionTable->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        productionTable->setObjectName("productionTable");

        splitLayout->addWidget(productionTable);

        formPanel = new QFrame(tab1);
        formPanel->setObjectName("formPanel");
        formPanel->setMinimumSize(QSize(350, 0));
        formPanel->setMaximumSize(QSize(400, 16777215));
        formLayout = new QVBoxLayout(formPanel);
        formLayout->setSpacing(15);
        formLayout->setContentsMargins(20, 20, 20, 20);
        formLayout->setObjectName("formLayout");
        labelFormTitle = new QLabel(formPanel);
        labelFormTitle->setObjectName("labelFormTitle");
        labelFormTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formLayout->addWidget(labelFormTitle);

        labelDate = new QLabel(formPanel);
        labelDate->setObjectName("labelDate");

        formLayout->addWidget(labelDate);

        inputDate = new QDateEdit(formPanel);
        inputDate->setObjectName("inputDate");
        inputDate->setCalendarPopup(true);

        formLayout->addWidget(inputDate);

        labelQuantiteOlive = new QLabel(formPanel);
        labelQuantiteOlive->setObjectName("labelQuantiteOlive");

        formLayout->addWidget(labelQuantiteOlive);

        inputQuantiteOlive = new QDoubleSpinBox(formPanel);
        inputQuantiteOlive->setObjectName("inputQuantiteOlive");
        inputQuantiteOlive->setDecimals(2);
        inputQuantiteOlive->setMaximum(100000.000000000000000);

        formLayout->addWidget(inputQuantiteOlive);

        labelQuantiteHuile = new QLabel(formPanel);
        labelQuantiteHuile->setObjectName("labelQuantiteHuile");

        formLayout->addWidget(labelQuantiteHuile);

        inputQuantiteHuile = new QDoubleSpinBox(formPanel);
        inputQuantiteHuile->setObjectName("inputQuantiteHuile");
        inputQuantiteHuile->setDecimals(2);
        inputQuantiteHuile->setMaximum(50000.000000000000000);

        formLayout->addWidget(inputQuantiteHuile);

        labelRendement = new QLabel(formPanel);
        labelRendement->setObjectName("labelRendement");

        formLayout->addWidget(labelRendement);

        inputRendement = new QLineEdit(formPanel);
        inputRendement->setObjectName("inputRendement");
        inputRendement->setEnabled(false);

        formLayout->addWidget(inputRendement);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->addItem(spacerItem5);

        formButtons = new QHBoxLayout();
        formButtons->setObjectName("formButtons");
        btnAdd = new QPushButton(formPanel);
        btnAdd->setObjectName("btnAdd");

        formButtons->addWidget(btnAdd);

        btnUpdate = new QPushButton(formPanel);
        btnUpdate->setObjectName("btnUpdate");

        formButtons->addWidget(btnUpdate);

        btnDelete = new QPushButton(formPanel);
        btnDelete->setObjectName("btnDelete");

        formButtons->addWidget(btnDelete);


        formLayout->addLayout(formButtons);


        splitLayout->addWidget(formPanel);


        tab1Layout1->addLayout(splitLayout);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        tab2Layout = new QVBoxLayout(tab2);
        tab2Layout->setSpacing(20);
        tab2Layout->setContentsMargins(20, 20, 20, 20);
        tab2Layout->setObjectName("tab2Layout");
        statsTitle = new QLabel(tab2);
        statsTitle->setObjectName("statsTitle");
        statsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tab2Layout->addWidget(statsTitle);

        statsCards = new QHBoxLayout();
        statsCards->setObjectName("statsCards");
        cardTotal = new QFrame(tab2);
        cardTotal->setObjectName("cardTotal");
        cardTotal->setMinimumSize(QSize(0, 120));
        vboxLayout3 = new QVBoxLayout(cardTotal);
        vboxLayout3->setObjectName("vboxLayout3");
        labelTotal = new QLabel(cardTotal);
        labelTotal->setObjectName("labelTotal");
        labelTotal->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout3->addWidget(labelTotal);

        valueTotal = new QLabel(cardTotal);
        valueTotal->setObjectName("valueTotal");
        valueTotal->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout3->addWidget(valueTotal);


        statsCards->addWidget(cardTotal);

        cardOlives = new QFrame(tab2);
        cardOlives->setObjectName("cardOlives");
        cardOlives->setMinimumSize(QSize(0, 120));
        vboxLayout4 = new QVBoxLayout(cardOlives);
        vboxLayout4->setObjectName("vboxLayout4");
        labelOlives = new QLabel(cardOlives);
        labelOlives->setObjectName("labelOlives");
        labelOlives->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout4->addWidget(labelOlives);

        valueOlives = new QLabel(cardOlives);
        valueOlives->setObjectName("valueOlives");
        valueOlives->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout4->addWidget(valueOlives);


        statsCards->addWidget(cardOlives);

        cardHuile = new QFrame(tab2);
        cardHuile->setObjectName("cardHuile");
        cardHuile->setMinimumSize(QSize(0, 120));
        vboxLayout5 = new QVBoxLayout(cardHuile);
        vboxLayout5->setObjectName("vboxLayout5");
        labelHuile = new QLabel(cardHuile);
        labelHuile->setObjectName("labelHuile");
        labelHuile->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout5->addWidget(labelHuile);

        valueHuile = new QLabel(cardHuile);
        valueHuile->setObjectName("valueHuile");
        valueHuile->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout5->addWidget(valueHuile);


        statsCards->addWidget(cardHuile);

        cardRendement = new QFrame(tab2);
        cardRendement->setObjectName("cardRendement");
        cardRendement->setMinimumSize(QSize(0, 120));
        vboxLayout6 = new QVBoxLayout(cardRendement);
        vboxLayout6->setObjectName("vboxLayout6");
        labelRendement1 = new QLabel(cardRendement);
        labelRendement1->setObjectName("labelRendement1");
        labelRendement1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout6->addWidget(labelRendement1);

        valueRendement = new QLabel(cardRendement);
        valueRendement->setObjectName("valueRendement");
        valueRendement->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout6->addWidget(valueRendement);


        statsCards->addWidget(cardRendement);


        tab2Layout->addLayout(statsCards);

        spacerItem6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        tab2Layout->addItem(spacerItem6);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName("tab3");
        tab3Layout = new QVBoxLayout(tab3);
        tab3Layout->setSpacing(20);
        tab3Layout->setContentsMargins(20, 20, 20, 20);
        tab3Layout->setObjectName("tab3Layout");
        predTitle = new QLabel(tab3);
        predTitle->setObjectName("predTitle");
        predTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tab3Layout->addWidget(predTitle);

        predFrame = new QFrame(tab3);
        predFrame->setObjectName("predFrame");
        predLayout = new QVBoxLayout(predFrame);
        predLayout->setSpacing(15);
        predLayout->setContentsMargins(20, 20, 20, 20);
        predLayout->setObjectName("predLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        labelPredInput = new QLabel(predFrame);
        labelPredInput->setObjectName("labelPredInput");

        hboxLayout->addWidget(labelPredInput);

        inputPredOlives = new QDoubleSpinBox(predFrame);
        inputPredOlives->setObjectName("inputPredOlives");
        inputPredOlives->setMaximum(100000.000000000000000);
        inputPredOlives->setValue(1000.000000000000000);

        hboxLayout->addWidget(inputPredOlives);

        btnPredict = new QPushButton(predFrame);
        btnPredict->setObjectName("btnPredict");

        hboxLayout->addWidget(btnPredict);


        predLayout->addLayout(hboxLayout);

        predResult = new QFrame(predFrame);
        predResult->setObjectName("predResult");
        predResult->setMinimumSize(QSize(0, 150));
        vboxLayout7 = new QVBoxLayout(predResult);
        vboxLayout7->setObjectName("vboxLayout7");
        valuePredRendement = new QLabel(predResult);
        valuePredRendement->setObjectName("valuePredRendement");
        valuePredRendement->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout7->addWidget(valuePredRendement);

        valuePredHuile = new QLabel(predResult);
        valuePredHuile->setObjectName("valuePredHuile");
        valuePredHuile->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout7->addWidget(valuePredHuile);


        predLayout->addWidget(predResult);


        tab3Layout->addWidget(predFrame);

        spacerItem7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        tab3Layout->addItem(spacerItem7);

        tabWidget->addTab(tab3, QString());
        tab4 = new QWidget();
        tab4->setObjectName("tab4");
        tab4Layout = new QVBoxLayout(tab4);
        tab4Layout->setSpacing(20);
        tab4Layout->setContentsMargins(20, 20, 20, 20);
        tab4Layout->setObjectName("tab4Layout");
        anomalyTitle = new QLabel(tab4);
        anomalyTitle->setObjectName("anomalyTitle");
        anomalyTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tab4Layout->addWidget(anomalyTitle);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        btnAnalyze = new QPushButton(tab4);
        btnAnalyze->setObjectName("btnAnalyze");

        hboxLayout1->addWidget(btnAnalyze);

        spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem8);

        labelThreshold = new QLabel(tab4);
        labelThreshold->setObjectName("labelThreshold");

        hboxLayout1->addWidget(labelThreshold);

        inputThreshold = new QSpinBox(tab4);
        inputThreshold->setObjectName("inputThreshold");
        inputThreshold->setMinimum(5);
        inputThreshold->setMaximum(50);
        inputThreshold->setValue(15);

        hboxLayout1->addWidget(inputThreshold);


        tab4Layout->addLayout(hboxLayout1);

        anomalyTable = new QTableWidget(tab4);
        if (anomalyTable->columnCount() < 5)
            anomalyTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        anomalyTable->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        anomalyTable->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        anomalyTable->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        anomalyTable->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        anomalyTable->setHorizontalHeaderItem(4, __qtablewidgetitem15);
        anomalyTable->setObjectName("anomalyTable");

        tab4Layout->addWidget(anomalyTable);

        tabWidget->addTab(tab4, QString());

        contentLayout->addWidget(tabWidget);

        stackedWidget->addWidget(pageProduction);
        pagePartenaire = new QWidget();
        pagePartenaire->setObjectName("pagePartenaire");
        verticalLayout_6 = new QVBoxLayout(pagePartenaire);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        headerFramePartenaire = new QFrame(pagePartenaire);
        headerFramePartenaire->setObjectName("headerFramePartenaire");
        headerFramePartenaire->setMinimumSize(QSize(0, 80));
        headerFramePartenaire->setStyleSheet(QString::fromUtf8("background: #ffffff; border: none; border-bottom: 3px solid #5d732c;"));
        horizontalLayout_6 = new QHBoxLayout(headerFramePartenaire);
        horizontalLayout_6->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        headerTitlePartenaire = new QLabel(headerFramePartenaire);
        headerTitlePartenaire->setObjectName("headerTitlePartenaire");
        headerTitlePartenaire->setStyleSheet(QString::fromUtf8("color: #2d4a1f; font-size: 28px; font-weight: bold;"));

        horizontalLayout_6->addWidget(headerTitlePartenaire);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        userIconHeaderPartenaire = new QLabel(headerFramePartenaire);
        userIconHeaderPartenaire->setObjectName("userIconHeaderPartenaire");
        userIconHeaderPartenaire->setStyleSheet(QString::fromUtf8("font-size: 28px; color: #5d732c;"));

        horizontalLayout_6->addWidget(userIconHeaderPartenaire);


        verticalLayout_6->addWidget(headerFramePartenaire);

        tabWidgetPartenaire = new QTabWidget(pagePartenaire);
        tabWidgetPartenaire->setObjectName("tabWidgetPartenaire");
        partnersListTab = new QWidget();
        partnersListTab->setObjectName("partnersListTab");
        vboxLayout8 = new QVBoxLayout(partnersListTab);
        vboxLayout8->setSpacing(15);
        vboxLayout8->setContentsMargins(20, 20, 20, 20);
        vboxLayout8->setObjectName("vboxLayout8");
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(10);
        hboxLayout2->setObjectName("hboxLayout2");
        searchLineEdit = new QLineEdit(partnersListTab);
        searchLineEdit->setObjectName("searchLineEdit");

        hboxLayout2->addWidget(searchLineEdit);

        searchButton = new QPushButton(partnersListTab);
        searchButton->setObjectName("searchButton");

        hboxLayout2->addWidget(searchButton);

        exportButton = new QPushButton(partnersListTab);
        exportButton->setObjectName("exportButton");

        hboxLayout2->addWidget(exportButton);

        filterButton = new QPushButton(partnersListTab);
        filterButton->setObjectName("filterButton");

        hboxLayout2->addWidget(filterButton);


        vboxLayout8->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(15);
        hboxLayout3->setObjectName("hboxLayout3");
        partnersTable = new QTableWidget(partnersListTab);
        if (partnersTable->columnCount() < 5)
            partnersTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        partnersTable->setObjectName("partnersTable");

        hboxLayout3->addWidget(partnersTable);

        formFramePartenaire = new QFrame(partnersListTab);
        formFramePartenaire->setObjectName("formFramePartenaire");
        formFramePartenaire->setMinimumSize(QSize(350, 0));
        formFramePartenaire->setMaximumSize(QSize(400, 16777215));
        vboxLayout9 = new QVBoxLayout(formFramePartenaire);
        vboxLayout9->setSpacing(12);
        vboxLayout9->setContentsMargins(20, 20, 20, 20);
        vboxLayout9->setObjectName("vboxLayout9");
        formTitleLabel = new QLabel(formFramePartenaire);
        formTitleLabel->setObjectName("formTitleLabel");
        formTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout9->addWidget(formTitleLabel);

        nameLabel = new QLabel(formFramePartenaire);
        nameLabel->setObjectName("nameLabel");

        vboxLayout9->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(formFramePartenaire);
        nameLineEdit->setObjectName("nameLineEdit");

        vboxLayout9->addWidget(nameLineEdit);

        emailLabel = new QLabel(formFramePartenaire);
        emailLabel->setObjectName("emailLabel");

        vboxLayout9->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(formFramePartenaire);
        emailLineEdit->setObjectName("emailLineEdit");

        vboxLayout9->addWidget(emailLineEdit);

        phoneLabel = new QLabel(formFramePartenaire);
        phoneLabel->setObjectName("phoneLabel");

        vboxLayout9->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(formFramePartenaire);
        phoneLineEdit->setObjectName("phoneLineEdit");

        vboxLayout9->addWidget(phoneLineEdit);

        typeLabel = new QLabel(formFramePartenaire);
        typeLabel->setObjectName("typeLabel");

        vboxLayout9->addWidget(typeLabel);

        typeComboBox = new QComboBox(formFramePartenaire);
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->setObjectName("typeComboBox");

        vboxLayout9->addWidget(typeComboBox);

        statusLabel = new QLabel(formFramePartenaire);
        statusLabel->setObjectName("statusLabel");

        vboxLayout9->addWidget(statusLabel);

        statusComboBox = new QComboBox(formFramePartenaire);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        vboxLayout9->addWidget(statusComboBox);

        spacerItem9 = new QSpacerItem(0, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout9->addItem(spacerItem9);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(10);
        hboxLayout4->setObjectName("hboxLayout4");
        addButton = new QPushButton(formFramePartenaire);
        addButton->setObjectName("addButton");

        hboxLayout4->addWidget(addButton);

        updateButton = new QPushButton(formFramePartenaire);
        updateButton->setObjectName("updateButton");

        hboxLayout4->addWidget(updateButton);

        deleteButton = new QPushButton(formFramePartenaire);
        deleteButton->setObjectName("deleteButton");

        hboxLayout4->addWidget(deleteButton);


        vboxLayout9->addLayout(hboxLayout4);


        hboxLayout3->addWidget(formFramePartenaire);


        vboxLayout8->addLayout(hboxLayout3);

        tabWidgetPartenaire->addTab(partnersListTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName("statsTab");
        vboxLayout10 = new QVBoxLayout(statsTab);
        vboxLayout10->setSpacing(20);
        vboxLayout10->setContentsMargins(20, 20, 20, 20);
        vboxLayout10->setObjectName("vboxLayout10");
        statsHeaderLabel = new QLabel(statsTab);
        statsHeaderLabel->setObjectName("statsHeaderLabel");
        statsHeaderLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout10->addWidget(statsHeaderLabel);

        statsCardsLayout = new QHBoxLayout();
        statsCardsLayout->setObjectName("statsCardsLayout");
        cardTotalPartenaires = new QFrame(statsTab);
        cardTotalPartenaires->setObjectName("cardTotalPartenaires");
        cardTotalPartenaires->setMinimumSize(QSize(0, 120));
        vboxLayout11 = new QVBoxLayout(cardTotalPartenaires);
        vboxLayout11->setObjectName("vboxLayout11");
        labelTotalPartenaires = new QLabel(cardTotalPartenaires);
        labelTotalPartenaires->setObjectName("labelTotalPartenaires");
        labelTotalPartenaires->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout11->addWidget(labelTotalPartenaires);

        valueTotalPartenaires = new QLabel(cardTotalPartenaires);
        valueTotalPartenaires->setObjectName("valueTotalPartenaires");
        valueTotalPartenaires->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout11->addWidget(valueTotalPartenaires);


        statsCardsLayout->addWidget(cardTotalPartenaires);

        cardActifs = new QFrame(statsTab);
        cardActifs->setObjectName("cardActifs");
        cardActifs->setMinimumSize(QSize(0, 120));
        vboxLayout12 = new QVBoxLayout(cardActifs);
        vboxLayout12->setObjectName("vboxLayout12");
        labelActifs = new QLabel(cardActifs);
        labelActifs->setObjectName("labelActifs");
        labelActifs->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout12->addWidget(labelActifs);

        valueActifs = new QLabel(cardActifs);
        valueActifs->setObjectName("valueActifs");
        valueActifs->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout12->addWidget(valueActifs);


        statsCardsLayout->addWidget(cardActifs);

        cardInactifs = new QFrame(statsTab);
        cardInactifs->setObjectName("cardInactifs");
        cardInactifs->setMinimumSize(QSize(0, 120));
        vboxLayout13 = new QVBoxLayout(cardInactifs);
        vboxLayout13->setObjectName("vboxLayout13");
        labelInactifs = new QLabel(cardInactifs);
        labelInactifs->setObjectName("labelInactifs");
        labelInactifs->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout13->addWidget(labelInactifs);

        valueInactifs = new QLabel(cardInactifs);
        valueInactifs->setObjectName("valueInactifs");
        valueInactifs->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout13->addWidget(valueInactifs);


        statsCardsLayout->addWidget(cardInactifs);


        vboxLayout10->addLayout(statsCardsLayout);

        spacerItem10 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout10->addItem(spacerItem10);

        tabWidgetPartenaire->addTab(statsTab, QString());
        mailingTab = new QWidget();
        mailingTab->setObjectName("mailingTab");
        vboxLayout14 = new QVBoxLayout(mailingTab);
        vboxLayout14->setSpacing(15);
        vboxLayout14->setContentsMargins(20, 20, 20, 20);
        vboxLayout14->setObjectName("vboxLayout14");
        mailingHeaderLabel = new QLabel(mailingTab);
        mailingHeaderLabel->setObjectName("mailingHeaderLabel");
        mailingHeaderLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout14->addWidget(mailingHeaderLabel);

        mailingFrame = new QFrame(mailingTab);
        mailingFrame->setObjectName("mailingFrame");
        vboxLayout15 = new QVBoxLayout(mailingFrame);
        vboxLayout15->setSpacing(15);
        vboxLayout15->setContentsMargins(20, 20, 20, 20);
        vboxLayout15->setObjectName("vboxLayout15");
        subjectLabel = new QLabel(mailingFrame);
        subjectLabel->setObjectName("subjectLabel");

        vboxLayout15->addWidget(subjectLabel);

        subjectLineEdit = new QLineEdit(mailingFrame);
        subjectLineEdit->setObjectName("subjectLineEdit");

        vboxLayout15->addWidget(subjectLineEdit);

        messageLabel = new QLabel(mailingFrame);
        messageLabel->setObjectName("messageLabel");

        vboxLayout15->addWidget(messageLabel);

        messageTextEdit = new QTextEdit(mailingFrame);
        messageTextEdit->setObjectName("messageTextEdit");

        vboxLayout15->addWidget(messageTextEdit);

        sendMailButton = new QPushButton(mailingFrame);
        sendMailButton->setObjectName("sendMailButton");

        vboxLayout15->addWidget(sendMailButton);


        vboxLayout14->addWidget(mailingFrame);

        spacerItem11 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout14->addItem(spacerItem11);

        tabWidgetPartenaire->addTab(mailingTab, QString());

        verticalLayout_6->addWidget(tabWidgetPartenaire);

        stackedWidget->addWidget(pagePartenaire);

        mainLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);
        tabWidgetClient->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        tabWidgetPartenaire->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZitTech - Gestion de Production", nullptr));
        label->setText(QString());
        btnEmploye->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnEmploye->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 Employ\303\251s", nullptr));
        btnClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnClient->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Clients", nullptr));
        btnStock->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnStock->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Stock", nullptr));
        btnMachine->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnMachine->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 Machines", nullptr));
        btnProduction->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnProduction->setText(QCoreApplication::translate("MainWindow", "\360\237\217\255 Production", nullptr));
        btnPartenaire->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;", nullptr));
        btnPartenaire->setText(QCoreApplication::translate("MainWindow", "\360\237\244\235 Partenaires", nullptr));
        btnSetting->setStyleSheet(QCoreApplication::translate("MainWindow", "background: transparent; color: #ffd700; border: none; padding: 8px; text-align: left;", nullptr));
        btnSetting->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 Param\303\250tres", nullptr));
        btnLogout->setStyleSheet(QCoreApplication::translate("MainWindow", "background: transparent; color: #ffd700; border: none; padding: 8px; text-align: left;", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 D\303\251connexion", nullptr));
        headerTitleEmploye->setText(QCoreApplication::translate("MainWindow", "Gestion des Employ\303\251s", nullptr));
        userIconHeaderEmploye->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        placeholderEmploye->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 Module Employ\303\251s - \303\200 impl\303\251menter", nullptr));
        headerTitleClient->setText(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        userIconHeaderClient->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        btnRefreshClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnRefreshClient->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204", nullptr));
        btnClearClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnClearClient->setText(QCoreApplication::translate("MainWindow", "\342\234\226", nullptr));
        searchBoxClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 10px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        searchBoxClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher un client...", nullptr));
        btnSearchClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnSearchClient->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = clientTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Type Client", nullptr));
        formPanelClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 8px;", nullptr));
        labelFormTitleClient->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; color: #2d4a1f; font-weight: bold;", nullptr));
        labelFormTitleClient->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 D\303\251tails Client", nullptr));
        labelIdClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelIdClient->setText(QCoreApplication::translate("MainWindow", "ID Client", nullptr));
        inputIdClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px; background: #f0f0f0;", nullptr));
        inputIdClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251r\303\251 automatiquement", nullptr));
        labelNomClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelNomClient->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        inputNomClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelPrenomClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelPrenomClient->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        inputPrenomClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelEmailClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelEmailClient->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        inputEmailClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputEmailClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "exemple@email.com", nullptr));
        labelTelephoneClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelTelephoneClient->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        inputTelephoneClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputTelephoneClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "+216 XX XXX XXX", nullptr));
        labelTypeClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelTypeClient->setText(QCoreApplication::translate("MainWindow", "Type Client", nullptr));
        inputTypeClient->setItemText(0, QCoreApplication::translate("MainWindow", "Particulier", nullptr));
        inputTypeClient->setItemText(1, QCoreApplication::translate("MainWindow", "Entreprise", nullptr));
        inputTypeClient->setItemText(2, QCoreApplication::translate("MainWindow", "Revendeur", nullptr));
        inputTypeClient->setItemText(3, QCoreApplication::translate("MainWindow", "Grossiste", nullptr));

        inputTypeClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelFeedbackClient->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelFeedbackClient->setText(QCoreApplication::translate("MainWindow", "Feedback / Avis", nullptr));
        inputFeedbackClient->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputFeedbackClient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Commentaires ou avis du client...", nullptr));
        btnAddClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnAddClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdateClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnUpdateClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
#if QT_CONFIG(tooltip)
        btnDeleteClient->setToolTip(QCoreApplication::translate("MainWindow", "Supprimer le client s\303\251lectionn\303\251", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDeleteClient->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #dc3545; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnDeleteClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidgetClient->setTabText(tabWidgetClient->indexOf(clientListTab), QCoreApplication::translate("MainWindow", "Liste des Clients", nullptr));
        statsLabelClient->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        statsLabelClient->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques Clients", nullptr));
        cardTotalClients->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelTotalClients->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelTotalClients->setText(QCoreApplication::translate("MainWindow", "Total Clients", nullptr));
        valueTotalClients->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #2d4a1f; font-weight: bold;", nullptr));
        valueTotalClients->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cardParticuliers->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelParticuliers->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelParticuliers->setText(QCoreApplication::translate("MainWindow", "Particuliers", nullptr));
        valueParticuliers->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #ffd700; font-weight: bold;", nullptr));
        valueParticuliers->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cardEntreprises->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelEntreprises->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelEntreprises->setText(QCoreApplication::translate("MainWindow", "Entreprises", nullptr));
        valueEntreprises->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #28a745; font-weight: bold;", nullptr));
        valueEntreprises->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        tabWidgetClient->setTabText(tabWidgetClient->indexOf(clientStatsTab), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        headerTitleStock->setText(QCoreApplication::translate("MainWindow", "Gestion des Stocks", nullptr));
        userIconHeaderStock->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        placeholderStock->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Module Stock - \303\200 impl\303\251menter", nullptr));
        headerTitleMachine->setText(QCoreApplication::translate("MainWindow", "Gestion des Machines", nullptr));
        userIconHeaderMachine->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        placeholderMachine->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 Module Machines - \303\200 impl\303\251menter", nullptr));
        headerTitle->setText(QCoreApplication::translate("MainWindow", "Gestion de Production", nullptr));
        userIconHeader->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 28px; color: #5d732c;", nullptr));
        userIconHeader->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        btnRefresh->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204", nullptr));
        btnClear->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\342\234\226", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par date ou quantit\303\251...", nullptr));
        btnSearch->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        btnExportPDF->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        btnExportPDF->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = productionTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = productionTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = productionTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Qt\303\251 Olives (kg)", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = productionTable->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Qt\303\251 Huile (L)", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = productionTable->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Rendement (%)", nullptr));
        labelFormTitle->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; color: #2d4a1f; font-weight: bold;", nullptr));
        labelFormTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 D\303\251tails Production", nullptr));
        labelDate->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelDate->setText(QCoreApplication::translate("MainWindow", "Date de Production", nullptr));
        inputDate->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelQuantiteOlive->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelQuantiteOlive->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 Olives (kg)", nullptr));
        inputQuantiteOlive->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputQuantiteOlive->setSuffix(QCoreApplication::translate("MainWindow", " kg", nullptr));
        labelQuantiteHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelQuantiteHuile->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 Huile (L)", nullptr));
        inputQuantiteHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputQuantiteHuile->setSuffix(QCoreApplication::translate("MainWindow", " L", nullptr));
        labelRendement->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelRendement->setText(QCoreApplication::translate("MainWindow", "Rendement (%)", nullptr));
        inputRendement->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px; background: #f0f0f0; font-weight: bold; color: #5d732c;", nullptr));
        inputRendement->setPlaceholderText(QCoreApplication::translate("MainWindow", "Calcul\303\251 auto", nullptr));
        btnAdd->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnUpdate->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnUpdate->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnDelete->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #dc3545; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Liste des Productions", nullptr));
        statsTitle->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        statsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques de Production", nullptr));
        cardTotal->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelTotal->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelTotal->setText(QCoreApplication::translate("MainWindow", "Total Productions", nullptr));
        valueTotal->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #2d4a1f; font-weight: bold;", nullptr));
        valueTotal->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cardOlives->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelOlives->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelOlives->setText(QCoreApplication::translate("MainWindow", "Total Olives (kg)", nullptr));
        valueOlives->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #2d4a1f; font-weight: bold;", nullptr));
        valueOlives->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        cardHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelHuile->setText(QCoreApplication::translate("MainWindow", "Total Huile (L)", nullptr));
        valueHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #2d4a1f; font-weight: bold;", nullptr));
        valueHuile->setText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        cardRendement->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelRendement1->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelRendement1->setText(QCoreApplication::translate("MainWindow", "Rendement Moyen", nullptr));
        valueRendement->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #ffd700; font-weight: bold;", nullptr));
        valueRendement->setText(QCoreApplication::translate("MainWindow", "0.00%", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        predTitle->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        predTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\224\256 Pr\303\251diction du Rendement", nullptr));
        predFrame->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelPredInput->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelPredInput->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 Olives (kg):", nullptr));
        inputPredOlives->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputPredOlives->setSuffix(QCoreApplication::translate("MainWindow", " kg", nullptr));
        btnPredict->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px 30px; border-radius: 8px; font-weight: bold;", nullptr));
        btnPredict->setText(QCoreApplication::translate("MainWindow", "\360\237\224\256 Pr\303\251dire", nullptr));
        predResult->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #f8f8f8; border: 2px dashed #5d732c; border-radius: 8px;", nullptr));
        valuePredRendement->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px; color: #ffd700; font-weight: bold;", nullptr));
        valuePredRendement->setText(QCoreApplication::translate("MainWindow", "---%", nullptr));
        valuePredHuile->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 18px; color: #5d732c;", nullptr));
        valuePredHuile->setText(QCoreApplication::translate("MainWindow", "Huile estim\303\251e: --- L", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QCoreApplication::translate("MainWindow", "Pr\303\251diction Rendement", nullptr));
        anomalyTitle->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        anomalyTitle->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 D\303\251tection des Anomalies", nullptr));
        btnAnalyze->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px 30px; border-radius: 8px; font-weight: bold;", nullptr));
        btnAnalyze->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Analyser", nullptr));
        labelThreshold->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        labelThreshold->setText(QCoreApplication::translate("MainWindow", "Seuil tol\303\251rance (%):", nullptr));
        inputThreshold->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        inputThreshold->setSuffix(QCoreApplication::translate("MainWindow", "%", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = anomalyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = anomalyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = anomalyTable->horizontalHeaderItem(2);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Rendement (%)", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = anomalyTable->horizontalHeaderItem(3);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\303\211cart (%)", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = anomalyTable->horizontalHeaderItem(4);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab4), QCoreApplication::translate("MainWindow", "D\303\251tection Anomalies", nullptr));
        headerTitlePartenaire->setText(QCoreApplication::translate("MainWindow", "Gestion des Partenaires", nullptr));
        userIconHeaderPartenaire->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        searchLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 10px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher un partenaire (nom, email, t\303\251l\303\251phone)...", nullptr));
        searchButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        exportButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 PDF", nullptr));
        filterButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;", nullptr));
        filterButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\275 Filtrer", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = partnersTable->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = partnersTable->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = partnersTable->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = partnersTable->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = partnersTable->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        formFramePartenaire->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 8px;", nullptr));
        formTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; color: #2d4a1f; font-weight: bold;", nullptr));
        formTitleLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\244\235 D\303\251tails Partenaire", nullptr));
        nameLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "Nom du Partenaire", nullptr));
        nameLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        emailLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        emailLabel->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        emailLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        phoneLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        phoneLabel->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        phoneLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        typeLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        typeLabel->setText(QCoreApplication::translate("MainWindow", "Type de Partenaire", nullptr));
        typeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        typeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Distributeur", nullptr));
        typeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Transporteur", nullptr));

        typeComboBox->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        statusComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Actif", nullptr));
        statusComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Inactif", nullptr));

        statusComboBox->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        addButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        updateButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        deleteButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #dc3545; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidgetPartenaire->setTabText(tabWidgetPartenaire->indexOf(partnersListTab), QCoreApplication::translate("MainWindow", "Liste des Partenaires", nullptr));
        statsHeaderLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        statsHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques des Partenaires", nullptr));
        cardTotalPartenaires->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelTotalPartenaires->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelTotalPartenaires->setText(QCoreApplication::translate("MainWindow", "Total Partenaires", nullptr));
        valueTotalPartenaires->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #2d4a1f; font-weight: bold;", nullptr));
        valueTotalPartenaires->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cardActifs->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelActifs->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelActifs->setText(QCoreApplication::translate("MainWindow", "Partenaires Actifs", nullptr));
        valueActifs->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #28a745; font-weight: bold;", nullptr));
        valueActifs->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cardInactifs->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 10px;", nullptr));
        labelInactifs->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #888;", nullptr));
        labelInactifs->setText(QCoreApplication::translate("MainWindow", "Partenaires Inactifs", nullptr));
        valueInactifs->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 32px; color: #dc3545; font-weight: bold;", nullptr));
        valueInactifs->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        tabWidgetPartenaire->setTabText(tabWidgetPartenaire->indexOf(statsTab), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        mailingHeaderLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 20px; color: #2d4a1f; font-weight: bold;", nullptr));
        mailingHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247 Envoyer un Email aux Partenaires", nullptr));
        mailingFrame->setStyleSheet(QCoreApplication::translate("MainWindow", "background: white; border: 2px solid #5d732c; border-radius: 8px;", nullptr));
        subjectLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        subjectLabel->setText(QCoreApplication::translate("MainWindow", "Sujet", nullptr));
        subjectLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        subjectLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le sujet du message...", nullptr));
        messageLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2d4a1f; font-weight: bold;", nullptr));
        messageLabel->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        messageTextEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        messageTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "R\303\251digez votre message ici...", nullptr));
        sendMailButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #ffd700; color: #2d4a1f; border: none; padding: 12px 30px; border-radius: 8px; font-weight: bold;", nullptr));
        sendMailButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 Envoyer aux Partenaires", nullptr));
        tabWidgetPartenaire->setTabText(tabWidgetPartenaire->indexOf(mailingTab), QCoreApplication::translate("MainWindow", "Mailing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
