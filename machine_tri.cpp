#include "machine_tri.h"
#include "machine_search.h"

#include <algorithm>
#include <QDate>

namespace {
    struct MachineRow {
        QString id;
        QString type;
        QString etat;
        QString dateMaintenance;
        QString duree;
    };

    static double parseNumber(const QString &text)
    {
        QString clean = text;
        clean.remove('%');
        clean.remove('h');
        clean = clean.trimmed();
        bool ok = false;
        double value = clean.toDouble(&ok);
        return ok ? value : 0.0;
    }

    static QList<MachineRow> readTable(QTableWidget *table)
    {
        QList<MachineRow> rows;
        int count = table->rowCount();
        for (int i = 0; i < count; ++i) {
            MachineRow row;
            row.id              = table->item(i, 0) ? table->item(i, 0)->text() : QString();
            row.type            = table->item(i, 1) ? table->item(i, 1)->text() : QString();
            row.etat            = table->item(i, 2) ? table->item(i, 2)->text() : QString();
            row.dateMaintenance = table->item(i, 3) ? table->item(i, 3)->text() : QString();
            row.duree           = table->item(i, 4) ? table->item(i, 4)->text() : QString();
            rows.append(row);
        }
        return rows;
    }

    static void writeTable(QTableWidget *table, const QList<MachineRow> &rows)
    {
        table->setRowCount(0);
        for (const MachineRow &row : rows) {
            int newRow = table->rowCount();
            table->insertRow(newRow);
            table->setItem(newRow, 0, new QTableWidgetItem(row.id));
            table->setItem(newRow, 1, new QTableWidgetItem(row.type));
            table->setItem(newRow, 2, new QTableWidgetItem(row.etat));
            table->setItem(newRow, 3, new QTableWidgetItem(row.dateMaintenance));
            table->setItem(newRow, 4, new QTableWidgetItem(row.duree));
        }
        table->resizeColumnsToContents();
    }
}

void MachineTri::trierParId(QTableWidget *table, bool ascendant)
{
    QList<MachineRow> rows = readTable(table);
    std::sort(rows.begin(), rows.end(), [ascendant](const MachineRow &a, const MachineRow &b) {
        int ai = a.id.toInt();
        int bi = b.id.toInt();
        return ascendant ? ai < bi : ai > bi;
    });
    writeTable(table, rows);
}

void MachineTri::trierParType(QTableWidget *table, bool ascendant)
{
    QList<MachineRow> rows = readTable(table);
    std::sort(rows.begin(), rows.end(), [ascendant](const MachineRow &a, const MachineRow &b) {
        if (ascendant)
            return a.type.toLower() < b.type.toLower();
        return a.type.toLower() > b.type.toLower();
    });
    writeTable(table, rows);
}

void MachineTri::trierParEtat(QTableWidget *table, bool ascendant)
{
    QList<MachineRow> rows = readTable(table);
    std::sort(rows.begin(), rows.end(), [ascendant](const MachineRow &a, const MachineRow &b) {
        if (ascendant)
            return a.etat.toLower() < b.etat.toLower();
        return a.etat.toLower() > b.etat.toLower();
    });
    writeTable(table, rows);
}

void MachineTri::trierParDateMaintenance(QTableWidget *table, bool ascendant)
{
    QList<MachineRow> rows = readTable(table);
    std::sort(rows.begin(), rows.end(), [ascendant](const MachineRow &a, const MachineRow &b) {
        QDate da = QDate::fromString(a.dateMaintenance, "dd/MM/yyyy");
        QDate db = QDate::fromString(b.dateMaintenance, "dd/MM/yyyy");
        if (!da.isValid()) da = QDate();
        if (!db.isValid()) db = QDate();
        return ascendant ? da < db : da > db;
    });
    writeTable(table, rows);
}

void MachineTri::trierParDuree(QTableWidget *table, bool ascendant)
{
    QList<MachineRow> rows = readTable(table);
    std::sort(rows.begin(), rows.end(), [ascendant](const MachineRow &a, const MachineRow &b) {
        double da = parseNumber(a.duree);
        double db = parseNumber(b.duree);
        return ascendant ? da < db : da > db;
    });
    writeTable(table, rows);
}

void MachineTri::reinitialiser(QTableWidget *table)
{
    MachineSearch::chargerTout(table);
}
