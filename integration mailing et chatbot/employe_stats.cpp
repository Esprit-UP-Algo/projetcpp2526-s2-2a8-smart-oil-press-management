#include "employe_stats.h"

// ─────────────────────────────────────────────────────────────
//  Charge et affiche les statistiques dans les labels UI
// ─────────────────────────────────────────────────────────────
void EmployeStats::charger(QLabel *labelTotal,
                           QLabel *labelOuvriers,
                           QLabel *labelTechniciens)
{
    Employe e;
    labelTotal->setText(QString::number(e.getTotalEmployes()));
    labelOuvriers->setText(QString::number(e.getNombreParPoste("Ouvrier")));
    labelTechniciens->setText(QString::number(e.getNombreParPoste("Technicien")));
}

// ─────────────────────────────────────────────────────────────
//  Nombre d'employés pour un poste donné
// ─────────────────────────────────────────────────────────────
int EmployeStats::parPoste(const QString &poste)
{
    Employe e;
    return e.getNombreParPoste(poste);
}

// ─────────────────────────────────────────────────────────────
//  Total employés
// ─────────────────────────────────────────────────────────────
int EmployeStats::total()
{
    Employe e;
    return e.getTotalEmployes();
}
