#include "statistiques.h"

Statistiques::Statistiques(const QSqlDatabase &db, QObject *parent)
    : QObject(parent), db(db)
{
}

// ── Requêtes SQL ─────────────────────────────────────────────

int Statistiques::getTotalArticles()
{
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK") && q.next())
        return q.value(0).toInt();
    return 0;
}

int Statistiques::getArticlesEnAlerte()
{
    // Stocks dont la quantité est <= au seuil d'alerte
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK WHERE QUANTITE <= SEUIL_ALERTE") && q.next())
        return q.value(0).toInt();
    return 0;
}

double Statistiques::getTotalQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT NVL(SUM(QUANTITE), 0) FROM ZIT.STOCK") && q.next())
        return q.value(0).toDouble();
    return 0.0;
}

double Statistiques::getMoyenneQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT NVL(AVG(QUANTITE), 0) FROM ZIT.STOCK") && q.next())
        return q.value(0).toDouble();
    return 0.0;
}

QString Statistiques::getStockMaxQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT TYPE_STOCK, QUANTITE, ORIGINE FROM ZIT.STOCK "
               "WHERE QUANTITE = (SELECT MAX(QUANTITE) FROM ZIT.STOCK) "
               "AND ROWNUM = 1") && q.next()) {
        return QString("%1 (%2 kg) — %3")
            .arg(q.value(0).toString())
            .arg(q.value(1).toDouble(), 0, 'f', 2)
            .arg(q.value(2).toString());
    }
    return "—";
}

QString Statistiques::getStockMinQuantite()
{
    QSqlQuery q(db);
    if (q.exec("SELECT TYPE_STOCK, QUANTITE, ORIGINE FROM ZIT.STOCK "
               "WHERE QUANTITE = (SELECT MIN(QUANTITE) FROM ZIT.STOCK) "
               "AND ROWNUM = 1") && q.next()) {
        return QString("%1 (%2 kg) — %3")
            .arg(q.value(0).toString())
            .arg(q.value(1).toDouble(), 0, 'f', 2)
            .arg(q.value(2).toString());
    }
    return "—";
}

int Statistiques::getNbOriginesDistinctes()
{
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(DISTINCT ORIGINE) FROM ZIT.STOCK") && q.next())
        return q.value(0).toInt();
    return 0;
}

int Statistiques::getStocksCritiques()
{
    // Stocks dont la quantité est STRICTEMENT inférieure au seuil
    QSqlQuery q(db);
    if (q.exec("SELECT COUNT(*) FROM ZIT.STOCK WHERE QUANTITE < SEUIL_ALERTE") && q.next())
        return q.value(0).toInt();
    return 0;
}

// ── Méthode principale ────────────────────────────────────────

void Statistiques::chargerStats(QLabel *valueTotalStocks,
                                QLabel *valueAlertStocks,
                                QLabel *valueTotalQuantite,
                                QLabel *valueMoyenneQuantite,
                                QLabel *valueStockMax,
                                QLabel *valueStockMin,
                                QLabel *valueNbOrigines,
                                QLabel *valueStockCritique)
{
    int    total      = getTotalArticles();
    int    alertes    = getArticlesEnAlerte();
    double totalQte   = getTotalQuantite();
    double moyenneQte = getMoyenneQuantite();
    QString stockMax  = getStockMaxQuantite();
    QString stockMin  = getStockMinQuantite();
    int    nbOrigines = getNbOriginesDistinctes();
    int    critiques  = getStocksCritiques();

    // Mettre à jour les labels si non null
    if (valueTotalStocks)
        valueTotalStocks->setText(QString::number(total));

    if (valueAlertStocks) {
        valueAlertStocks->setText(QString::number(alertes));
        // Colorer en rouge si des alertes existent
        if (alertes > 0)
            valueAlertStocks->setStyleSheet(
                "color: #ff4444; font: 16pt 'Segoe UI'; font-weight: bold;");
        else
            valueAlertStocks->setStyleSheet(
                "color: #44cc44; font: 16pt 'Segoe UI'; font-weight: bold;");
    }

    if (valueTotalQuantite)
        valueTotalQuantite->setText(
            QString::number(totalQte, 'f', 2) + " kg");

    if (valueMoyenneQuantite)
        valueMoyenneQuantite->setText(
            QString::number(moyenneQte, 'f', 2) + " kg");

    if (valueStockMax)
        valueStockMax->setText(stockMax);

    if (valueStockMin)
        valueStockMin->setText(stockMin);

    if (valueNbOrigines)
        valueNbOrigines->setText(QString::number(nbOrigines));

    if (valueStockCritique) {
        valueStockCritique->setText(QString::number(critiques));
        if (critiques > 0)
            valueStockCritique->setStyleSheet(
                "color: #ff2222; font: 16pt 'Segoe UI'; font-weight: bold;");
        else
            valueStockCritique->setStyleSheet(
                "color: #44cc44; font: 16pt 'Segoe UI'; font-weight: bold;");
    }

    qDebug() << "Stats chargées — Total:" << total
             << "Alertes:" << alertes
             << "TotalQte:" << totalQte
             << "Critiques:" << critiques;
}
