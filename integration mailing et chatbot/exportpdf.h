#ifndef EXPORTPDF_H
#define EXPORTPDF_H

#include <QObject>
#include <QTableWidget>
#include <QString>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFont>
#include <QColor>
#include <QRect>
#include <QDir>
#include <QPageSize>
#include <QPageLayout>
#include <QDebug>

class ExportPDF : public QObject
{
    Q_OBJECT

public:
    explicit ExportPDF(QObject *parent = nullptr);
    void exporterStockPDF(QTableWidget *table, QWidget *parentWidget = nullptr);

private:
    void dessinerEntete  (QPainter &p, int W, int &currentY);
    void dessinerTableau (QPainter &p, int W, int H, int &currentY, QTableWidget *table);
    void dessinerPiedPage(QPainter &p, int W, int H);
};

#endif // EXPORTPDF_H
