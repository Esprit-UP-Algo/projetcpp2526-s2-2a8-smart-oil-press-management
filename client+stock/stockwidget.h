#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class StockWidget; }
QT_END_NAMESPACE

class StockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StockWidget(QWidget *parent = nullptr);
    ~StockWidget();

private:
    Ui::StockWidget *ui;
};

#endif // STOCKWIDGET_H
