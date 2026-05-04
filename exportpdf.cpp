#include "exportpdf.h"
#include <QTextDocument>
#include <QTextStream>

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

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);

    QString html;
    QTextStream out(&html);

    out << "<html><head><meta charset='utf-8'/>"
           "<style>"
           "body{font-family:'Segoe UI',Arial,sans-serif;color:#1a1a1a;font-size:11pt;}"
           ".head{background:#2d4a1f;color:#fff;padding:14px 16px;border-radius:6px;}"
           ".title{font-size:18pt;font-weight:700;margin:0;}"
           ".subtitle{font-size:10pt;color:#ffd700;margin:4px 0 0 0;}"
           ".date{font-size:9pt;color:#5a5a5a;text-align:right;margin:8px 0 12px 0;}"
           "table{width:100%;border-collapse:collapse;table-layout:fixed;}"
           "th{background:#4a7c2f;color:white;font-size:10pt;padding:8px;border:1px solid #d0d0d0;}"
           "td{font-size:10pt;padding:7px;border:1px solid #d0d0d0;word-wrap:break-word;}"
           "tr:nth-child(even) td{background:#eef4e8;}"
           ".num{text-align:right;}"
           ".foot{margin-top:10px;font-size:9pt;color:#2d4a1f;font-weight:600;}"
           "</style></head><body>";

    out << "<div class='head'>"
           "<p class='title'>ZitTech Management</p>"
           "<p class='subtitle'>Rapport de Gestion des Stocks</p>"
           "</div>";
    out << "<p class='date'>Généré le : "
        << QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm")
        << "</p>";

    out << "<table><thead><tr>";
    for (int c = 0; c < table->columnCount(); ++c) {
        const QString header = table->horizontalHeaderItem(c)
        ? table->horizontalHeaderItem(c)->text().toHtmlEscaped()
        : QString();
        out << "<th>" << header << "</th>";
    }
    out << "</tr></thead><tbody>";

    int printedRows = 0;
    for (int r = 0; r < table->rowCount(); ++r) {
        if (table->isRowHidden(r))
            continue;
        out << "<tr>";
        for (int c = 0; c < table->columnCount(); ++c) {
            const QString txt = table->item(r, c)
            ? table->item(r, c)->text().toHtmlEscaped()
            : QString();
            const bool numericCol = (c == 2 || c == 3);
            out << "<td class='" << (numericCol ? "num" : "") << "'>" << txt << "</td>";
        }
        out << "</tr>";
        ++printedRows;
    }
    out << "</tbody></table>";

    out << "<p class='foot'>Total : " << printedRows << " article(s) en stock</p>";
    out << "</body></html>";

    QTextDocument doc;
    doc.setDocumentMargin(18.0);
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(parentWidget, "Export réussi",
                             "✅ Rapport exporté avec succès !\n\n" + path);
}

// ─────────────────────────────────────────────────────────────
//  EN-TÊTE
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerEntete(QPainter &p, int W, int &currentY)
{
    const int bandH = 52;

    // Bande verte foncée
    p.setPen(Qt::NoPen);
    p.setBrush(C_VERT_FONCE);
    p.drawRect(0, 0, W, bandH);

    // Titre blanc
    p.setPen(C_BLANC);
    p.setFont(QFont("Arial", 14, QFont::Bold));
    p.drawText(QRect(0, 2, W, 26), Qt::AlignCenter, "ZitTech Management");

    // Sous-titre jaune
    p.setPen(C_JAUNE);
    p.setFont(QFont("Arial", 9));
    p.drawText(QRect(0, 26, W, 20), Qt::AlignCenter, "Rapport de Gestion des Stocks");

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
    p.drawText(QRect(0, currentY + 2, W - 6, 14),
               Qt::AlignRight | Qt::AlignVCenter, dateStr);

    currentY += 16;
}

// ─────────────────────────────────────────────────────────────
//  TABLEAU
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerTableau(QPainter &p, int W, int H,
                                int &currentY, QTableWidget *table, QPrinter &printer)
{
    const int nbCols = table->columnCount();
    const int nbRowsTotal = table->rowCount();
    const int marge  = 15;
    const int tableW = W - 2 * marge;
    const int rowH   = 18;
    const int headH  = 22;

    // Proportions des 5 colonnes : ID / Type / Quantité / Seuil / Origine
    QList<double> ratios = {0.09, 0.19, 0.16, 0.16, 0.40};

    // Sécurité : s'adapter si le tableau a un nombre différent de colonnes
    while (ratios.size() < nbCols) ratios << (1.0 / nbCols);

    QList<int> colW;
    int usedW = 0;
    for (int c = 0; c < nbCols; c++) {
        const int w = (c == nbCols - 1) ? (tableW - usedW) : static_cast<int>(tableW * ratios[c]);
        colW << w;
        usedW += w;
    }

    auto drawTableHeader = [&]() {
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
            const QString hdr = table->horizontalHeaderItem(c)
                                    ? table->horizontalHeaderItem(c)->text()
                                    : QString();
            p.drawText(cell.adjusted(4, 0, -4, 0), Qt::AlignCenter | Qt::TextWordWrap, hdr);
            x += colW[c];
        }
        currentY += headH;
    };

    int pageNumber = 1;
    int printedRows = 0;
    const int footerReserve = 28;

    drawTableHeader();

    // ── Lignes de données ──────────────────────────────────────
    p.setFont(QFont("Arial", 9));

    for (int r = 0; r < nbRowsTotal; r++) {
        // Ignorer les lignes cachées (résultat de recherche/filtre)
        if (table->isRowHidden(r)) continue;

        // Pagination multi-pages
        if (currentY + rowH > H - footerReserve) {
            dessinerPiedPage(p, W, H, pageNumber++);
            printer.newPage();
            currentY = 0;
            dessinerEntete(p, W, currentY);
            drawTableHeader();
        }

        QColor fond = (r % 2 == 0) ? C_VERT_CLAIR : C_BLANC;
        int x = marge;

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
        printedRows++;
    }

    // Ligne de fermeture
    p.setPen(QPen(C_VERT_MID, 2));
    p.drawLine(marge, currentY, W - marge, currentY);

    // Total articles
    p.setPen(C_VERT_FONCE);
    p.setFont(QFont("Arial", 8, QFont::Bold));
    p.drawText(QRect(marge, currentY + 6, tableW, 20),
               Qt::AlignLeft | Qt::AlignVCenter,
               QString("Total : %1 article(s) en stock").arg(printedRows));

    dessinerPiedPage(p, W, H, pageNumber);
}

// ─────────────────────────────────────────────────────────────
//  PIED DE PAGE
// ─────────────────────────────────────────────────────────────
void ExportPDF::dessinerPiedPage(QPainter &p, int W, int H, int pageNumber)
{
    int bas = H - 20;

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
               QString("Page %1  |  Document confidentiel — Usage interne uniquement").arg(pageNumber));
}
