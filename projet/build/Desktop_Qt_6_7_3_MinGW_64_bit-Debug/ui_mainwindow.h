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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
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
    QPushButton *btnEmploye;
    QPushButton *btnClient;
    QPushButton *btnStock;
    QPushButton *btnMachine;
    QPushButton *btnProduction;
    QPushButton *btnCommande;
    QPushButton *btnSetting;
    QPushButton *btnLogout;
    QFrame *contentArea;
    QVBoxLayout *contentLayout;
    QFrame *headerFrame;
    QHBoxLayout *headerLayout;
    QLabel *headerTitle;
    QSpacerItem *spacerItem;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *tab1Layout;
    QHBoxLayout *searchLayout;
    QPushButton *btnRefresh;
    QPushButton *btnClear;
    QLineEdit *searchBox;
    QPushButton *btnSearch;
    QHBoxLayout *splitLayout;
    QTableWidget *machineTable;
    QFrame *formPanel;
    QVBoxLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelNom;
    QLineEdit *inputNom;
    QLabel *labelModele;
    QLineEdit *inputModele;
    QLabel *labelEtat;
    QComboBox *inputEtat;
    QLabel *label_3;
    QLabel *label_6;
    QSpacerItem *spacerItem1;
    QHBoxLayout *formButtons;
    QPushButton *btnAdd;
    QPushButton *btnUpdate;
    QPushButton *btnDeleteForm;
    QWidget *tab2;
    QVBoxLayout *tab2Layout;
    QFrame *frame;
    QFrame *frame_2;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 988);
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
        sidebarLayout->setContentsMargins(15, 15, 15, 15);
        sidebarLayout->setObjectName("sidebarLayout");
        logoLabel = new QLabel(sidebar);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(160, 90));
        logoLabel->setMaximumSize(QSize(180, 110));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/logo/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarLayout->addWidget(logoLabel);

        btnEmploye = new QPushButton(sidebar);
        btnEmploye->setObjectName("btnEmploye");
        btnEmploye->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnEmploye);

        btnClient = new QPushButton(sidebar);
        btnClient->setObjectName("btnClient");
        btnClient->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnClient);

        btnStock = new QPushButton(sidebar);
        btnStock->setObjectName("btnStock");
        btnStock->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnStock);

        btnMachine = new QPushButton(sidebar);
        btnMachine->setObjectName("btnMachine");
        btnMachine->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnMachine);

        btnProduction = new QPushButton(sidebar);
        btnProduction->setObjectName("btnProduction");
        btnProduction->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";\n"
""));

        sidebarLayout->addWidget(btnProduction);

        btnCommande = new QPushButton(sidebar);
        btnCommande->setObjectName("btnCommande");
        btnCommande->setStyleSheet(QString::fromUtf8("background: #D7B547; color: rgb(109, 55, 0); border: none; padding: 12px; border-radius: 8px; font-weight: bold; text-align: left;\n"
"font: 12pt \"Segoe UI\";\n"
""));

        sidebarLayout->addWidget(btnCommande);

        btnSetting = new QPushButton(sidebar);
        btnSetting->setObjectName("btnSetting");
        btnSetting->setStyleSheet(QString::fromUtf8("background: transparent; color:rgb(147, 147, 110); border: none; padding: 8px; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnSetting);

        btnLogout = new QPushButton(sidebar);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setStyleSheet(QString::fromUtf8("background: transparent; color:rgb(147, 147, 110); border: none; padding: 8px; text-align: left;\n"
"font: 12pt \"Segoe UI\";"));

        sidebarLayout->addWidget(btnLogout);


        mainLayout->addWidget(sidebar);

        contentArea = new QFrame(centralwidget);
        contentArea->setObjectName("contentArea");
        contentLayout = new QVBoxLayout(contentArea);
        contentLayout->setSpacing(0);
        contentLayout->setContentsMargins(0, 0, 0, 0);
        contentLayout->setObjectName("contentLayout");
        headerFrame = new QFrame(contentArea);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setMinimumSize(QSize(0, 80));
        headerLayout = new QHBoxLayout(headerFrame);
        headerLayout->setSpacing(20);
        headerLayout->setContentsMargins(20, 20, 20, 20);
        headerLayout->setObjectName("headerLayout");
        headerTitle = new QLabel(headerFrame);
        headerTitle->setObjectName("headerTitle");

        headerLayout->addWidget(headerTitle);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(spacerItem);


        contentLayout->addWidget(headerFrame);

        tabWidget = new QTabWidget(contentArea);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        tab1Layout = new QVBoxLayout(tab1);
        tab1Layout->setSpacing(15);
        tab1Layout->setContentsMargins(20, 20, 20, 20);
        tab1Layout->setObjectName("tab1Layout");
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        btnRefresh = new QPushButton(tab1);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setStyleSheet(QString::fromUtf8("background: #D7B547; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;"));

        searchLayout->addWidget(btnRefresh);

        btnClear = new QPushButton(tab1);
        btnClear->setObjectName("btnClear");
        btnClear->setStyleSheet(QString::fromUtf8("background: #D7B547; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;"));

        searchLayout->addWidget(btnClear);

        searchBox = new QLineEdit(tab1);
        searchBox->setObjectName("searchBox");

        searchLayout->addWidget(searchBox);

        btnSearch = new QPushButton(tab1);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setStyleSheet(QString::fromUtf8("background: #D7B547; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;"));

        searchLayout->addWidget(btnSearch);


        tab1Layout->addLayout(searchLayout);

        splitLayout = new QHBoxLayout();
        splitLayout->setSpacing(15);
        splitLayout->setObjectName("splitLayout");
        machineTable = new QTableWidget(tab1);
        if (machineTable->rowCount() < 17)
            machineTable->setRowCount(17);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(13, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(14, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(15, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        machineTable->setVerticalHeaderItem(16, __qtablewidgetitem16);
        machineTable->setObjectName("machineTable");

        splitLayout->addWidget(machineTable);

        formPanel = new QFrame(tab1);
        formPanel->setObjectName("formPanel");
        formPanel->setMinimumSize(QSize(350, 0));
        formPanel->setMaximumSize(QSize(400, 16777215));
        formLayout = new QVBoxLayout(formPanel);
        formLayout->setSpacing(15);
        formLayout->setContentsMargins(20, 20, 20, 20);
        formLayout->setObjectName("formLayout");
        label = new QLabel(formPanel);
        label->setObjectName("label");

        formLayout->addWidget(label);

        label_2 = new QLabel(formPanel);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(94, 94, 0);font: 900 italic 14pt \"Segoe UI\";"));

        formLayout->addWidget(label_2);

        labelNom = new QLabel(formPanel);
        labelNom->setObjectName("labelNom");
        labelNom->setStyleSheet(QString::fromUtf8("color:rgb(47, 47, 0);\n"
"\n"
"font: 900 10pt \"Segoe UI\";\n"
""));

        formLayout->addWidget(labelNom);

        inputNom = new QLineEdit(formPanel);
        inputNom->setObjectName("inputNom");

        formLayout->addWidget(inputNom);

        labelModele = new QLabel(formPanel);
        labelModele->setObjectName("labelModele");
        labelModele->setStyleSheet(QString::fromUtf8("color:rgb(47, 47, 0);\n"
"\n"
"font: 900 10pt \"Segoe UI\";\n"
""));

        formLayout->addWidget(labelModele);

        inputModele = new QLineEdit(formPanel);
        inputModele->setObjectName("inputModele");

        formLayout->addWidget(inputModele);

        labelEtat = new QLabel(formPanel);
        labelEtat->setObjectName("labelEtat");
        labelEtat->setStyleSheet(QString::fromUtf8("color:rgb(47, 47, 0);\n"
"\n"
"font: 900 10pt \"Segoe UI\";"));

        formLayout->addWidget(labelEtat);

        inputEtat = new QComboBox(formPanel);
        inputEtat->setObjectName("inputEtat");

        formLayout->addWidget(inputEtat);

        label_3 = new QLabel(formPanel);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color:rgb(47, 47, 0);\n"
"\n"
"font: 900 10pt \"Segoe UI\";"));

        formLayout->addWidget(label_3);

        label_6 = new QLabel(formPanel);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("background:rgb(27, 27, 27);"));

        formLayout->addWidget(label_6);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Ignored);

        formLayout->addItem(spacerItem1);

        formButtons = new QHBoxLayout();
        formButtons->setSpacing(10);
        formButtons->setObjectName("formButtons");
        btnAdd = new QPushButton(formPanel);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setStyleSheet(QString::fromUtf8("background: #D7B547; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;"));

        formButtons->addWidget(btnAdd);

        btnUpdate = new QPushButton(formPanel);
        btnUpdate->setObjectName("btnUpdate");
        btnUpdate->setStyleSheet(QString::fromUtf8("background: #D7B547; color: #2d4a1f; border: none; padding: 10px 15px; border-radius: 6px; font-weight: bold;"));

        formButtons->addWidget(btnUpdate);

        btnDeleteForm = new QPushButton(formPanel);
        btnDeleteForm->setObjectName("btnDeleteForm");

        formButtons->addWidget(btnDeleteForm);


        formLayout->addLayout(formButtons);


        splitLayout->addWidget(formPanel);


        tab1Layout->addLayout(splitLayout);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        tab2Layout = new QVBoxLayout(tab2);
        tab2Layout->setObjectName("tab2Layout");
        frame = new QFrame(tab2);
        frame->setObjectName("frame");
        QFont font;
        font.setPointSize(20);
        frame->setFont(font);
        frame->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 127);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        frame->setLineWidth(10);
        frame->setMidLineWidth(10);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(60, 30, 681, 361));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(18, 18, 0);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 70, 601, 41));
        label_5->setStyleSheet(QString::fromUtf8("font: 900 14pt \"Segoe UI\";color:rgb(175, 175, 87);\n"
""));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(330, 120, 49, 16));
        label_7->setStyleSheet(QString::fromUtf8("color:rgb(225, 225, 225);\n"
"font: 16pt \"Segoe UI\";"));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(320, 150, 131, 16));
        label_9 = new QLabel(frame_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(340, 180, 49, 16));
        label_9->setStyleSheet(QString::fromUtf8("color:rgb(225, 225, 225);\n"
"font: 16pt \"Segoe UI\";"));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(320, 210, 131, 16));

        tab2Layout->addWidget(frame);

        label_4 = new QLabel(tab2);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
""));

        tab2Layout->addWidget(label_4);

        tabWidget->addTab(tab2, QString());

        contentLayout->addWidget(tabWidget);


        mainLayout->addWidget(contentArea);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZitTech - Gestion des Machines", nullptr));
        btnEmploye->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        btnClient->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Clients", nullptr));
        btnStock->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Stock", nullptr));
        btnMachine->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 Machines", nullptr));
        btnProduction->setText(QCoreApplication::translate("MainWindow", "\360\237\217\255 Production", nullptr));
        btnCommande->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 Commandes", nullptr));
#if QT_CONFIG(tooltip)
        btnSetting->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSetting->setText(QCoreApplication::translate("MainWindow", "   \342\232\231\357\270\217 Param\303\250tres", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "   \360\237\232\252 D\303\251connexion", nullptr));
        headerTitle->setText(QCoreApplication::translate("MainWindow", "Gestion De Stock \360\237\223\246", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\342\234\226", nullptr));
        searchBox->setText(QCoreApplication::translate("MainWindow", "Chercher ici ...", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher une machine...", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem = machineTable->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID: STK001\n"
"Mati\303\250re Premi\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = machineTable->verticalHeaderItem(4);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "ID: STK002\n"
"Produit Fini", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = machineTable->verticalHeaderItem(8);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "ID: STK003\n"
"Emballage", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = machineTable->verticalHeaderItem(12);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "ID: STK004\n"
"Mati\303\250re Premi\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = machineTable->verticalHeaderItem(16);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "ID: STK005\n"
"Produit Fini", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Informations du Stock", nullptr));
        labelNom->setText(QCoreApplication::translate("MainWindow", "Id_Stock", nullptr));
        inputNom->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelModele->setText(QCoreApplication::translate("MainWindow", "Type_Stock", nullptr));
        inputModele->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        labelEtat->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        inputEtat->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border: 2px solid #5d732c; border-radius: 6px;", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Seuile_Alerte", nullptr));
        label_6->setText(QString());
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Ajouter Stock", nullptr));
        btnUpdate->setText(QCoreApplication::translate("MainWindow", "Modifier Stock", nullptr));
#if QT_CONFIG(tooltip)
        btnDeleteForm->setToolTip(QCoreApplication::translate("MainWindow", "Supprimer la machine s\303\251lectionn\303\251e", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDeleteForm->setStyleSheet(QCoreApplication::translate("MainWindow", "background: #dc3545; color: white; border: none; padding: 12px; border-radius: 8px; font-weight: bold;", nullptr));
        btnDeleteForm->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Liste Des Stocks", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "background: #D7B547;", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("MainWindow", "                                                   Statistiques", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "127", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Total Stocks", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "45", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Alerte Basse", nullptr));
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
