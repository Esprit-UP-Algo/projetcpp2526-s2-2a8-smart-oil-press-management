#include "machine_search.h"

#include <QTableWidgetItem>
#include <QSqlQueryModel>

static const QStringList HEADERS = {
    "ID", "Type", "État", "Date Maintenance", "Durée (h)"
};

static void initTable(QTableWidget *table)
{
    table->setRowCount(0);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(HEADERS);
}

void MachineSearch::remplirLigne(QTableWidget *table, int row,
                                 const QString &id,
                                 const QString &type,
                                 const QString &etat,
                                 const QString &dateMaintenance,
                                 const QString &duree)
{
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(id));
    table->setItem(row, 1, new QTableWidgetItem(type));
    table->setItem(row, 2, new QTableWidgetItem(etat));
    table->setItem(row, 3, new QTableWidgetItem(dateMaintenance));
    table->setItem(row, 4, new QTableWidgetItem(duree));
}

void MachineSearch::chargerTout(QTableWidget *table)
{
    initTable(table);

    Machine m;
    QSqlQueryModel *model = m.afficher();

    for (int row = 0; row < model->rowCount(); row++) {
        remplirLigne(table, row,
                     model->data(model->index(row, 0)).toString(),
                     model->data(model->index(row, 1)).toString(),
                     model->data(model->index(row, 2)).toString(),
                     model->data(model->index(row, 3)).toString(),
                     model->data(model->index(row, 4)).toString());
    }

    table->resizeColumnsToContents();
    delete model;
}

void MachineSearch::filtrer(QTableWidget *table, const QString &terme)
{
    if (terme.trimmed().isEmpty()) {
        chargerTout(table);
        return;
    }

    initTable(table);

    Machine m;
    QSqlQueryModel *model = m.afficher();

    for (int i = 0; i < model->rowCount(); i++) {
        QString id    = model->data(model->index(i, 0)).toString();
        QString type  = model->data(model->index(i, 1)).toString();
        QString etat  = model->data(model->index(i, 2)).toString();
        QString date  = model->data(model->index(i, 3)).toString();
        QString duree = model->data(model->index(i, 4)).toString();

        bool match = id.contains(terme,   Qt::CaseInsensitive) ||
                     type.contains(terme, Qt::CaseInsensitive) ||
                     etat.contains(terme, Qt::CaseInsensitive);

        if (match) {
            int newRow = table->rowCount();
            remplirLigne(table, newRow, id, type, etat, date, duree);
        }
    }

    delete model;
}
