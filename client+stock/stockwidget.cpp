#include "stockwidget.h"
#include "ui_stockwidget.h"

StockWidget::StockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StockWidget)
{
    ui->setupUi(this);
}

StockWidget::~StockWidget()
{
    delete ui;
}
