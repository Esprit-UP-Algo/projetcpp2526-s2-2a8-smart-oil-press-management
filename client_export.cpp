#include "client_export.h"
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

ClientExport::ClientExport(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Export initialisé";
}

ClientExport::~ClientExport()
{
    qDebug() << "Service Export détruit";
}

void ClientExport::afficherDialogExport(QTableWidget *table, QWidget *parent)
{
    QMessageBox msgBox(parent);
    msgBox.setWindowTitle("Export des Clients");
    msgBox.setText("Choisissez le format d'export :");

    QPushButton *btnPDF   = msgBox.addButton("PDF",          QMessageBox::AcceptRole);
    QPushButton *btnExcel = msgBox.addButton("Excel (CSV)",  QMessageBox::AcceptRole);
    msgBox.addButton("Annuler", QMessageBox::RejectRole);
    msgBox.exec();

    if (msgBox.clickedButton() == btnPDF) {
        QString chemin = QFileDialog::getSaveFileName(parent, "Exporter en PDF", "", "*.pdf");
        if (!chemin.isEmpty()) exporterEnPDF(table, chemin);
    } else if (msgBox.clickedButton() == btnExcel) {
        QString chemin = QFileDialog::getSaveFileName(parent, "Exporter en Excel", "", "*.csv");
        if (!chemin.isEmpty()) exporterEnExcel(table, chemin);
    }
}

void ClientExport::exporterPDF(QTableWidget *table, const QString &cheminFichier)
{
    if (!table || table->rowCount() == 0) {
        QMessageBox::warning(nullptr, "Export PDF",
                             "Le tableau est vide. Aucun PDF à générer.");
        return;
    }

    // Appeler la fonction d'export existante
    exporterEnPDF(table, cheminFichier);
}

void ClientExport::exporterExcel(QTableWidget *table, const QString &cheminFichier)
{
    exporterEnExcel(table, cheminFichier);
}

// ─────────────────────────────────────────────────────────────────────────────
//  EXPORT PDF  — coordonnées en Points (1 pt = 1/72 pouce)
//  A4 Paysage  = 842 × 595 pt
// ─────────────────────────────────────────────────────────────────────────────
void ClientExport::exporterEnPDF(QTableWidget *table, const QString &chemin)
{
    // ── 1. Configuration de l'imprimante ─────────────────────────────────────
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(chemin);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Landscape);

    // Marges nulles côté QPrinter : on gère les marges dans le dessin
    printer.setPageMargins(QMarginsF(0, 0, 0, 0), QPageLayout::Point);

    // ── 2. Dimensions de la page en POINTS ───────────────────────────────────
    // pageRect(Point) renvoie les dimensions réelles en points typographiques,
    // indépendamment de la résolution physique du périphérique.
    QRectF pageRectPt = printer.pageRect(QPrinter::Point);

    // Facteur de conversion : points → pixels device
    // Exemple : 300 DPI → 1 pt = 300/72 ≈ 4.17 px
    qreal dpi   = printer.resolution();          // résolution physique (ex. 1200)
    qreal scale = dpi / 72.0;                    // pts → device pixels

    // Dimensions de la page en pixels device (ce que QPainter utilise)
    qreal pageW = pageRectPt.width()  * scale;
    qreal pageH = pageRectPt.height() * scale;

    // ── 3. Paramètres de mise en page (en POINTS, puis convertis) ────────────
    // Travailler en points rend les valeurs lisibles (comme en CSS/Word).
    const qreal marginPt     = 20.0;   // marge gauche/droite : 20 pt ≈ 7 mm
    const qreal headerHPt    = 36.0;   // hauteur bandeau titre : 36 pt ≈ 12.7 mm
    const qreal rowHPt       = 16.0;   // hauteur d'une ligne de données : 16 pt
    const qreal headerRowHPt = 20.0;   // hauteur ligne d'en-tête du tableau
    const qreal footerHPt    = 18.0;   // hauteur pied de page

    // Largeur disponible pour le tableau (en points)
    qreal tableWidthPt = pageRectPt.width() - 2 * marginPt;

    // Largeurs des colonnes en PROPORTIONS (somme = 1.0)
    // Ordre : ID | Nom | Prénom | Email | Téléphone | Type | Avis
    const int   nbCols = 7;
    const qreal colRatios[nbCols] = { 0.05, 0.12, 0.12, 0.20, 0.11, 0.10, 0.30 };
    qreal colWidthsPt[nbCols];
    for (int i = 0; i < nbCols; i++)
        colWidthsPt[i] = tableWidthPt * colRatios[i];

    // ── 4. Fontes (taille en points) ─────────────────────────────────────────
    QFont fontTitle("Arial", 14, QFont::Bold);
    QFont fontDate ("Arial",  8);
    QFont fontHead ("Arial",  9, QFont::Bold);
    QFont fontData ("Arial",  8);
    QFont fontTotal("Arial",  9, QFont::Bold);
    QFont fontFoot ("Arial",  7);

    // ── 5. Couleurs ──────────────────────────────────────────────────────────
    const QColor cBannerDark (27,  94,  32);   // vert foncé titre
    const QColor cHeaderRow  (46, 125,  50);   // vert moyen en-tête tableau
    const QColor cRowAlt     (240, 248, 240);  // vert très clair lignes paires
    const QColor cFooterBg   (232, 245, 233);  // vert pâle pied de page
    const QColor cGreen      (46, 125,  50);
    const QColor cBorder     (180, 210, 180);  // bordure légère

    // ── 6. Début du dessin ───────────────────────────────────────────────────
    QPainter p;
    if (!p.begin(&printer)) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'initialiser le PDF.");
        return;
    }

    // Toutes les coordonnées passées à QPainter sont en pixels device.
    // On définit un lambda de conversion pour garder le code lisible.
    auto pt = [&](qreal pts) -> qreal { return pts * scale; };

    int  pageNum   = 1;
    qreal y        = pt(marginPt);   // curseur vertical courant

    QStringList headers = {"ID", "Nom", "Prénom", "Email", "Téléphone", "Type", "Avis"};

    // ── Fonction locale : dessiner l'en-tête de page ─────────────────────────
    auto drawPageHeader = [&]() {
        // Bandeau titre
        p.fillRect(QRectF(0, 0, pageW, pt(headerHPt)),
                   QBrush(cBannerDark));

        p.setPen(Qt::white);
        p.setFont(fontTitle);
        p.drawText(QRectF(pt(marginPt), 0, pageW * 0.6, pt(headerHPt)),
                   Qt::AlignLeft | Qt::AlignVCenter,
                   "ZitTech – Liste des Clients");

        p.setFont(fontDate);
        p.drawText(QRectF(0, 0, pageW - pt(marginPt), pt(headerHPt)),
                   Qt::AlignRight | Qt::AlignVCenter,
                   QString("Généré le : %1   |   Page %2")
                       .arg(QDate::currentDate().toString("dd/MM/yyyy"))
                       .arg(pageNum));

        y = pt(headerHPt) + pt(6); // espace après le bandeau

        // ── En-tête du tableau ────────────────────────────────────────────────
        p.fillRect(QRectF(pt(marginPt), y,
                          pt(tableWidthPt), pt(headerRowHPt)),
                   QBrush(cHeaderRow));

        p.setPen(Qt::white);
        p.setFont(fontHead);

        qreal x = pt(marginPt);
        for (int i = 0; i < nbCols; i++) {
            qreal cw = pt(colWidthsPt[i]);
            // Bordure verticale entre colonnes
            if (i > 0) {
                p.setPen(QPen(Qt::white, 0.5));
                p.drawLine(QPointF(x, y), QPointF(x, y + pt(headerRowHPt)));
            }
            p.setPen(Qt::white);
            p.drawText(QRectF(x + pt(3), y, cw - pt(6), pt(headerRowHPt)),
                       Qt::AlignLeft | Qt::AlignVCenter,
                       headers[i]);
            x += cw;
        }
        y += pt(headerRowHPt);
    };

    // ── Fonction locale : nouvelle page ──────────────────────────────────────
    auto newPage = [&]() {
        printer.newPage();
        pageNum++;
        y = 0;
        drawPageHeader();
    };

    // ── Dessin de la première page ────────────────────────────────────────────
    drawPageHeader();

    // ── 7. Lignes de données ─────────────────────────────────────────────────
    p.setFont(fontData);

    for (int row = 0; row < table->rowCount(); row++) {
        // Saut de page si nécessaire (on réserve de la place pour le pied)
        if (y + pt(rowHPt) > pageH - pt(footerHPt + 4)) {
            newPage();
        }

        // Fond alterné
        QColor bgColor = (row % 2 == 0) ? Qt::white : cRowAlt;
        p.fillRect(QRectF(pt(marginPt), y, pt(tableWidthPt), pt(rowHPt)), bgColor);

        // Bordure horizontale inférieure de la ligne
        p.setPen(QPen(cBorder, 0.5));
        p.drawLine(QPointF(pt(marginPt),                    y + pt(rowHPt)),
                   QPointF(pt(marginPt) + pt(tableWidthPt), y + pt(rowHPt)));

        // Cellules
        qreal x = pt(marginPt);
        p.setPen(Qt::black);
        for (int col = 0; col < nbCols; col++) {
            qreal cw = pt(colWidthsPt[col]);

            // Bordure verticale
            if (col > 0) {
                p.setPen(QPen(cBorder, 0.5));
                p.drawLine(QPointF(x, y), QPointF(x, y + pt(rowHPt)));
                p.setPen(Qt::black);
            }

            QString text = (table->item(row, col))
                               ? table->item(row, col)->text()
                               : "";

            // Élision pour les textes trop longs (colonne Avis)
            QFontMetricsF fm(fontData);
            qreal maxW = cw - pt(6);
            text = fm.elidedText(text, Qt::ElideRight,
                                 static_cast<int>(maxW));

            p.setFont(fontData);
            p.drawText(QRectF(x + pt(3), y, cw - pt(6), pt(rowHPt)),
                       Qt::AlignLeft | Qt::AlignVCenter,
                       text);
            x += cw;
        }

        y += pt(rowHPt);
    }

    // ── 8. Ligne de total ────────────────────────────────────────────────────
    if (table->rowCount() > 0) {
        if (y + pt(rowHPt + 4) > pageH - pt(footerHPt + 4))
            newPage();

        p.fillRect(QRectF(pt(marginPt), y + pt(2),
                          pt(tableWidthPt), pt(rowHPt)),
                   QBrush(QColor(200, 230, 201)));

        p.setFont(fontTotal);
        p.setPen(cGreen);
        p.drawText(QRectF(pt(marginPt + 3), y + pt(2),
                          pt(tableWidthPt), pt(rowHPt)),
                   Qt::AlignLeft | Qt::AlignVCenter,
                   QString("Total : %1 client(s)").arg(table->rowCount()));
        y += pt(rowHPt + 4);
    }

    // ── 9. Pied de page (toutes les pages) ───────────────────────────────────
    // On dessine le pied de page sur la dernière page (les autres pages l'ont
    // déjà dans leur bandeau via le numéro de page affiché en haut à droite).
    p.fillRect(QRectF(0, pageH - pt(footerHPt),
                      pageW, pt(footerHPt)),
               QBrush(cFooterBg));

    p.setPen(cGreen);
    p.setFont(fontFoot);
    p.drawText(QRectF(pt(marginPt), pageH - pt(footerHPt),
                      pageW - 2 * pt(marginPt), pt(footerHPt)),
               Qt::AlignLeft | Qt::AlignVCenter,
               "ZitTech – Gestion de Production d'Huile d'Olive");

    p.drawText(QRectF(pt(marginPt), pageH - pt(footerHPt),
                      pageW - 2 * pt(marginPt), pt(footerHPt)),
               Qt::AlignRight | Qt::AlignVCenter,
               QString("Page %1").arg(pageNum));

    p.end();

    QMessageBox::information(nullptr, "Export réussi",
                             QString("%1 client(s) exporté(s) avec succès !")
                                 .arg(table->rowCount()));
}

// ─────────────────────────────────────────────────────────────────────────────
//  EXPORT EXCEL (CSV) — inchangé, fonctionnait déjà
// ─────────────────────────────────────────────────────────────────────────────
void ClientExport::exporterEnExcel(QTableWidget *table, const QString &chemin)
{
    QFile file(chemin);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible de créer le fichier");
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);

    // En-tête
    for (int col = 0; col < table->columnCount(); col++) {
        stream << "\"" << table->horizontalHeaderItem(col)->text() << "\"";
        if (col < table->columnCount() - 1) stream << ";";
    }
    stream << "\n";

    // Données
    for (int row = 0; row < table->rowCount(); row++) {
        for (int col = 0; col < table->columnCount(); col++) {
            QString text = table->item(row, col) ? table->item(row, col)->text() : "";
            stream << "\"" << text.replace("\"", "\"\"") << "\"";
            if (col < table->columnCount() - 1) stream << ";";
        }
        stream << "\n";
    }

    file.close();
    QMessageBox::information(nullptr, "Succès",
                             "Fichier CSV exporté avec succès !\nOuvrez-le avec Excel.");
}
