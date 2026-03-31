#include "employe_search.h"
#include <QTableWidgetItem>
#include <QSqlQueryModel>

// ── Colonnes du tableau ───────────────────────────────────────
static const QStringList HEADERS = {
    "ID", "Nom", "Prénom", "Poste", "Salaire", "Date Embauche"
};

// ─────────────────────────────────────────────────────────────
//  Initialise le tableau (colonnes + headers)
// ─────────────────────────────────────────────────────────────
static void initTable(QTableWidget *table)
{
    table->setRowCount(0);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels(HEADERS);
}

// ─────────────────────────────────────────────────────────────
//  Remplit une ligne du tableau
// ─────────────────────────────────────────────────────────────
void EmployeSearch::remplirLigne(QTableWidget *table, int row,
                                 const QString &id,  const QString &nom,
                                 const QString &prenom, const QString &poste,
                                 const QString &salaire, const QString &date)
{
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(id));
    table->setItem(row, 1, new QTableWidgetItem(nom));
    table->setItem(row, 2, new QTableWidgetItem(prenom));
    table->setItem(row, 3, new QTableWidgetItem(poste));
    table->setItem(row, 4, new QTableWidgetItem(salaire));
    table->setItem(row, 5, new QTableWidgetItem(date));
}

// ─────────────────────────────────────────────────────────────
//  Charge TOUS les employés depuis la BDD
// ─────────────────────────────────────────────────────────────
void EmployeSearch::chargerTout(QTableWidget *table)
{
    initTable(table);

    Employe e;
    QSqlQueryModel *model = e.afficher();

    for (int row = 0; row < model->rowCount(); row++) {
        remplirLigne(table, row,
                     model->data(model->index(row, 0)).toString(),
                     model->data(model->index(row, 1)).toString(),
                     model->data(model->index(row, 2)).toString(),
                     model->data(model->index(row, 3)).toString(),
                     model->data(model->index(row, 4)).toString(),
                     model->data(model->index(row, 5)).toString());
    }

    table->resizeColumnsToContents();
    delete model;
}

// ─────────────────────────────────────────────────────────────
//  Filtre les employés selon le terme (ID / Nom / Prénom / Poste)
// ─────────────────────────────────────────────────────────────
void EmployeSearch::filtrer(QTableWidget *table, const QString &terme)
{
    if (terme.trimmed().isEmpty()) {
        chargerTout(table);
        return;
    }

    initTable(table);

    Employe e;
    QSqlQueryModel *model = e.afficher();

    for (int i = 0; i < model->rowCount(); i++) {
        QString id     = model->data(model->index(i, 0)).toString();
        QString nom    = model->data(model->index(i, 1)).toString();
        QString prenom = model->data(model->index(i, 2)).toString();
        QString poste  = model->data(model->index(i, 3)).toString();
        QString sal    = model->data(model->index(i, 4)).toString();
        QString date   = model->data(model->index(i, 5)).toString();

        bool match = id.contains(terme,     Qt::CaseInsensitive) ||
                     nom.contains(terme,    Qt::CaseInsensitive) ||
                     prenom.contains(terme, Qt::CaseInsensitive) ||
                     poste.contains(terme,  Qt::CaseInsensitive);

        if (match) {
            int newRow = table->rowCount();
            remplirLigne(table, newRow, id, nom, prenom, poste, sal, date);
        }
    }

    delete model;
}
