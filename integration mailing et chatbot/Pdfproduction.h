#ifndef PDFPRODUCTION_H
#define PDFPRODUCTION_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QPrinter>
#include <QPainter>
#include <QFont>
#include <QRect>
#include <QColor>
#include <QPageSize>
#include <QPageLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

class PdfProduction
{
public:
    PdfProduction();

    // Export all productions from DB to a PDF file
    void exporterPDF(QWidget *parent);

private:
    void dessinerPDF(QPainter &painter, QPrinter &printer);
    bool chargerDonnees();

    struct LigneProduction {
        int    id;
        QDate  date;
        double quantiteOlive;
        double quantiteHuile;
        double rendement;
    };

    QList<LigneProduction> lignes;
};

#endif // PDFPRODUCTION_H
