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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QFrame *sidebar;
    QVBoxLayout *vboxLayout;
    QLabel *logoLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *employeesButton;
    QPushButton *clientsButton;
    QPushButton *stockButton;
    QPushButton *machinesButton;
    QPushButton *productionButton;
    QPushButton *partnersButton;
    QSpacerItem *bottomSpacer;
    QPushButton *logoutButton;
    QFrame *mainFrame;
    QVBoxLayout *vboxLayout1;
    QLabel *headerLabel;
    QTabWidget *tabWidget;
    QWidget *partnersListTab;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout1;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *exportButton;
    QPushButton *filterButton;
    QHBoxLayout *hboxLayout2;
    QTableWidget *partnersTable;
    QFrame *formFrame;
    QVBoxLayout *vboxLayout3;
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
    QSpacerItem *formSpacer;
    QHBoxLayout *hboxLayout3;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;
    QWidget *statsTab;
    QVBoxLayout *vboxLayout4;
    QLabel *statsHeaderLabel;
    QFrame *statsFrame;
    QVBoxLayout *vboxLayout5;
    QLabel *statsContentLabel;
    QWidget *mailingTab;
    QVBoxLayout *vboxLayout6;
    QLabel *mailingHeaderLabel;
    QTextEdit *messageTextEdit;
    QPushButton *sendMailButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1313, 861);
        MainWindow->setMaximumSize(QSize(1313, 861));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        hboxLayout = new QHBoxLayout(centralwidget);
        hboxLayout->setSpacing(0);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        sidebar = new QFrame(centralwidget);
        sidebar->setObjectName("sidebar");
        vboxLayout = new QVBoxLayout(sidebar);
        vboxLayout->setSpacing(10);
        vboxLayout->setContentsMargins(15, 15, 15, 15);
        vboxLayout->setObjectName("vboxLayout");
        logoLabel = new QLabel(sidebar);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(160, 90));
        logoLabel->setMaximumSize(QSize(180, 110));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/resources/logo.png")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout->addWidget(logoLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(verticalSpacer);

        employeesButton = new QPushButton(sidebar);
        employeesButton->setObjectName("employeesButton");

        vboxLayout->addWidget(employeesButton);

        clientsButton = new QPushButton(sidebar);
        clientsButton->setObjectName("clientsButton");

        vboxLayout->addWidget(clientsButton);

        stockButton = new QPushButton(sidebar);
        stockButton->setObjectName("stockButton");

        vboxLayout->addWidget(stockButton);

        machinesButton = new QPushButton(sidebar);
        machinesButton->setObjectName("machinesButton");

        vboxLayout->addWidget(machinesButton);

        productionButton = new QPushButton(sidebar);
        productionButton->setObjectName("productionButton");

        vboxLayout->addWidget(productionButton);

        partnersButton = new QPushButton(sidebar);
        partnersButton->setObjectName("partnersButton");

        vboxLayout->addWidget(partnersButton);

        bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(bottomSpacer);

        logoutButton = new QPushButton(sidebar);
        logoutButton->setObjectName("logoutButton");

        vboxLayout->addWidget(logoutButton);


        hboxLayout->addWidget(sidebar);

        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName("mainFrame");
        vboxLayout1 = new QVBoxLayout(mainFrame);
        vboxLayout1->setSpacing(0);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName("vboxLayout1");
        headerLabel = new QLabel(mainFrame);
        headerLabel->setObjectName("headerLabel");

        vboxLayout1->addWidget(headerLabel);

        tabWidget = new QTabWidget(mainFrame);
        tabWidget->setObjectName("tabWidget");
        partnersListTab = new QWidget();
        partnersListTab->setObjectName("partnersListTab");
        vboxLayout2 = new QVBoxLayout(partnersListTab);
        vboxLayout2->setSpacing(15);
        vboxLayout2->setContentsMargins(20, 20, 20, 20);
        vboxLayout2->setObjectName("vboxLayout2");
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(10);
        hboxLayout1->setObjectName("hboxLayout1");
        searchLineEdit = new QLineEdit(partnersListTab);
        searchLineEdit->setObjectName("searchLineEdit");

        hboxLayout1->addWidget(searchLineEdit);

        searchButton = new QPushButton(partnersListTab);
        searchButton->setObjectName("searchButton");

        hboxLayout1->addWidget(searchButton);

        exportButton = new QPushButton(partnersListTab);
        exportButton->setObjectName("exportButton");

        hboxLayout1->addWidget(exportButton);

        filterButton = new QPushButton(partnersListTab);
        filterButton->setObjectName("filterButton");

        hboxLayout1->addWidget(filterButton);


        vboxLayout2->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(15);
        hboxLayout2->setObjectName("hboxLayout2");
        partnersTable = new QTableWidget(partnersListTab);
        if (partnersTable->columnCount() < 5)
            partnersTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        partnersTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        partnersTable->setObjectName("partnersTable");
        partnersTable->setColumnCount(5);

        hboxLayout2->addWidget(partnersTable);

        formFrame = new QFrame(partnersListTab);
        formFrame->setObjectName("formFrame");
        formFrame->setMinimumSize(QSize(300, 0));
        vboxLayout3 = new QVBoxLayout(formFrame);
        vboxLayout3->setSpacing(12);
        vboxLayout3->setContentsMargins(20, 20, 20, 20);
        vboxLayout3->setObjectName("vboxLayout3");
        nameLabel = new QLabel(formFrame);
        nameLabel->setObjectName("nameLabel");

        vboxLayout3->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(formFrame);
        nameLineEdit->setObjectName("nameLineEdit");

        vboxLayout3->addWidget(nameLineEdit);

        emailLabel = new QLabel(formFrame);
        emailLabel->setObjectName("emailLabel");

        vboxLayout3->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(formFrame);
        emailLineEdit->setObjectName("emailLineEdit");

        vboxLayout3->addWidget(emailLineEdit);

        phoneLabel = new QLabel(formFrame);
        phoneLabel->setObjectName("phoneLabel");

        vboxLayout3->addWidget(phoneLabel);

        phoneLineEdit = new QLineEdit(formFrame);
        phoneLineEdit->setObjectName("phoneLineEdit");

        vboxLayout3->addWidget(phoneLineEdit);

        typeLabel = new QLabel(formFrame);
        typeLabel->setObjectName("typeLabel");

        vboxLayout3->addWidget(typeLabel);

        typeComboBox = new QComboBox(formFrame);
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->setObjectName("typeComboBox");

        vboxLayout3->addWidget(typeComboBox);

        statusLabel = new QLabel(formFrame);
        statusLabel->setObjectName("statusLabel");

        vboxLayout3->addWidget(statusLabel);

        statusComboBox = new QComboBox(formFrame);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        vboxLayout3->addWidget(statusComboBox);

        formSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout3->addItem(formSpacer);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(10);
        hboxLayout3->setObjectName("hboxLayout3");
        addButton = new QPushButton(formFrame);
        addButton->setObjectName("addButton");

        hboxLayout3->addWidget(addButton);

        updateButton = new QPushButton(formFrame);
        updateButton->setObjectName("updateButton");

        hboxLayout3->addWidget(updateButton);

        deleteButton = new QPushButton(formFrame);
        deleteButton->setObjectName("deleteButton");

        hboxLayout3->addWidget(deleteButton);


        vboxLayout3->addLayout(hboxLayout3);


        hboxLayout2->addWidget(formFrame);


        vboxLayout2->addLayout(hboxLayout2);

        tabWidget->addTab(partnersListTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName("statsTab");
        vboxLayout4 = new QVBoxLayout(statsTab);
        vboxLayout4->setSpacing(20);
        vboxLayout4->setContentsMargins(20, 20, 20, 20);
        vboxLayout4->setObjectName("vboxLayout4");
        statsHeaderLabel = new QLabel(statsTab);
        statsHeaderLabel->setObjectName("statsHeaderLabel");
        statsHeaderLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout4->addWidget(statsHeaderLabel);

        statsFrame = new QFrame(statsTab);
        statsFrame->setObjectName("statsFrame");
        vboxLayout5 = new QVBoxLayout(statsFrame);
        vboxLayout5->setObjectName("vboxLayout5");
        statsContentLabel = new QLabel(statsFrame);
        statsContentLabel->setObjectName("statsContentLabel");
        statsContentLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout5->addWidget(statsContentLabel);


        vboxLayout4->addWidget(statsFrame);

        tabWidget->addTab(statsTab, QString());
        mailingTab = new QWidget();
        mailingTab->setObjectName("mailingTab");
        vboxLayout6 = new QVBoxLayout(mailingTab);
        vboxLayout6->setSpacing(15);
        vboxLayout6->setContentsMargins(20, 20, 20, 20);
        vboxLayout6->setObjectName("vboxLayout6");
        mailingHeaderLabel = new QLabel(mailingTab);
        mailingHeaderLabel->setObjectName("mailingHeaderLabel");
        mailingHeaderLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout6->addWidget(mailingHeaderLabel);

        messageTextEdit = new QTextEdit(mailingTab);
        messageTextEdit->setObjectName("messageTextEdit");

        vboxLayout6->addWidget(messageTextEdit);

        sendMailButton = new QPushButton(mailingTab);
        sendMailButton->setObjectName("sendMailButton");

        vboxLayout6->addWidget(sendMailButton);

        tabWidget->addTab(mailingTab, QString());

        vboxLayout1->addWidget(tabWidget);


        hboxLayout->addWidget(mainFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZitTech - Gestion des Partenaires", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"/* GLOBAL */\n"
"QMainWindow {\n"
"    background-color: #f5f5f5;\n"
"    font-family: Segoe UI;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"/* SIDEBAR */\n"
"#sidebar {\n"
"    background-color: #2d4a1f;\n"
"}\n"
"\n"
"#sidebar QPushButton {\n"
"    background-color: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    text-align: left;\n"
"}\n"
"\n"
"#sidebar QPushButton:hover {\n"
"    background-color: #ffed4e;\n"
"}\n"
"\n"
"/* HEADER */\n"
"#headerLabel {\n"
"    font-size: 26px;\n"
"    font-weight: bold;\n"
"    color: #2d4a1f;\n"
"    padding: 20px;\n"
"}\n"
"\n"
"/* TAB WIDGET */\n"
"QTabWidget::pane {\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 8px;\n"
"    background: white;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #eaeaea;\n"
"    padding: 10px 25px;\n"
"    margin-right: 5px;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;\n"
"    color: #2d4a1f;\n"
"    font-"
                        "weight: bold;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #ffd700;\n"
"}\n"
"\n"
"/* INPUTS */\n"
"QLineEdit, QComboBox, QTextEdit {\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    padding: 6px;\n"
"    background: white;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"/* SEARCH BAR */\n"
"#searchLineEdit {\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    padding: 10px;\n"
"    background: white;\n"
"    color: #2d4a1f;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* TABLE */\n"
"QTableWidget {\n"
"    background: white;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #5d732c;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* ACTION BUTTONS */\n"
"QPushButton {\n"
"    background-color: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border-radius: 8px;\n"
"    padding: 8px 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    backgro"
                        "und-color: #ffed4e;\n"
"}\n"
"\n"
"/* SEARCH BUTTONS - JAUNE */\n"
"#searchButton, #filterButton, #refreshButton, #exportButton {\n"
"    background-color: #ffd700;\n"
"    color: #2d4a1f;\n"
"    border-radius: 8px;\n"
"    padding: 10px 16px;\n"
"    font-weight: bold;\n"
"    min-width: 100px;\n"
"}\n"
"\n"
"#searchButton:hover, #filterButton:hover, #refreshButton:hover, #exportButton:hover {\n"
"    background-color: #ffed4e;\n"
"}\n"
"\n"
"#clearButton {\n"
"    background-color: #dc3545;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 10px 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#clearButton:hover {\n"
"    background-color: #c82333;\n"
"}\n"
"   ", nullptr));
        employeesButton->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 Employ\303\251s", nullptr));
        clientsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 Clients", nullptr));
        stockButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Stock", nullptr));
        machinesButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 Machines", nullptr));
        productionButton->setText(QCoreApplication::translate("MainWindow", "\360\237\217\255 Production", nullptr));
        partnersButton->setText(QCoreApplication::translate("MainWindow", "\360\237\244\235 Partenaires", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 D\303\251connexion", nullptr));
        headerLabel->setText(QCoreApplication::translate("MainWindow", "Gestion des Partenaires", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher un partenaire (nom, email, t\303\251l\303\251phone)...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\245 ", nullptr));
        filterButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\275 ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = partnersTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = partnersTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = partnersTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = partnersTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = partnersTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        nameLabel->setText(QCoreApplication::translate("MainWindow", "Nom du Partenaire", nullptr));
        emailLabel->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        phoneLabel->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        typeLabel->setText(QCoreApplication::translate("MainWindow", "Type de Partenaire", nullptr));
        typeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        typeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Distributeur", nullptr));
        typeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Transporteur", nullptr));

        statusLabel->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        statusComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Actif", nullptr));
        statusComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Inactif", nullptr));

        addButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        deleteButton->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"QPushButton {\n"
"    background-color: #dc3545;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 8px 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #c82333;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #a71d2a;\n"
"}\n"
"                     ", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(partnersListTab), QCoreApplication::translate("MainWindow", "Liste des Partenaires", nullptr));
        statsHeaderLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 18px; font-weight: bold; color: #2d4a1f;", nullptr));
        statsHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques des partenaires", nullptr));
        statsFrame->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: white; border: 2px solid #5d732c; border-radius: 8px; padding: 20px;", nullptr));
        statsContentLabel->setText(QCoreApplication::translate("MainWindow", "Contenu des statistiques \303\240 d\303\251velopper...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statsTab), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        mailingHeaderLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 18px; font-weight: bold; color: #2d4a1f;", nullptr));
        mailingHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247 Envoyer un mail aux partenaires", nullptr));
        messageTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "R\303\251digez votre message ici...", nullptr));
        sendMailButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 Envoyer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mailingTab), QCoreApplication::translate("MainWindow", "Mailing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
