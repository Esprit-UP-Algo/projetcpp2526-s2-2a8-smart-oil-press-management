#include "client_historique.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QDate>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QLocale>
#include <QStandardPaths>
#include <QStringConverter>
#include <algorithm>

static QString achatsFichierChemin()
{
    const QString base = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString dossier = base + QStringLiteral("/ZitTech");
    QDir().mkpath(dossier);
    return dossier + QStringLiteral("/achats_tous_clients.txt");
}

namespace {

bool parseLigneAchatFichier(const QString &ligne, Achat *out)
{
    if (ligne.trimmed().isEmpty() || ligne.trimmed().startsWith(QLatin1Char('#')))
        return false;
    const QStringList p = ligne.split(QLatin1Char('|'));
    if (p.size() != 5)
        return false;
    bool okId = false;
    const int idCli = p.at(0).trimmed().toInt(&okId);
    if (!okId)
        return false;
    const QDate d = QDate::fromString(p.at(1).trimmed(), Qt::ISODate);
    if (!d.isValid())
        return false;
    bool okQ = false, okPu = false;
    const double q  = QLocale::c().toDouble(p.at(3).trimmed(), &okQ);
    const double pu = QLocale::c().toDouble(p.at(4).trimmed(), &okPu);
    if (!okQ || !okPu)
        return false;

    out->idClient     = idCli;
    out->produit      = p.at(2).trimmed();
    out->quantite     = q;
    out->prixUnitaire = pu;
    out->dateAchat    = d;
    return true;
}

QVector<Achat> lireAchatsDepuisFichier(int idClientFiltre)
{
    QVector<Achat> liste;
    const QString chemin = achatsFichierChemin();
    QFile f(chemin);
    if (!f.exists() || !f.open(QIODevice::ReadOnly | QIODevice::Text))
        return liste;

    QTextStream in(&f);
    in.setEncoding(QStringConverter::Utf8);
    int ligneFichier = 0;
    while (!in.atEnd()) {
        ++ligneFichier;
        const QString ligne = in.readLine();
        Achat a;
        if (!parseLigneAchatFichier(ligne, &a))
            continue;
        if (a.idClient != idClientFiltre)
            continue;
        a.id = ligneFichier;
        liste.append(a);
    }
    return liste;
}

QVector<Achat> lireTousAchatsDepuisFichier()
{
    QVector<Achat> liste;
    const QString chemin = achatsFichierChemin();
    QFile f(chemin);
    if (!f.exists() || !f.open(QIODevice::ReadOnly | QIODevice::Text))
        return liste;

    QTextStream in(&f);
    in.setEncoding(QStringConverter::Utf8);
    int ligneFichier = 0;
    while (!in.atEnd()) {
        ++ligneFichier;
        const QString ligne = in.readLine();
        Achat a;
        if (!parseLigneAchatFichier(ligne, &a))
            continue;
        a.id = 1000000 + ligneFichier;
        liste.append(a);
    }
    return liste;
}

bool ajouterAchatAuFichier(int idClient, const QDate &date, const QString &produit,
                           double quantite, double prixUnitaire, QString *erreurMsg)
{
    const QString chemin = achatsFichierChemin();
    QFile f(chemin);
    const bool nouveau = !f.exists();
    if (!f.open(QIODevice::Append | QIODevice::Text)) {
        if (erreurMsg)
            *erreurMsg = QStringLiteral("Impossible d'écrire le fichier :\n%1\n%2")
                             .arg(chemin, f.errorString());
        return false;
    }

    QTextStream out(&f);
    out.setEncoding(QStringConverter::Utf8);
    if (nouveau) {
        out << QStringLiteral(
            "# ZitTech — carnet des achats (tous les clients). Modifiable avec le Bloc-notes.\n"
            "# Une ligne = un achat. Format : ID_CLIENT|AAAA-MM-JJ|PRODUIT|QUANTITE|PRIX_UNITAIRE\n");
    }
    const QString prod = QString(produit).replace(QLatin1Char('|'), QLatin1Char(' '))
                             .replace(QLatin1Char('\n'), QLatin1Char(' '))
                             .replace(QLatin1Char('\r'), QLatin1Char(' '));
    out << idClient << QLatin1Char('|') << date.toString(Qt::ISODate) << QLatin1Char('|') << prod
        << QLatin1Char('|') << QString::number(quantite, 'f', 2) << QLatin1Char('|')
        << QString::number(prixUnitaire, 'f', 2) << QLatin1Char('\n');
    f.close();
    qDebug() << "[ClientHistorique] Achat enregistré dans" << chemin;
    return true;
}

} // namespace

QString ClientHistorique::campagneOleicoleAnnee(const QDate &date)
{
    if (!date.isValid())
        return QString();
    const int y = date.year();
    const int m = date.month();
    if (m >= 7)
        return QString::number(y) + QLatin1Char('/') + QString::number(y + 1);
    return QString::number(y - 1) + QLatin1Char('/') + QString::number(y);
}

QString ClientHistorique::campagneOleicoleAnneeSuivante(const QString &campagneCourante)
{
    const QStringList p = campagneCourante.split(QLatin1Char('/'));
    if (p.size() != 2)
        return QString();
    bool ok0 = false, ok1 = false;
    const int a = p.at(0).toInt(&ok0);
    const int b = p.at(1).toInt(&ok1);
    if (!ok0 || !ok1)
        return QString();
    return QString::number(a + 1) + QLatin1Char('/') + QString::number(b + 1);
}

QVector<Achat> ClientHistorique::chargerTousLesAchats()
{
    QVector<Achat> out;
    const QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery q(db);
        q.setForwardOnly(true);
        if (q.exec(QStringLiteral(
                "SELECT ID, ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT "
                "FROM ZIT.ACHATS ORDER BY DATE_ACHAT ASC"))) {
            while (q.next()) {
                Achat a;
                a.id           = q.value(0).toInt();
                a.idClient     = q.value(1).toInt();
                a.produit      = q.value(2).toString();
                a.quantite     = q.value(3).toDouble();
                a.prixUnitaire = q.value(4).toDouble();
                a.dateAchat    = q.value(5).toDate();
                out.append(a);
            }
        }
    }
    const QVector<Achat> depuisFichier = lireTousAchatsDepuisFichier();
    for (const Achat &a : depuisFichier)
        out.append(a);

    std::sort(out.begin(), out.end(), [](const Achat &x, const Achat &y) {
        if (x.dateAchat != y.dateAchat)
            return x.dateAchat < y.dateAchat;
        return x.id < y.id;
    });
    return out;
}

QString ClientHistorique::saisonDepuisDate(const QDate &date)
{
    if (!date.isValid())
        return QStringLiteral("Non définie");

    const int mois  = date.month();
    const int annee = date.year();
    const auto yy   = [](int y) {
        return QStringLiteral("%1").arg(y % 100, 2, 10, QLatin1Char('0'));
    };

    if (mois == 12)
        return QStringLiteral("Hiver %1/%2").arg(yy(annee), yy(annee + 1));
    if (mois == 1 || mois == 2)
        return QStringLiteral("Hiver %1/%2").arg(yy(annee - 1), yy(annee));
    return QStringLiteral("Hors saison");
}

bool ClientHistorique::insererAchat(int idClient, const QDate &date, const QString &produit,
                                    double quantite, double prixUnitaire, QString *erreurMsg)
{
    const QString p = produit.trimmed();
    if (p.isEmpty()) {
        if (erreurMsg)
            *erreurMsg = QStringLiteral("Indiquez le produit.");
        return false;
    }
    if (quantite <= 0.0) {
        if (erreurMsg)
            *erreurMsg = QStringLiteral("La quantité doit être supérieure à 0.");
        return false;
    }
    if (prixUnitaire < 0.0) {
        if (erreurMsg)
            *erreurMsg = QStringLiteral("Le prix unitaire ne peut pas être négatif.");
        return false;
    }
    if (!date.isValid()) {
        if (erreurMsg)
            *erreurMsg = QStringLiteral("Date d'achat invalide.");
        return false;
    }

    QString errOracle;
    const QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.setForwardOnly(true);
        const bool prepared = query.prepare(
            QStringLiteral(
                "INSERT INTO ZIT.ACHATS (ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT) "
                "VALUES (?, ?, ?, ?, TO_DATE(?, 'YYYY-MM-DD'))"
                ));
        if (prepared) {
            query.addBindValue(idClient);
            query.addBindValue(p);
            query.addBindValue(quantite);
            query.addBindValue(prixUnitaire);
            query.addBindValue(date.toString(Qt::ISODate));
        }
        if (prepared && query.exec())
            return true;
        errOracle = query.lastError().text();
        qDebug() << "[ClientHistorique::insererAchat Oracle]" << errOracle;

        QSqlQuery q2(db);
        q2.setForwardOnly(true);
        const QString sql = QStringLiteral(
                                "INSERT INTO ZIT.ACHATS (ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT) "
                                "VALUES (%1, '%2', %3, %4, TO_DATE('%5', 'YYYY-MM-DD'))"
                                )
                                .arg(idClient)
                                .arg(QString(p).replace(QLatin1Char('\''), QStringLiteral("''")))
                                .arg(QString::number(quantite, 'f', 4))
                                .arg(QString::number(prixUnitaire, 'f', 4))
                                .arg(date.toString(Qt::ISODate));
        if (q2.exec(sql))
            return true;
        errOracle = q2.lastError().text();
        qDebug() << "[ClientHistorique::insererAchat Oracle SQL direct]" << errOracle;
    }

    // Table Oracle absente ou autre erreur : carnet externe (tous les clients)
    if (ajouterAchatAuFichier(idClient, date, p, quantite, prixUnitaire, erreurMsg))
        return true;

    if (erreurMsg && !errOracle.isEmpty())
        *erreurMsg = QStringLiteral("%1\n\n(Oracle : %2)").arg(*erreurMsg, errOracle);
    return false;
}

QVector<Achat> ClientHistorique::chargerAchatsClient(int idClient)
{
    QVector<Achat> achats;
    const QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.setForwardOnly(true);
        query.prepare(
            QStringLiteral(
                "SELECT ID, ID_CLIENT, PRODUIT, QUANTITE, PRIX_UNITAIRE, DATE_ACHAT "
                "FROM ZIT.ACHATS WHERE ID_CLIENT = :id ORDER BY DATE_ACHAT DESC"
                ));
        query.bindValue(QStringLiteral(":id"), idClient);
        if (query.exec()) {
            while (query.next()) {
                Achat achat;
                achat.id           = query.value(0).toInt();
                achat.idClient     = query.value(1).toInt();
                achat.produit      = query.value(2).toString();
                achat.quantite     = query.value(3).toDouble();
                achat.prixUnitaire = query.value(4).toDouble();
                achat.dateAchat    = query.value(5).toDate();
                achats.append(achat);
            }
        } else {
            qDebug() << "[ClientHistorique::chargerAchatsClient Oracle]" << query.lastError().text();
        }
    }

    const QVector<Achat> depuisFichier = lireAchatsDepuisFichier(idClient);
    for (const Achat &a : depuisFichier)
        achats.append(a);

    std::sort(achats.begin(), achats.end(), [](const Achat &x, const Achat &y) {
        if (x.dateAchat != y.dateAchat)
            return x.dateAchat > y.dateAchat;
        return x.id > y.id;
    });
    return achats;
}

QString ClientHistorique::cheminFichierAchatsExternes()
{
    return achatsFichierChemin();
}

ClientHistorique::ClientHistorique(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Historique initialisé";
}

ClientHistorique::~ClientHistorique()
{
    qDebug() << "Service Historique détruit";
}

void ClientHistorique::afficherHistoriqueAchats(int idClient, QTableWidget *table)
{
    table->setRowCount(0);

    QVector<Achat> achats = chargerAchatsClient(idClient);

    table->clearSpans();
    table->setColumnCount(6);
    const QStringList headers = {
        QStringLiteral("Date"),
        QStringLiteral("Produit"),
        QStringLiteral("Quantité (kg)"),
        QStringLiteral("Prix unitaire (DT)"),
        QStringLiteral("Total (DT)"),
        QStringLiteral("Saison")
    };
    table->setHorizontalHeaderLabels(headers);

    int row = 0;
    double totalGlobal = 0;

    for (const Achat &achat : achats) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(achat.dateAchat.toString(QStringLiteral("dd/MM/yyyy"))));
        table->setItem(row, 1, new QTableWidgetItem(achat.produit));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(achat.quantite, 'f', 2)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(achat.prixUnitaire, 'f', 2)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(achat.getTotal(), 'f', 2)));
        table->setItem(row, 5, new QTableWidgetItem(saisonDepuisDate(achat.dateAchat)));

        for (int col = 0; col < 6; col++) {
            if (table->item(row, col)) {
                table->item(row, col)->setTextAlignment(Qt::AlignCenter);
                table->item(row, col)->setFlags(table->item(row, col)->flags() & ~Qt::ItemIsEditable);
            }
        }

        totalGlobal += achat.getTotal();
        row++;
    }

    // Ligne de total
    if (row > 0) {
        table->insertRow(row);
        QFont boldFont;
        boldFont.setBold(true);

        QTableWidgetItem *totalItem = new QTableWidgetItem(QStringLiteral("TOTAL"));
        totalItem->setTextAlignment(Qt::AlignCenter);
        totalItem->setFont(boldFont);
        totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 0, totalItem);
        table->setSpan(row, 0, 1, 4);

        QTableWidgetItem *totalValueItem = new QTableWidgetItem(QString::number(totalGlobal, 'f', 2));
        totalValueItem->setTextAlignment(Qt::AlignCenter);
        totalValueItem->setFont(boldFont);
        totalValueItem->setFlags(totalValueItem->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 4, totalValueItem);

        QTableWidgetItem *dashSaison = new QTableWidgetItem(QStringLiteral("—"));
        dashSaison->setTextAlignment(Qt::AlignCenter);
        dashSaison->setFont(boldFont);
        dashSaison->setFlags(dashSaison->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, 5, dashSaison);
    }

    table->resizeColumnsToContents();
}

void ClientHistorique::afficherResumeAchats(int idClient, QTextEdit *textEdit)
{
    QString resume = getHistoriqueTexte(idClient);
    textEdit->setPlainText(resume);
}

QString ClientHistorique::getHistoriqueTexte(int idClient)
{
    QString texte;

    // Récupérer les infos du client
    QSqlQuery clientQuery;
    clientQuery.prepare("SELECT NOM, PRENOM, TYPE_CLIENT FROM ZIT.CLIENT WHERE ID_CLIENT = :id");
    clientQuery.bindValue(":id", idClient);

    QString nomClient = "Client inconnu";
    QString typeClient = "";

    if (clientQuery.exec() && clientQuery.next()) {
        nomClient = clientQuery.value(0).toString() + " " + clientQuery.value(1).toString();
        typeClient = clientQuery.value(2).toString();
    }

    QVector<Achat> achats = chargerAchatsClient(idClient);

    texte += "========================================\n";
    texte += "      HISTORIQUE D'ACHAT\n";
    texte += "========================================\n\n";
    texte += "Client : " + nomClient + "\n";
    texte += "Type   : " + typeClient + "\n";
    texte += "ID     : " + QString::number(idClient) + "\n";
    texte += "----------------------------------------\n\n";

    if (achats.isEmpty()) {
        texte += "Aucun achat enregistré pour ce client.\n";
    } else {
        texte += "Liste des achats :\n\n";
        texte += QString("%1 | %2 | %3 | %4 | %5 | %6\n")
                     .arg(QStringLiteral("Date"), 12)
                     .arg(QStringLiteral("Produit"), 18)
                     .arg(QStringLiteral("Quantité"), 10)
                     .arg(QStringLiteral("Prix u."), 10)
                     .arg(QStringLiteral("Total"), 10)
                     .arg(QStringLiteral("Saison"), 12);
        texte += QString("%1 | %2 | %3 | %4 | %5 | %6\n")
                     .arg(QStringLiteral("----------"), 12)
                     .arg(QStringLiteral("----------------"), 18)
                     .arg(QStringLiteral("----------"), 10)
                     .arg(QStringLiteral("----------"), 10)
                     .arg(QStringLiteral("----------"), 10)
                     .arg(QStringLiteral("------------"), 12);

        double totalGlobal = 0;
        for (const Achat &achat : achats) {
            texte += QString("%1 | %2 | %3 | %4 | %5 | %6\n")
            .arg(achat.dateAchat.toString(QStringLiteral("dd/MM/yyyy")), 12)
                .arg(achat.produit.left(16), 18)
                .arg(QString::number(achat.quantite, 'f', 2), 10)
                .arg(QString::number(achat.prixUnitaire, 'f', 2), 10)
                .arg(QString::number(achat.getTotal(), 'f', 2), 10)
                .arg(saisonDepuisDate(achat.dateAchat), 12);
            totalGlobal += achat.getTotal();
        }

        texte += "\n----------------------------------------\n";
        texte += QString("TOTAL GÉNÉRAL : %1 DT\n").arg(totalGlobal, 0, 'f', 2);
        texte += QString("NOMBRE D'ACHATS : %1\n").arg(achats.size());

        double moyenne = totalGlobal / achats.size();
        texte += QString("PANIER MOYEN : %1 DT\n").arg(moyenne, 0, 'f', 2);
    }

    texte += "\n========================================\n";
    texte += "Généré le : " + QDate::currentDate().toString("dd/MM/yyyy") + "\n";
    texte += "========================================\n";

    return texte;
}
