/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWidget
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QPushButton *btnSearch;
    QPushButton *btnRefresh;
    QPushButton *btnClear;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QHBoxLayout *tab1Layout;
    QTableWidget *clientTable;
    QFrame *formPanel;
    QVBoxLayout *formLayout;
    QLabel *labelIdClient;
    QLineEdit *inputIdClient;
    QLabel *labelNom;
    QLineEdit *inputNom;
    QLabel *labelPrenom;
    QLineEdit *inputPrenom;
    QLabel *labelEmail;
    QLineEdit *inputEmail;
    QLabel *labelTelephone;
    QLineEdit *inputTelephone;
    QLabel *labelTypeClient;
    QComboBox *inputTypeClient;
    QLabel *labelFeedback;
    QTextEdit *inputFeedback;
    QHBoxLayout *formButtons;
    QPushButton *btnAdd;
    QPushButton *btnUpdate;
    QPushButton *btnDeleteForm;
    QWidget *tab2;
    QVBoxLayout *tab2Layout;
    QLabel *statsLabel;

    void setupUi(QWidget *ClientWidget)
    {
        if (ClientWidget->objectName().isEmpty())
            ClientWidget->setObjectName("ClientWidget");
        ClientWidget->resize(1000, 768);
        ClientWidget->setStyleSheet(QString::fromUtf8("\n"
"QWidget#ClientWidget {\n"
"    background: #f5f5f5;\n"
"}\n"
"\n"
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
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #b39609;\n"
"    color: white;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #c9a80a;\n"
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
"QPushButton {\n"
"    background: #b39609;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 15px;\n"
"    border-radius: 6p"
                        "x;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: #c9a80a;\n"
"}\n"
"\n"
"QPushButton#btnDeleteForm {\n"
"    background: #dc3545;\n"
"}\n"
"\n"
"QPushButton#btnDeleteForm:hover {\n"
"    background: #c82333;\n"
"}\n"
"\n"
"/* Table */\n"
"QTableWidget {\n"
"    background: white;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 8px;\n"
"    gridline-color: #e0e0e0;\n"
"    font-size: 13px;\n"
"    color: #2d4a1f;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background: #b39609;\n"
"    color: white;\n"
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
"QLabel {\n"
"    color: #2d4a1f;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLineEdit, QComboBox, QTextEdit {\n"
"    padd"
                        "ing: 8px 12px;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    background: white;\n"
"    color: #2d4a1f;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    min-height: 80px;\n"
"    max-height: 100px;\n"
"}\n"
"   "));
        mainLayout = new QVBoxLayout(ClientWidget);
        mainLayout->setSpacing(10);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setObjectName("mainLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        searchBox = new QLineEdit(ClientWidget);
        searchBox->setObjectName("searchBox");

        searchLayout->addWidget(searchBox);

        btnSearch = new QPushButton(ClientWidget);
        btnSearch->setObjectName("btnSearch");

        searchLayout->addWidget(btnSearch);

        btnRefresh = new QPushButton(ClientWidget);
        btnRefresh->setObjectName("btnRefresh");

        searchLayout->addWidget(btnRefresh);

        btnClear = new QPushButton(ClientWidget);
        btnClear->setObjectName("btnClear");

        searchLayout->addWidget(btnClear);


        mainLayout->addLayout(searchLayout);

        tabWidget = new QTabWidget(ClientWidget);
        tabWidget->setObjectName("tabWidget");
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        tab1Layout = new QHBoxLayout(tab1);
        tab1Layout->setSpacing(15);
        tab1Layout->setContentsMargins(10, 10, 10, 10);
        tab1Layout->setObjectName("tab1Layout");
        clientTable = new QTableWidget(tab1);
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

        tab1Layout->addWidget(clientTable);

        formPanel = new QFrame(tab1);
        formPanel->setObjectName("formPanel");
        formPanel->setMinimumSize(QSize(300, 0));
        formLayout = new QVBoxLayout(formPanel);
        formLayout->setSpacing(10);
        formLayout->setContentsMargins(10, 10, 10, 10);
        formLayout->setObjectName("formLayout");
        labelIdClient = new QLabel(formPanel);
        labelIdClient->setObjectName("labelIdClient");

        formLayout->addWidget(labelIdClient);

        inputIdClient = new QLineEdit(formPanel);
        inputIdClient->setObjectName("inputIdClient");
        inputIdClient->setReadOnly(true);

        formLayout->addWidget(inputIdClient);

        labelNom = new QLabel(formPanel);
        labelNom->setObjectName("labelNom");

        formLayout->addWidget(labelNom);

        inputNom = new QLineEdit(formPanel);
        inputNom->setObjectName("inputNom");

        formLayout->addWidget(inputNom);

        labelPrenom = new QLabel(formPanel);
        labelPrenom->setObjectName("labelPrenom");

        formLayout->addWidget(labelPrenom);

        inputPrenom = new QLineEdit(formPanel);
        inputPrenom->setObjectName("inputPrenom");

        formLayout->addWidget(inputPrenom);

        labelEmail = new QLabel(formPanel);
        labelEmail->setObjectName("labelEmail");

        formLayout->addWidget(labelEmail);

        inputEmail = new QLineEdit(formPanel);
        inputEmail->setObjectName("inputEmail");

        formLayout->addWidget(inputEmail);

        labelTelephone = new QLabel(formPanel);
        labelTelephone->setObjectName("labelTelephone");

        formLayout->addWidget(labelTelephone);

        inputTelephone = new QLineEdit(formPanel);
        inputTelephone->setObjectName("inputTelephone");

        formLayout->addWidget(inputTelephone);

        labelTypeClient = new QLabel(formPanel);
        labelTypeClient->setObjectName("labelTypeClient");

        formLayout->addWidget(labelTypeClient);

        inputTypeClient = new QComboBox(formPanel);
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->addItem(QString());
        inputTypeClient->setObjectName("inputTypeClient");

        formLayout->addWidget(inputTypeClient);

        labelFeedback = new QLabel(formPanel);
        labelFeedback->setObjectName("labelFeedback");

        formLayout->addWidget(labelFeedback);

        inputFeedback = new QTextEdit(formPanel);
        inputFeedback->setObjectName("inputFeedback");

        formLayout->addWidget(inputFeedback);

        formButtons = new QHBoxLayout();
        formButtons->setObjectName("formButtons");
        btnAdd = new QPushButton(formPanel);
        btnAdd->setObjectName("btnAdd");

        formButtons->addWidget(btnAdd);

        btnUpdate = new QPushButton(formPanel);
        btnUpdate->setObjectName("btnUpdate");

        formButtons->addWidget(btnUpdate);

        btnDeleteForm = new QPushButton(formPanel);
        btnDeleteForm->setObjectName("btnDeleteForm");

        formButtons->addWidget(btnDeleteForm);


        formLayout->addLayout(formButtons);


        tab1Layout->addWidget(formPanel);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        tab2Layout = new QVBoxLayout(tab2);
        tab2Layout->setObjectName("tab2Layout");
        statsLabel = new QLabel(tab2);
        statsLabel->setObjectName("statsLabel");
        statsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tab2Layout->addWidget(statsLabel);

        tabWidget->addTab(tab2, QString());

        mainLayout->addWidget(tabWidget);


        retranslateUi(ClientWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        ClientWidget->setWindowTitle(QCoreApplication::translate("ClientWidget", "Gestion Clients", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("ClientWidget", "Rechercher un client...", nullptr));
        btnSearch->setText(QCoreApplication::translate("ClientWidget", "\360\237\224\215", nullptr));
        btnRefresh->setText(QCoreApplication::translate("ClientWidget", "\360\237\224\204", nullptr));
        btnClear->setText(QCoreApplication::translate("ClientWidget", "\342\234\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ClientWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ClientWidget", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ClientWidget", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ClientWidget", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ClientWidget", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = clientTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ClientWidget", "Type Client", nullptr));
        labelIdClient->setText(QCoreApplication::translate("ClientWidget", "ID Client", nullptr));
        inputIdClient->setPlaceholderText(QCoreApplication::translate("ClientWidget", "G\303\251n\303\251r\303\251 automatiquement", nullptr));
        labelNom->setText(QCoreApplication::translate("ClientWidget", "Nom", nullptr));
        labelPrenom->setText(QCoreApplication::translate("ClientWidget", "Pr\303\251nom", nullptr));
        labelEmail->setText(QCoreApplication::translate("ClientWidget", "Email", nullptr));
        labelTelephone->setText(QCoreApplication::translate("ClientWidget", "T\303\251l\303\251phone", nullptr));
        labelTypeClient->setText(QCoreApplication::translate("ClientWidget", "Type Client", nullptr));
        inputTypeClient->setItemText(0, QCoreApplication::translate("ClientWidget", "Particulier", nullptr));
        inputTypeClient->setItemText(1, QCoreApplication::translate("ClientWidget", "Entreprise", nullptr));
        inputTypeClient->setItemText(2, QCoreApplication::translate("ClientWidget", "Revendeur", nullptr));
        inputTypeClient->setItemText(3, QCoreApplication::translate("ClientWidget", "Grossiste", nullptr));

        labelFeedback->setText(QCoreApplication::translate("ClientWidget", "Feedback / Avis", nullptr));
        btnAdd->setText(QCoreApplication::translate("ClientWidget", "Ajouter", nullptr));
        btnUpdate->setText(QCoreApplication::translate("ClientWidget", "Modifier", nullptr));
        btnDeleteForm->setText(QCoreApplication::translate("ClientWidget", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("ClientWidget", "Liste des Clients", nullptr));
        statsLabel->setText(QCoreApplication::translate("ClientWidget", "Statistiques Clients", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("ClientWidget", "Statistiques", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
