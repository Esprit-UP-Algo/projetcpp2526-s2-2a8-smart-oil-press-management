#include "exportpdf.h"

// ── Couleurs ZitTech ──────────────────────────────────────────
static const QColor C_VERT_FONCE ("#2d4a1f");
static const QColor C_VERT_MID   ("#4a7c2f");
static const QColor C_VERT_CLAIR ("#eef4e8");
static const QColor C_JAUNE      ("#ffd700");
static const QColor C_BLANC      (Qt::white);
static const QColor C_TEXTE      ("#1a1a1a");
static const QColor C_BORD       ("#c0c0c0");
static const QColor C_GRIS_PIED  ("#555555");

ExportPDF::ExportPDF(QObject *parent) : QObject(parent) {}

// ─────────────────────────────────────────────────────────────
void ExportPDF::exporterStockPDF(QTableWidget *table, QWidget *parentWidget)
{
    if (!table || table->rowCount() == 0) {
        QMessageBox::warning(parentWidget, "Export PDF",
                             "Le tableau est vide. Aucun PDF à générer.");
        return;
    }

    QString path = QFileDialog::getSaveFileName(
        parentWidget,
        "Enregistrer le rapport PDF",
        QDir::homePath() + "/Rapport_Stock_" +
            QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm") + ".pdf",
        "Fichiers PDF (*.pdf)");

    if (path.isEmpty()) return;

    if (!path.endsWith(".pdf", Qt::CaseInsensitive))
        path += ".pdf";

    // ── FIX 1: HighResolution remplace ScreenResolution (compatible Qt5+Qt6) ──
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(parentWidget, "Erreur PDF",
                              "Impossible de créer le fichier PDF.\n"
                              "Vérifiez les droits d'écriture du dossier.");
        return;
    }

    // ── FIX 2: Utiliser painter.viewport() à la place de printer.pageRect()
    //           viewport() est identique sur Qt5 et Qt6, pas déprécié ──────────
    const int W = painter.viewport().width();
    const int H = painter.viewport().height();

    int currentY = 0;

    dessinerEntete  (painter, W, currentY);
    dessinerTableau (painter, W, H, currentY, table);
    dessinerPiedPage(painter, W, H);

    painter.end();

    QMessageBox::information(parentWidget, "Export réussi",
                             "✅ Rapport exporté avec succès !\n\n" + path);
}

// ─────────────────────────────────────────────────────────────
//  EN-TÊTE
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerEntete(QPainter &p, int W, int &currentY)
{
    int bandH = 90;

    // Bande verte foncée
    p.setPen(Qt::NoPen);
    p.setBrush(C_VERT_FONCE);
    p.drawRect(0, 0, W, bandH);

    // Titre blanc
    p.setPen(C_BLANC);
    p.setFont(QFont("Arial", 22, QFont::Bold));
    p.drawText(QRect(0, 8, W, 42), Qt::AlignCenter, "ZitTech Management");

    // Sous-titre jaune
    p.setPen(C_JAUNE);
    p.setFont(QFont("Arial", 13));
    p.drawText(QRect(0, 52, W, 30), Qt::AlignCenter, "Rapport de Gestion des Stocks");

    // Barre jaune séparatrice
    p.setPen(Qt::NoPen);
    p.setBrush(C_JAUNE);
    p.drawRect(0, bandH, W, 5);

    currentY = bandH + 5;

    // Date alignée à droite
    p.setPen(C_GRIS_PIED);
    p.setFont(QFont("Arial", 8));
    QString dateStr = "Généré le : " +
                      QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm");
    p.drawText(QRect(0, currentY + 4, W - 10, 20),
               Qt::AlignRight | Qt::AlignVCenter, dateStr);

    currentY += 28;
}

// ─────────────────────────────────────────────────────────────
//  TABLEAU
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerTableau(QPainter &p, int W, int H,
                                int &currentY, QTableWidget *table)
{
    const int nbCols = table->columnCount();
    const int nbRows = table->rowCount();
    const int marge  = 15;
    const int tableW = W - 2 * marge;
    const int rowH   = 28;
    const int headH  = 36;

    // Proportions des 5 colonnes : ID / Type / Quantité / Seuil / Origine
    QList<double> ratios = {0.09, 0.19, 0.16, 0.16, 0.40};

    // Sécurité : s'adapter si le tableau a un nombre différent de colonnes
    while (ratios.size() < nbCols) ratios << (1.0 / nbCols);

    QList<int> colW;
    for (int c = 0; c < nbCols; c++)
        colW << (int)(tableW * ratios[c]);

    // ── En-tête du tableau ─────────────────────────────────────
    p.setFont(QFont("Arial", 9, QFont::Bold));
    int x = marge;
    for (int c = 0; c < nbCols; c++) {
        QRect cell(x, currentY, colW[c], headH);

        p.setPen(Qt::NoPen);
        p.setBrush(C_VERT_MID);
        p.drawRect(cell);

        if (c < nbCols - 1) {
            p.setPen(QPen(C_BLANC, 1));
            p.drawLine(x + colW[c], currentY, x + colW[c], currentY + headH);
        }

        p.setPen(C_BLANC);
        QString hdr = table->horizontalHeaderItem(c)
                          ? table->horizontalHeaderItem(c)->text() : "";
        p.drawText(cell.adjusted(4, 0, -4, 0),
                   Qt::AlignCenter | Qt::TextWordWrap, hdr);
        x += colW[c];
    }
    currentY += headH;

    // ── Lignes de données ──────────────────────────────────────
    p.setFont(QFont("Arial", 9));

    for (int r = 0; r < nbRows; r++) {
        // Pagination : arrêter si on déborde
        if (currentY + rowH > H - 50) break;

        // Ignorer les lignes cachées (résultat de recherche/filtre)
        if (table->isRowHidden(r)) continue;

        QColor fond = (r % 2 == 0) ? C_VERT_CLAIR : C_BLANC;
        x = marge;

        for (int c = 0; c < nbCols; c++) {
            QRect cell(x, currentY, colW[c], rowH);

            p.setPen(Qt::NoPen);
            p.setBrush(fond);
            p.drawRect(cell);

            p.setPen(QPen(C_BORD, 1));
            p.drawLine(x, currentY + rowH, x + colW[c], currentY + rowH);
            if (c < nbCols - 1)
                p.drawLine(x + colW[c], currentY, x + colW[c], currentY + rowH);

            p.setPen(C_TEXTE);
            QString txt = table->item(r, c) ? table->item(r, c)->text() : "";

            // Colonnes numériques alignées à droite
            Qt::Alignment al = (c == 2 || c == 3)
                                   ? Qt::AlignRight  | Qt::AlignVCenter
                                   : Qt::AlignLeft   | Qt::AlignVCenter;
            p.drawText(cell.adjusted(6, 0, -6, 0), al, txt);
            x += colW[c];
        }
        currentY += rowH;
    }

    // Ligne de fermeture
    p.setPen(QPen(C_VERT_MID, 2));
    p.drawLine(marge, currentY, W - marge, currentY);

    // Total articles
    p.setPen(C_VERT_FONCE);
    p.setFont(QFont("Arial", 8, QFont::Bold));
    p.drawText(QRect(marge, currentY + 6, tableW, 20),
               Qt::AlignLeft | Qt::AlignVCenter,
               QString("Total : %1 article(s) en stock").arg(nbRows));
}

// ─────────────────────────────────────────────────────────────
//  PIED DE PAGE
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerPiedPage(QPainter &p, int W, int H)
{
    int bas = H - 30;

    // Ligne jaune
    p.setPen(QPen(C_JAUNE, 2));
    p.drawLine(15, bas, W - 15, bas);

    // Gauche : copyright
    p.setPen(C_VERT_FONCE);
    p.setFont(QFont("Arial", 8, QFont::Bold));
    p.drawText(QRect(15, bas + 5, W / 2, 20),
               Qt::AlignLeft | Qt::AlignVCenter,
               "ZitTech Management © " +
                   QString::number(QDate::currentDate().year()));

    // Droite : mention confidentielle
    p.setPen(C_GRIS_PIED);
    p.setFont(QFont("Arial", 7));
    p.drawText(QRect(W / 2, bas + 5, W / 2 - 15, 20),
               Qt::AlignRight | Qt::AlignVCenter,
               "Document confidentiel — Usage interne uniquement");
}
