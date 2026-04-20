#include "employe_stats.h"
#include <QSqlQuery>
#include <QDebug>
#include <QPainter>
#include <QDate>

// ============================================================
//  STYLE COMMUN
// ============================================================

static void applyChartStyle(QChart *chart, const QString &titre)
{
    chart->setTitle(titre);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(800);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setDropShadowEnabled(true);

    QFont titleFont("Arial", 13, QFont::Bold);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor("#1b5e20")));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 10));
}

static QChartView *wrapInView(QChart *chart, QSize minSize = QSize(520, 400))
{
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(minSize);
    return view;
}

// le reste du fichier est identique...

// ============================================================
//  COULEURS DÉGRADÉ VERT
// ============================================================

QColor EmployeStats::getCouleurDegradeVert(int index, int tot)
{
    struct { int r, g, b; } dark  = { 27,  94,  32  };
    struct { int r, g, b; } light = { 165, 214, 167 };

    double t = (tot <= 1) ? 0.0 : (double)index / (double)(tot - 1);
    return QColor(
        dark.r + (int)((light.r - dark.r) * t),
        dark.g + (int)((light.g - dark.g) * t),
        dark.b + (int)((light.b - dark.b) * t));
}

// ============================================================
//  MÉTHODES STATIQUES (compatibilité ancienne)
// ============================================================

void EmployeStats::charger(QLabel *labelTotal,
                           QLabel *labelOuvriers,
                           QLabel *labelTechniciens)
{
    Employe e;
    labelTotal->setText(QString::number(e.getTotalEmployes()));
    labelOuvriers->setText(QString::number(e.getNombreParPoste("Ouvrier")));
    labelTechniciens->setText(QString::number(e.getNombreParPoste("Technicien")));
}

int EmployeStats::parPoste(const QString &poste)
{
    Employe e;
    return e.getNombreParPoste(poste);
}

int EmployeStats::total()
{
    Employe e;
    return e.getTotalEmployes();
}

// ============================================================
//  1) CAMEMBERT — Répartition par poste
// ============================================================

QChartView *EmployeStats::creerGraphiqueRepartitionPostes()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    QSqlQuery query;
    query.exec("SELECT POSTE, COUNT(*) FROM EMPLOYE GROUP BY POSTE ORDER BY COUNT(*) DESC");

    QList<QPair<QString, int>> resultats;
    int totalEmp = 0;
    while (query.next()) {
        resultats.append({ query.value(0).toString(), query.value(1).toInt() });
        totalEmp += query.value(1).toInt();
    }

    for (int i = 0; i < resultats.size(); i++) {
        QString label = resultats[i].first;
        int     count = resultats[i].second;
        double  pct   = (totalEmp > 0) ? (count * 100.0 / totalEmp) : 0;

        QPieSlice *slice = series->append(
            QString("%1\n%2 (%3%)").arg(label).arg(count).arg(pct, 0, 'f', 1),
            count);

        QColor couleur = getCouleurDegradeVert(i, qMax(resultats.size(), 2));
        slice->setBrush(couleur);
        slice->setLabelColor(QColor("#1b5e20"));
        slice->setLabelFont(QFont("Arial", 10, QFont::Bold));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);

        if (i == 0) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.06f);
        }
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Répartition des Employés par Poste");
    chart->legend()->setVisible(false);

    return wrapInView(chart, QSize(520, 420));
}

// ============================================================
//  2) BARRES — Salaire moyen par poste
// ============================================================

QChartView *EmployeStats::creerGraphiqueSalaires()
{
    QSqlQuery query;
    query.exec("SELECT POSTE, AVG(SALAIRE), MIN(SALAIRE), MAX(SALAIRE) "
               "FROM EMPLOYE GROUP BY POSTE ORDER BY AVG(SALAIRE) DESC");

    QStringList categories;
    QList<double> moyennes, mins, maxs;

    while (query.next()) {
        categories << query.value(0).toString();
        moyennes   << query.value(1).toDouble();
        mins       << query.value(2).toDouble();
        maxs       << query.value(3).toDouble();
    }

    const int n = categories.size();

    QBarSeries *series = new QBarSeries();

    // Barre salaire moyen
    QBarSet *setMoy = new QBarSet("Salaire Moyen");
    setMoy->setColor(QColor("#2d4a1f"));
    setMoy->setBorderColor(QColor("#1b5e20"));
    setMoy->setLabelFont(QFont("Arial", 9));

    // Barre salaire min
    QBarSet *setMin = new QBarSet("Salaire Min");
    setMin->setColor(QColor("#a5d6a7"));
    setMin->setBorderColor(QColor("#1b5e20"));
    setMin->setLabelFont(QFont("Arial", 9));

    // Barre salaire max
    QBarSet *setMax = new QBarSet("Salaire Max");
    setMax->setColor(QColor("#ffd700"));
    setMax->setBorderColor(QColor("#b8860b"));
    setMax->setLabelFont(QFont("Arial", 9));

    for (int i = 0; i < n; i++) {
        *setMoy << moyennes[i];
        *setMin << mins[i];
        *setMax << maxs[i];
    }

    series->append(setMoy);
    series->append(setMin);
    series->append(setMax);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value DT");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Salaires par Poste (Moy / Min / Max)");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Postes");
    axisX->setLabelsFont(QFont("Arial", 10));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Salaire (DT)");
    axisY->setLabelFormat("%.0f");
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return wrapInView(chart, QSize(620, 420));
}

// ============================================================
//  3) BARRES HORIZONTALES — Ancienneté par employé
// ============================================================

QChartView *EmployeStats::creerGraphiqueAnciennete()
{
    QSqlQuery query;
    query.exec("SELECT NOM, PRENOM, DATE_EMBAUCHE FROM EMPLOYE ORDER BY DATE_EMBAUCHE ASC");

    QList<QPair<QString, int>> employes; // nom complet, années ancienneté

    QDate today = QDate::currentDate();
    while (query.next()) {
        QString nom    = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QDate   date   = query.value(2).toDate();

        if (!date.isValid()) {
            // Essayer format string si Oracle retourne string
            date = QDate::fromString(query.value(2).toString(), "dd/MM/yyyy");
        }

        int annees = 0;
        if (date.isValid())
            annees = date.daysTo(today) / 365;

        employes.append({ nom + " " + prenom, annees });
    }

    QHorizontalBarSeries *series = new QHorizontalBarSeries();

    QStringList noms;
    for (int i = 0; i < employes.size(); i++) {
        noms << employes[i].first;

        QBarSet *set = new QBarSet(employes[i].first);
        *set << employes[i].second;
        set->setColor(getCouleurDegradeVert(i, qMax(employes.size(), 2)));
        set->setBorderColor(QColor("#1b5e20"));
        set->setLabelFont(QFont("Arial", 9));
        series->append(set);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value ans");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Ancienneté des Employés (années)");
    chart->legend()->setVisible(false);

    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(noms);
    axisY->setLabelsFont(QFont("Arial", 10));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Années d'ancienneté");
    axisX->setLabelFormat("%.0f");
    axisX->setMinorTickCount(4);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    return wrapInView(chart, QSize(620, 420));
}
