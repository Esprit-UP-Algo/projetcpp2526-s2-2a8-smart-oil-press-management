#ifndef EMPLOYE_PDF_H
#define EMPLOYE_PDF_H

#include <QTableWidget>
#include <QWidget>

// ============================================================
//  EmployePDF — Module d'export PDF du tableau des Employés
//  Utilisation dans mainwindow.cpp :
//      EmployePDF::exporter(ui->employeTable, this);
// ============================================================
class EmployePDF
{
public:
    static void exporter(QTableWidget *table, QWidget *parent);

private:
    EmployePDF() = delete;
};

#endif // EMPLOYE_PDF_H
