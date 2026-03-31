#include "machine_pdf.h"

#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QMessageBox>
#include <QDate>
#include <QDir>
#include <QPageSize>
#include <QPageLayout>

void MachinePDF::exporter(QTableWidget *table, QWidget *parent)
{
    QString defaultName = QDir::homePath() + "/Machines_"
                          + QDate::currentDate().toString("dd-MM-yyyy") + ".pdf";

    QString fileName = QFileDialog::getSaveFileName(
        parent,
        "Exporter la liste des machines en PDF",
        defaultName,
        "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageMargins(QMarginsF(0, 0, 0, 0), QPageLayout::Millimeter);

    QPainter p;
    if (!p.begin(&printer)) {
        QMessageBox::critical(parent, "Erreur", "Impossible de créer le PDF.");
        return;
    }

    const QColor C_DARK_GREEN(45,  74,  31);
    const QColor C_MID_GREEN (93,  115, 44);
    const QColor C_GOLD      (255, 215,  0);
    const QColor C_GOLD_DARK (200, 160,  0);
    const QColor C_WHITE     (255, 255, 255);
    const QColor C_ROW_EVEN  (248, 252, 240);
    const QColor C_ROW_ODD   (255, 255, 255);
    const QColor C_BORDER    (180, 200, 140);
    const QColor C_TEXT_DARK ( 30,  30,  30);
    const QColor C_TEXT_GRAY (120, 120, 120);

    QRectF pr = printer.pageRect(QPrinter::DevicePixel);
    int W = (int)pr.width();
    int H = (int)pr.height();

    int nbRows = table->rowCount();
    QStringList colHeaders = {
        "ID", "Type Machine", "État", "Date Maintenance", "Durée (h)"
    };
    int nCols = colHeaders.size();

    QVector<double> colRatio = {0.08, 0.34, 0.18, 0.22, 0.18};
    int margin = (int)(W * 0.04);
    int tableW = W - 2 * margin;
    QVector<int> colW;
    for (double r : colRatio) colW << (int)(tableW * r);

    auto font = [&](const QString &fam, int pt, bool bold = false) -> QFont {
        QFont f(fam, 0, bold ? QFont::Bold : QFont::Normal);
        f.setPixelSize((int)(pt * printer.resolution() / 72.0));
        return f;
    };

    QFont fTitle  = font("Arial", 20, true);
    QFont fSub    = font("Arial", 11);
    QFont fMeta   = font("Arial",  9);
    QFont fHead   = font("Arial", 10, true);
    QFont fCell   = font("Arial",  9);
    QFont fFooter = font("Arial",  8);

    int headerH  = (int)(H * 0.13);
    int goldBarH = (int)(H * 0.012);
    int colHeadH = (int)(H * 0.055);
    int rowH     = (int)(H * 0.052);
    int footerH  = (int)(H * 0.06);
    int tableTop = headerH + goldBarH + (int)(H * 0.02);
    int bodyH    = H - tableTop - footerH - (int)(H * 0.01);
    int maxRows  = (bodyH - colHeadH) / rowH;
    int totalPages = (nbRows == 0) ? 1 : (nbRows + maxRows - 1) / maxRows;

    auto drawHeader = [&](int page) {
        p.setPen(Qt::NoPen);
        p.setBrush(C_DARK_GREEN);
        p.drawRect(0, 0, W, headerH);

        p.setBrush(C_MID_GREEN);
        p.drawRect(0, 0, (int)(W * 0.006), headerH);

        int cSize = (int)(headerH * 0.55);
        int cX = margin, cY = (headerH - cSize) / 2;
        p.setBrush(C_GOLD);
        p.drawEllipse(cX, cY, cSize, cSize);
        p.setPen(C_DARK_GREEN);
        p.setFont(font("Arial", 14, true));
        p.drawText(QRect(cX, cY, cSize, cSize), Qt::AlignCenter, "Z");

        int tX = cX + cSize + (int)(W * 0.015);
        p.setPen(C_WHITE);
        p.setFont(fTitle);
        p.drawText(QRect(tX, (int)(headerH*0.08), W-tX-margin, (int)(headerH*0.50)),
                   Qt::AlignVCenter | Qt::AlignLeft, "ZitTech  —  Gestion de Production");

        p.setPen(C_GOLD);
        p.setFont(fSub);
        p.drawText(QRect(tX, (int)(headerH*0.55), W-tX-margin, (int)(headerH*0.38)),
                   Qt::AlignVCenter | Qt::AlignLeft, "Liste des Machines");

        int mW = (int)(W * 0.30);
        int mX = W - margin - mW;
        p.setPen(QColor(190, 220, 160));
        p.setFont(fMeta);
        p.drawText(QRect(mX,(int)(headerH*0.15),mW,(int)(headerH*0.38)),
                   Qt::AlignVCenter|Qt::AlignRight,
                   "Date d'export : " + QDate::currentDate().toString("dd/MM/yyyy"));
        p.drawText(QRect(mX,(int)(headerH*0.52),mW,(int)(headerH*0.38)),
                   Qt::AlignVCenter|Qt::AlignRight,
                   QString("Machines : %1   |   Page %2 / %3").arg(nbRows).arg(page).arg(totalPages));

        p.setBrush(C_GOLD); p.setPen(Qt::NoPen);
        p.drawRect(0, headerH, W, goldBarH);
    };

    auto drawFooter = [&](int page) {
        int fy = H - footerH;
        p.setPen(QPen(C_GOLD, 2));
        p.drawLine(margin, fy+6, W-margin, fy+6);

        p.setPen(C_MID_GREEN); p.setFont(fFooter);
        p.drawText(QRect(margin, fy+14, (int)(W*0.4), footerH-14),
                   Qt::AlignVCenter|Qt::AlignLeft, "ZitTech  •  Document confidentiel");
        p.drawText(QRect(W/2-150, fy+14, 300, footerH-14),
                   Qt::AlignVCenter|Qt::AlignCenter,
                   QString("Page %1 sur %2").arg(page).arg(totalPages));
        p.setPen(C_TEXT_GRAY);
        p.drawText(QRect(W-margin-(int)(W*0.35), fy+14, (int)(W*0.35), footerH-14),
                   Qt::AlignVCenter|Qt::AlignRight,
                   "Généré le " + QDate::currentDate().toString("dddd dd MMMM yyyy"));
    };

    auto drawColHeaders = [&](int y) {
        p.setPen(Qt::NoPen);
        p.setBrush(C_MID_GREEN);
        p.drawRect(margin, y, tableW, colHeadH);

        p.setPen(QPen(C_GOLD, 2));
        p.drawLine(margin, y, margin+tableW, y);

        int x = margin;
        for (int c = 0; c < nCols; c++) {
            if (c > 0) { p.setPen(QPen(C_GOLD_DARK,1)); p.drawLine(x,y+4,x,y+colHeadH-4); }
            p.setPen(C_WHITE); p.setFont(fHead);
            p.drawText(QRect(x+10, y, colW[c]-12, colHeadH),
                       Qt::AlignVCenter|Qt::AlignLeft, colHeaders[c]);
            x += colW[c];
        }

        p.setPen(QPen(C_GOLD, 2));
        p.drawLine(margin, y+colHeadH, margin+tableW, y+colHeadH);
    };

    auto drawRow = [&](int rowIdx, int y, bool even) {
        p.setPen(Qt::NoPen);
        p.setBrush(even ? C_ROW_EVEN : C_ROW_ODD);
        p.drawRect(margin, y, tableW, rowH);

        int x = margin;
        for (int c = 0; c < nCols && c < table->columnCount(); c++) {
            if (c > 0) { p.setPen(QPen(C_BORDER,1)); p.drawLine(x,y+4,x,y+rowH-4); }

            QTableWidgetItem *item = table->item(rowIdx, c);
            QString txt = item ? item->text() : "";
            if (c == 4 && !txt.isEmpty()) txt += " h";

            if (c == 2) { p.setPen(C_MID_GREEN); p.setFont(font("Arial",9,true)); }
            else        { p.setPen(C_TEXT_DARK); p.setFont(fCell); }

            p.drawText(QRect(x+10, y, colW[c]-14, rowH),
                       Qt::AlignVCenter|Qt::AlignLeft, txt);
            x += colW[c];
        }

        p.setPen(QPen(C_BORDER,1));
        p.drawLine(margin, y+rowH, margin+tableW, y+rowH);
    };

    auto drawBorder = [&](int yStart, int nDrawnRows) {
        int tH = colHeadH + nDrawnRows * rowH;
        p.setPen(QPen(C_MID_GREEN,2)); p.setBrush(Qt::NoBrush);
        p.drawRect(margin, yStart, tableW, tH);
    };

    int currentPage = 1;
    int rowIdx = 0;

    while (true) {
        drawHeader(currentPage);
        drawFooter(currentPage);

        int yHead = tableTop;
        drawColHeaders(yHead);

        int yRow = yHead + colHeadH;
        int rowsThisPage = 0;

        while (rowIdx < nbRows && rowsThisPage < maxRows) {
            drawRow(rowIdx, yRow, rowIdx % 2 == 0);
            yRow += rowH; rowIdx++; rowsThisPage++;
        }

        for (int r = rowsThisPage; r < maxRows; r++) {
            p.setPen(Qt::NoPen);
            p.setBrush(r % 2 == 0 ? C_ROW_EVEN : C_ROW_ODD);
            p.drawRect(margin, yRow, tableW, rowH);
            p.setPen(QPen(C_BORDER,1));
            p.drawLine(margin, yRow+rowH, margin+tableW, yRow+rowH);
            yRow += rowH;
        }

        drawBorder(yHead, qMax(rowsThisPage, 1));

        if (rowIdx >= nbRows) break;
        printer.newPage();
        currentPage++;
    }

    p.end();

    QMessageBox::information(parent, "Export réussi",
                             QString("PDF généré avec succès !\n\n"
                                     "Fichier : %1\n"
                                     "Machines : %2\n"
                                     "Pages : %3")
                                 .arg(fileName).arg(nbRows).arg(totalPages));
}
