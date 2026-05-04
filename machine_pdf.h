#ifndef MACHINE_PDF_H
#define MACHINE_PDF_H

#include <QTableWidget>
#include <QWidget>

class MachinePDF
{
public:
    static void exporter(QTableWidget *table, QWidget *parent);

private:
    MachinePDF() = delete;
};

#endif // MACHINE_PDF_H
