#include "pdfproduction.h"

PdfProduction::PdfProduction() {}

// ─────────────────────────────────────────────────────────────────────────────
// chargerDonnees — fetch all production rows from DB
// ─────────────────────────────────────────────────────────────────────────────
bool PdfProduction::chargerDonnees()
{
    lignes.clear();

    QSqlQuery query;
    query.prepare(
        "SELECT ID_PROD, DATE_PROD, QUANTITE_OLIVE, QUANTITE_HUILE, RENDEMENT "
        "FROM ZIT.PRODUCTION "
        "ORDER BY ID_PROD ASC"
        );

    if (!query.exec()) {
        qDebug() << "Erreur chargement données PDF :" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        LigneProduction l;
        l.id            = query.value("ID_PROD").toInt();
        l.date          = query.value("DATE_PROD").toDate();
        l.quantiteOlive = query.value("QUANTITE_OLIVE").toDouble();
        l.quantiteHuile = query.value("QUANTITE_HUILE").toDouble();
        l.rendement     = query.value("RENDEMENT").toDouble();
        lignes.append(l);
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// exporterPDF — entry point
// ─────────────────────────────────────────────────────────────────────────────
void PdfProduction::exporterPDF(QWidget *parent)
{
    if (!chargerDonnees()) {
        QMessageBox::critical(parent, "Erreur",
                              "Impossible de charger les données de production.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        parent,
        "Enregistrer le rapport PDF",
        "rapport_production_" + QDate::currentDate().toString("yyyy-MM-dd") + ".pdf",
        "Fichiers PDF (*.pdf)"
        );
    if (filePath.isEmpty()) return;
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive))
        filePath += ".pdf";

    // ── Même configuration que ExporterPartenaire ────────────────────────────
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(parent, "Erreur",
                              "Impossible d'initialiser l'export PDF.\n"
                              "Vérifiez les droits d'écriture du dossier.");
        return;
    }

    dessinerPDF(painter, printer);
    painter.end();

    QMessageBox::information(parent, "Export réussi",
                             QString("Le fichier PDF a été créé avec succès :\n%1").arg(filePath));
}

// ─────────────────────────────────────────────────────────────────────────────
// dessinerPDF — même approche que ExporterPartenaire :
//   dimensions via painter.viewport(), tailles en % de page, polices fixes
// ─────────────────────────────────────────────────────────────────────────────
void PdfProduction::dessinerPDF(QPainter &painter, QPrinter &printer)
{
    // ── Dimensions via viewport (Qt5 + Qt6 compatible) ───────────────────────
    const int pageW   = painter.viewport().width();
    const int pageH   = painter.viewport().height();
    const int marginX = int(pageW * 0.03);
    const int marginTop = int(pageH * 0.12);

    // ── Palette couleurs ZitTech ─────────────────────────────────────────────
    const QColor couleurEntete     (45,  74,  31);   // vert foncé
    const QColor couleurSousEntete (93, 115,  44);   // vert moyen
    const QColor couleurOr         (255, 215,  0);   // or
    const QColor couleurLigneImpaire(240, 248, 235); // vert très clair
    const QColor couleurTexteEntete(255, 255, 255);  // blanc
    const QColor couleurTexte      (30,  30,  30);   // quasi-noir

    const int tableW  = pageW - 2 * marginX;

    // ══════════════════════════════════════════════════════════════════════════
    // 1. BANDEAU TITRE
    // ══════════════════════════════════════════════════════════════════════════
    const int bandeauH = int(pageH * 0.09);
    painter.setPen(Qt::NoPen);
    painter.setBrush(couleurEntete);
    painter.drawRect(0, 0, pageW, bandeauH);

    // Titre principal
    painter.setFont(QFont("Arial", 22, QFont::Bold));
    painter.setPen(couleurOr);
    painter.drawText(
        QRect(marginX, 0, tableW, int(bandeauH * 0.65)),
        Qt::AlignVCenter | Qt::AlignLeft,
        "ZitTech \u2014 Rapport de Production"
        );

    // Date d'export
    painter.setFont(QFont("Arial", 11));
    painter.setPen(Qt::white);
    painter.drawText(
        QRect(marginX, int(bandeauH * 0.60), tableW, int(bandeauH * 0.40)),
        Qt::AlignVCenter | Qt::AlignLeft,
        "Généré le : " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm")
        );

    // ══════════════════════════════════════════════════════════════════════════
    // 2. BARRE DE STATISTIQUES
    // ══════════════════════════════════════════════════════════════════════════
    double totalOlives = 0, totalHuile = 0, rendSum = 0;
    for (const auto &l : lignes) {
        totalOlives += l.quantiteOlive;
        totalHuile  += l.quantiteHuile;
        rendSum     += l.rendement;
    }
    double rendMoy = lignes.isEmpty() ? 0.0 : rendSum / lignes.size();

    const int statsY = bandeauH + int(pageH * 0.01);
    const int statsH = int(pageH * 0.08);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(240, 248, 235));
    painter.drawRect(marginX, statsY, tableW, statsH);

    // Bordure basse de la barre stats
    painter.setPen(QPen(couleurSousEntete, 2));
    painter.drawLine(marginX, statsY + statsH, marginX + tableW, statsY + statsH);

    QStringList statLabels = {
        QString("Productions : %1").arg(lignes.size()),
        QString("Total olives : %1 kg").arg(QString::number(totalOlives, 'f', 2)),
        QString("Total huile : %1 L").arg(QString::number(totalHuile, 'f', 2)),
        QString("Rendement moyen : %1 %").arg(QString::number(rendMoy, 'f', 2))
    };

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(couleurEntete);
    int statColW = tableW / statLabels.size();
    for (int i = 0; i < statLabels.size(); ++i) {
        painter.drawText(
            QRect(marginX + i * statColW, statsY, statColW, statsH),
            Qt::AlignCenter,
            statLabels[i]
            );
    }

    // ══════════════════════════════════════════════════════════════════════════
    // 3. EN-TÊTE DU TABLEAU
    // ══════════════════════════════════════════════════════════════════════════
    const int nbCols  = 5;
    const int headerH = int(pageH * 0.065);
    const int rowH    = int(pageH * 0.055);

    int colW[5] = {
        int(tableW * 0.08),   // ID
        int(tableW * 0.17),   // Date
        int(tableW * 0.25),   // Olives (kg)
        int(tableW * 0.25),   // Huile (L)
        int(tableW * 0.25)    // Rendement (%)
    };
    const QString headers[5] = {
        "ID", "Date", "Olives (kg)", "Huile (L)", "Rendement (%)"
    };

    int y = marginTop;

    // Lambda : dessiner l'en-tête
    auto dessinerEntete = [&]() {
        int x = marginX;
        for (int col = 0; col < nbCols; ++col) {
            painter.fillRect(x, y, colW[col], headerH, couleurSousEntete);
            painter.setPen(QPen(Qt::white, 2));
            painter.drawRect(x, y, colW[col], headerH);
            painter.setFont(QFont("Arial", 13, QFont::Bold));
            painter.setPen(couleurTexteEntete);
            painter.drawText(
                QRect(x + 8, y, colW[col] - 10, headerH),
                Qt::AlignVCenter | Qt::AlignLeft,
                headers[col]
                );
            x += colW[col];
        }
    };

    dessinerEntete();
    y += headerH;

    // ══════════════════════════════════════════════════════════════════════════
    // 4. LIGNES DE DONNÉES
    // ══════════════════════════════════════════════════════════════════════════
    int rowIndex = 0;
    int pageCount = 1;

    for (const auto &ligne : lignes) {

        // Pagination automatique
        if (y + rowH > pageH - int(pageH * 0.06)) {
            printer.newPage();
            y = marginTop;
            ++pageCount;
            dessinerEntete();
            y += headerH;
        }

        // Fond alterné
        QColor bg = (rowIndex % 2 == 0) ? Qt::white : couleurLigneImpaire;
        int x = marginX;
        for (int col = 0; col < nbCols; ++col) {
            painter.fillRect(x, y, colW[col], rowH, bg);
            painter.setPen(QPen(QColor(180, 200, 170), 1));
            painter.drawRect(x, y, colW[col], rowH);
            x += colW[col];
        }

        // Texte des cellules
        const QString cellules[5] = {
            QString::number(ligne.id),
            ligne.date.toString("dd/MM/yyyy"),
            QString::number(ligne.quantiteOlive, 'f', 2) + " kg",
            QString::number(ligne.quantiteHuile, 'f', 2) + " L",
            QString::number(ligne.rendement,     'f', 2) + " %"
        };

        x = marginX;
        painter.setFont(QFont("Arial", 11));
        painter.setPen(couleurTexte);
        for (int col = 0; col < nbCols; ++col) {
            painter.drawText(
                QRect(x + 8, y, colW[col] - 12, rowH),
                Qt::AlignVCenter | Qt::AlignLeft,
                cellules[col]
                );
            x += colW[col];
        }

        y += rowH;
        ++rowIndex;
    }

    // ══════════════════════════════════════════════════════════════════════════
    // 5. PIED DE PAGE
    // ══════════════════════════════════════════════════════════════════════════
    // Total lignes
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(couleurEntete);
    painter.drawText(
        QRect(marginX, y + int(pageH * 0.015), tableW / 2, int(pageH * 0.04)),
        Qt::AlignLeft,
        QString("Total : %1 production(s)").arg(lignes.size())
        );

    // Numéro de page + copyright (aligné à droite)
    painter.setFont(QFont("Arial", 11));
    painter.setPen(couleurSousEntete);
    painter.drawText(
        QRect(marginX, y + int(pageH * 0.015), tableW, int(pageH * 0.04)),
        Qt::AlignRight,
        QString("ZitTech \u00A9 %1  \u2014  Page %2")
            .arg(QDate::currentDate().year())
            .arg(pageCount)
        );
}
