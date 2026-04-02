#ifndef EXPORTERPARTENAIRE_H
#define EXPORTERPARTENAIRE_H

#include "partenaire.h"
#include <QList>
#include <QString>
#include <QWidget>

class ExporterPartenaire
{
public:
    ExporterPartenaire();

    // Exporte la liste des partenaires en PDF.
    // parent  : fenêtre parente pour le QFileDialog
    // liste   : les partenaires à exporter (tel qu'affiché dans le tableau)
    // Retourne true si l'export a réussi, false sinon.
    static bool exporterEnPDF(QWidget *parent, const QList<Partenaire> &liste);
};

#endif // EXPORTERPARTENAIRE_H
