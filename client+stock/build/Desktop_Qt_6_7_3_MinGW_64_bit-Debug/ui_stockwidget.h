/********************************************************************************
** Form generated from reading UI file 'stockwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKWIDGET_H
#define UI_STOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StockWidget
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBox;
    QPushButton *btnSearch;
    QPushButton *btnRefresh;
    QPushButton *btnClear;
    QHBoxLayout *contentLayout;
    QTableWidget *stockTable;
    QFrame *formPanel;
    QVBoxLayout *formLayout;
    QLabel *labelFormTitle;
    QLabel *labelId;
    QLineEdit *inputId;
    QLabel *labelType;
    QLineEdit *inputType;
    QLabel *labelQuantite;
    QSpinBox *inputQuantite;
    QLabel *labelSeuil;
    QSpinBox *inputSeuil;
    QHBoxLayout *formButtons;
    QPushButton *btnAdd;
    QPushButton *btnUpdate;
    QPushButton *btnDeleteForm;

    void setupUi(QWidget *StockWidget)
    {
        if (StockWidget->objectName().isEmpty())
            StockWidget->setObjectName("StockWidget");
        StockWidget->resize(1200, 700);
        StockWidget->setStyleSheet(QString::fromUtf8("\n"
"QWidget#StockWidget {\n"
"    background: #f5f5f5;\n"
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
"/* Buttons */\n"
"QPushButton {\n"
"    background: #b39609;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 15px;\n"
"    border-radius: 6px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: #c9a80a;\n"
"}\n"
"QPushButton#btnDeleteForm {\n"
"    background: #dc3545;\n"
"}\n"
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
"QTableWidget::item:selected {\n"
"    background: #b39609;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
""
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
"QLabel {\n"
"    color: #2d4a1f;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit, QSpinBox, QComboBox {\n"
"    padding: 8px 12px;\n"
"    border: 2px solid #5d732c;\n"
"    border-radius: 6px;\n"
"    background: white;\n"
"    color: #2d4a1f;\n"
"    font-size: 13px;\n"
"}\n"
"   "));
        mainLayout = new QVBoxLayout(StockWidget);
        mainLayout->setSpacing(15);
        mainLayout->setContentsMargins(15, 15, 15, 15);
        mainLayout->setObjectName("mainLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        searchBox = new QLineEdit(StockWidget);
        searchBox->setObjectName("searchBox");

        searchLayout->addWidget(searchBox);

        btnSearch = new QPushButton(StockWidget);
        btnSearch->setObjectName("btnSearch");

        searchLayout->addWidget(btnSearch);

        btnRefresh = new QPushButton(StockWidget);
        btnRefresh->setObjectName("btnRefresh");

        searchLayout->addWidget(btnRefresh);

        btnClear = new QPushButton(StockWidget);
        btnClear->setObjectName("btnClear");

        searchLayout->addWidget(btnClear);


        mainLayout->addLayout(searchLayout);

        contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(20);
        contentLayout->setObjectName("contentLayout");
        stockTable = new QTableWidget(StockWidget);
        if (stockTable->columnCount() < 4)
            stockTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        stockTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        stockTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        stockTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        stockTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        stockTable->setObjectName("stockTable");

        contentLayout->addWidget(stockTable);

        formPanel = new QFrame(StockWidget);
        formPanel->setObjectName("formPanel");
        formPanel->setMinimumSize(QSize(350, 0));
        formLayout = new QVBoxLayout(formPanel);
        formLayout->setSpacing(10);
        formLayout->setObjectName("formLayout");
        labelFormTitle = new QLabel(formPanel);
        labelFormTitle->setObjectName("labelFormTitle");

        formLayout->addWidget(labelFormTitle);

        labelId = new QLabel(formPanel);
        labelId->setObjectName("labelId");

        formLayout->addWidget(labelId);

        inputId = new QLineEdit(formPanel);
        inputId->setObjectName("inputId");

        formLayout->addWidget(inputId);

        labelType = new QLabel(formPanel);
        labelType->setObjectName("labelType");

        formLayout->addWidget(labelType);

        inputType = new QLineEdit(formPanel);
        inputType->setObjectName("inputType");

        formLayout->addWidget(inputType);

        labelQuantite = new QLabel(formPanel);
        labelQuantite->setObjectName("labelQuantite");

        formLayout->addWidget(labelQuantite);

        inputQuantite = new QSpinBox(formPanel);
        inputQuantite->setObjectName("inputQuantite");

        formLayout->addWidget(inputQuantite);

        labelSeuil = new QLabel(formPanel);
        labelSeuil->setObjectName("labelSeuil");

        formLayout->addWidget(labelSeuil);

        inputSeuil = new QSpinBox(formPanel);
        inputSeuil->setObjectName("inputSeuil");

        formLayout->addWidget(inputSeuil);

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


        contentLayout->addWidget(formPanel);


        mainLayout->addLayout(contentLayout);


        retranslateUi(StockWidget);

        QMetaObject::connectSlotsByName(StockWidget);
    } // setupUi

    void retranslateUi(QWidget *StockWidget)
    {
        StockWidget->setWindowTitle(QCoreApplication::translate("StockWidget", "Gestion des Stocks", nullptr));
        searchBox->setPlaceholderText(QCoreApplication::translate("StockWidget", "Rechercher un stock...", nullptr));
        btnSearch->setText(QCoreApplication::translate("StockWidget", "\360\237\224\215", nullptr));
        btnRefresh->setText(QCoreApplication::translate("StockWidget", "\360\237\224\204", nullptr));
        btnClear->setText(QCoreApplication::translate("StockWidget", "\342\234\226", nullptr));
        QTableWidgetItem *___qtablewidgetitem = stockTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("StockWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = stockTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("StockWidget", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = stockTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("StockWidget", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = stockTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("StockWidget", "Seuil Alerte", nullptr));
        labelFormTitle->setText(QCoreApplication::translate("StockWidget", "Informations du Stock", nullptr));
        labelId->setText(QCoreApplication::translate("StockWidget", "Id Stock", nullptr));
        labelType->setText(QCoreApplication::translate("StockWidget", "Type Stock", nullptr));
        labelQuantite->setText(QCoreApplication::translate("StockWidget", "Quantit\303\251", nullptr));
        labelSeuil->setText(QCoreApplication::translate("StockWidget", "Seuil Alerte", nullptr));
        btnAdd->setText(QCoreApplication::translate("StockWidget", "Ajouter Stock", nullptr));
        btnUpdate->setText(QCoreApplication::translate("StockWidget", "Modifier Stock", nullptr));
        btnDeleteForm->setText(QCoreApplication::translate("StockWidget", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockWidget: public Ui_StockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKWIDGET_H
