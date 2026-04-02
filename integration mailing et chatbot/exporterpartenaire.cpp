#include "exporterpartenaire.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QRect>
#include <QDateTime>
#include <QDebug>

ExporterPartenaire::ExporterPartenaire() {}

// ─────────────────────────────────────────────────────────────────────────────
// Export PDF avec QPrinter + QPainter (compatible Qt5 et Qt6)
// ─────────────────────────────────────────────────────────────────────────────
bool ExporterPartenaire::exporterEnPDF(QWidget *parent, const QList<Partenaire> &liste)
{
    // ── 1. Demander le chemin de sauvegarde ───────────────────────────────────
    QString cheminFichier = QFileDialog::getSaveFileName(
        parent,
        "Exporter les partenaires en PDF",
        "partenaires_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (cheminFichier.isEmpty())
        return false;

    if (!cheminFichier.endsWith(".pdf", Qt::CaseInsensitive))
        cheminFichier += ".pdf";

    // ── 2. Configurer l'imprimante ────────────────────────────────────────────
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(cheminFichier);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);

    // ── 3. Démarrer le dessin ─────────────────────────────────────────────────
    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(parent, "Erreur",
                              "Impossible d'initialiser l'export PDF.\n"
                              "Verifiez les droits d'ecriture du dossier.");
        return false;
    }

    // ── 4. Dimensions via viewport du painter (Qt5 + Qt6 compatible) ─────────
    const int pageW    = painter.viewport().width();
    const int pageH    = painter.viewport().height();
    const int marginX  = int(pageW * 0.03);
    const int marginTop = int(pageH * 0.10);

    // ── 5. Couleurs du thème vert ZitTech ─────────────────────────────────────
    const QColor couleurEntete(45, 74, 31);
    const QColor couleurLigneImpaire(240, 248, 235);
    const QColor couleurTexteEntete(255, 255, 255);
    const QColor couleurTexte(30, 30, 30);

    // ── 6. Titre ──────────────────────────────────────────────────────────────
    painter.setFont(QFont("Arial", 26, QFont::Bold));
    painter.setPen(couleurEntete);
    painter.drawText(
        QRect(marginX, int(pageH * 0.02), pageW - 2 * marginX, int(pageH * 0.06)),
        Qt::AlignCenter,
        "Liste des Partenaires - ZitTech"
        );

    painter.setFont(QFont("Arial", 12));
    painter.setPen(Qt::gray);
    painter.drawText(
        QRect(marginX, int(pageH * 0.063), pageW - 2 * marginX, int(pageH * 0.03)),
        Qt::AlignRight,
        "Genere le : " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm")
        );

    // ── 7. Colonnes ───────────────────────────────────────────────────────────
    const int nbCols  = 5;
    const int tableW  = pageW - 2 * marginX;
    const int rowH    = int(pageH * 0.055);
    const int headerH = int(pageH * 0.065);

    int colW[5] = {
        int(tableW * 0.20),
        int(tableW * 0.27),
        int(tableW * 0.15),
        int(tableW * 0.18),
        int(tableW * 0.20)
    };
    const QString headers[5] = {"Nom", "Email", "Telephone", "Investissement", "Employe ID"};

    int y = marginTop;

    // ── Lambda : dessiner l'en-tête du tableau ────────────────────────────────
    auto dessinerEntete = [&]() {
        int x = marginX;
        for (int col = 0; col < nbCols; ++col) {
            painter.fillRect(x, y, colW[col], headerH, couleurEntete);
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

    // ── 8. Lignes de données ──────────────────────────────────────────────────
    int rowIndex = 0;
    for (const Partenaire &p : liste) {

        // Pagination automatique
        if (y + rowH > pageH - int(pageH * 0.06)) {
            printer.newPage();
            y = marginTop;
            dessinerEntete();
            y += headerH;
        }

        // Fond alterné
        QColor bgLigne = (rowIndex % 2 == 0) ? Qt::white : couleurLigneImpaire;
        int x = marginX;
        for (int col = 0; col < nbCols; ++col) {
            painter.fillRect(x, y, colW[col], rowH, bgLigne);
            painter.setPen(QPen(QColor(180, 200, 170), 1));
            painter.drawRect(x, y, colW[col], rowH);
            x += colW[col];
        }

        // Texte des cellules
        const QString cellules[5] = {
            p.getNom(),
            p.getEmail(),
            p.getTelephone(),
            p.getInvestissement(),
            p.getIdEmploye() > 0 ? QString::number(p.getIdEmploye()) : "-"
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

    // ── 9. Pied de page ───────────────────────────────────────────────────────
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(couleurEntete);
    painter.drawText(
        QRect(marginX, y + int(pageH * 0.015), tableW, int(pageH * 0.04)),
        Qt::AlignLeft,
        QString("Total : %1 partenaire(s)").arg(liste.size())
        );

    painter.end();

    QMessageBox::information(
        parent,
        "Export reussi",
        QString("Le fichier PDF a ete cree avec succes :\n%1").arg(cheminFichier)
        );
    return true;
}
