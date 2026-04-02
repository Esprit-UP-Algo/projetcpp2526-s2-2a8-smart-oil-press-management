#ifndef STATPRODUCTION_H
#define STATPRODUCTION_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>

class StatProduction
{
public:
    StatProduction();

    // Statistics computed from DB
    int    getTotalProductions()  const { return totalProductions; }
    double getTotalOlives()       const { return totalOlives; }
    double getTotalHuile()        const { return totalHuile; }
    double getRendementMoyen()    const { return rendementMoyen; }
    double getRendementMax()      const { return rendementMax; }
    double getRendementMin()      const { return rendementMin; }

    // Load stats from DB and update the stat card labels
    void calculerEtAfficher(QLabel *labelTotal,
                            QLabel *labelOlives,
                            QLabel *labelHuile,
                            QLabel *labelRendement);

private:
    int    totalProductions;
    double totalOlives;
    double totalHuile;
    double rendementMoyen;
    double rendementMax;
    double rendementMin;

    // Internal: fetch all stats from DB
    bool chargerStats();
};

#endif // STATPRODUCTION_H
