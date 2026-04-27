#include "rechproduction.h"
#include <QRegularExpression>
#include <QMessageBox>

RechProduction::RechProduction() {}

// ─────────────────────────────────────────────────────────────────────────────
// remplirTable — shared helper: run query and fill the QTableWidget
// ─────────────────────────────────────────────────────────────────────────────
void RechProduction::remplirTable(QSqlQuery &query, QTableWidget *table)
{
    table->setRowCount(0);

    if (!query.exec()) {
        qDebug() << "RechProduction::remplirTable error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        table->setItem(row, 0,
                       new QTableWidgetItem(query.value("ID_PROD").toString()));

        QDate date = query.value("DATE_PROD").toDate();
        table->setItem(row, 1,
                       new QTableWidgetItem(date.toString("dd/MM/yyyy")));

        table->setItem(row, 2,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_OLIVE").toDouble(), 'f', 2) + " kg"));

        table->setItem(row, 3,
                       new QTableWidgetItem(
                           QString::number(query.value("QUANTITE_HUILE").toDouble(), 'f', 2) + " L"));

        table->setItem(row, 4,
                       new QTableWidgetItem(
                           QString::number(query.value("RENDEMENT").toDouble(), 'f', 2) + " %"));

        for (int col = 0; col < 5; col++) {
            if (table->item(row, col))
                table->item(row, col)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        row++;
    }
    table->resizeColumnsToContents();
}

// ─────────────────────────────────────────────────────────────────────────────
// rechercher — parse the user input and dispatch to the right method
// ─────────────────────────────────────────────────────────────────────────────
void RechProduction::rechercher(const QString &terme, QTableWidget *table)
{
    QString t = terme.trimmed();
    if (t.isEmpty()) return;

    // ── Pattern: number followed by "kg" or "KG" (case-insensitive) ──────────
    // Examples: "150 kg", "150.5KG", "200kg"
    QRegularExpression reOlive(R"(^(\d+(?:\.\d+)?)\s*[kK][gG]$)");
    QRegularExpressionMatch mOlive = reOlive.match(t);
    if (mOlive.hasMatch()) {
        double valeur = mOlive.captured(1).toDouble();
        rechercherParOlive(valeur, table);
        return;
    }

    // ── Pattern: number followed by "l" or "L" ────────────────────────────────
    // Examples: "50 L", "50.5l", "30L"
    QRegularExpression reHuile(R"(^(\d+(?:\.\d+)?)\s*[lL]$)");
    QRegularExpressionMatch mHuile = reHuile.match(t);
    if (mHuile.hasMatch()) {
        double valeur = mHuile.captured(1).toDouble();
        rechercherParHuile(valeur, table);
        return;
    }

    // ── Pattern: date MM/DD/YYYY ──────────────────────────────────────────────
    // Examples: "04/06/2025", "12/31/2024"
    QRegularExpression reDate(R"(^(\d{2})/(\d{2})/(\d{4})$)");
    QRegularExpressionMatch mDate = reDate.match(t);
    if (mDate.hasMatch()) {
        int month = mDate.captured(1).toInt();
        int day   = mDate.captured(2).toInt();
        int year  = mDate.captured(3).toInt();
        QDate date(year, month, day);
        if (date.isValid()) {
            rechercherParDate(date, table);
            return;
        }
    }

    // ── No pattern matched ────────────────────────────────────────────────────
    QMessageBox::information(nullptr, "Format non reconnu",
                             "Format de recherche invalide.\n\n"
                             "Exemples valides :\n"
                             "  • 150 kg   ou   150.5 KG   → recherche par quantité d'olives\n"
                             "  • 50 L     ou   50.5 l     → recherche par quantité d'huile\n"
                             "  • 04/06/2025               → recherche par date (MM/JJ/AAAA)");
}

// ─────────────────────────────────────────────────────────────────────────────
// rechercherParOlive
// ─────────────────────────────────────────────────────────────────────────────
void RechProduction::rechercherParOlive(double valeur, QTableWidget *table)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "WHERE QUANTITE_OLIVE = :val "
        "ORDER BY ID_PROD ASC");
    query.bindValue(":val", valeur);
    remplirTable(query, table);
}

// ─────────────────────────────────────────────────────────────────────────────
// rechercherParHuile
// ─────────────────────────────────────────────────────────────────────────────
void RechProduction::rechercherParHuile(double valeur, QTableWidget *table)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "WHERE QUANTITE_HUILE = :val "
        "ORDER BY ID_PROD ASC");
    query.bindValue(":val", valeur);
    remplirTable(query, table);
}

// ─────────────────────────────────────────────────────────────────────────────
// rechercherParDate — input is MM/DD/YYYY, stored as DATE in Oracle
// ─────────────────────────────────────────────────────────────────────────────
void RechProduction::rechercherParDate(const QDate &date, QTableWidget *table)
{
    QSqlQuery query;
    query.prepare(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "WHERE TRUNC(DATE_PROD) = :dat "
        "ORDER BY ID_PROD ASC");
    query.bindValue(":dat", date);
    remplirTable(query, table);
}
