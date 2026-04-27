#include "client_stat.h"
#include "client_historique.h"
#include <QSqlQuery>
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include <QMap>
#include <QSet>

ClientStat::ClientStat(QObject *parent) : QObject(parent)
{
    qDebug() << "Service Statistiques (v2 - Style professionnel) initialisé";
}

ClientStat::~ClientStat()
{
    qDebug() << "Service Statistiques détruit";
}

namespace {

QMap<int, double> volumesParClientId(const QVector<Achat> &achats)
{
    QMap<int, double> m;
    for (const Achat &a : achats) {
        if (a.idClient > 0)
            m[a.idClient] += a.quantite;
    }
    return m;
}

QVector<double> totauxQuantiteParMois(const QVector<Achat> &achats)
{
    QVector<double> t(12, 0.0);
    for (const Achat &a : achats) {
        if (!a.dateAchat.isValid())
            continue;
        const int mois = a.dateAchat.month();
        if (mois >= 1 && mois <= 12)
            t[mois - 1] += a.quantite;
    }
    return t;
}

} // namespace

// ============================================================
//  UTILITAIRES COULEURS
// ============================================================

QColor ClientStat::getCouleurDegradeVert(int index, int total)
{
    struct {
        int r, g, b;
    } dark  = { 27, 94, 32 };
    struct {
        int r, g, b;
    } light = { 165, 214, 167 };

    double t = (total <= 1) ? 0.0 : (double)index / (double)(total - 1);
    return QColor(
        dark.r + (int)((light.r - dark.r) * t),
        dark.g + (int)((light.g - dark.g) * t),
        dark.b + (int)((light.b - dark.b) * t));
}

// ============================================================
//  STYLE COMMUN DES GRAPHIQUES
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

// ============================================================
//  1) CAMEMBERT — Répartition par type client
// ============================================================

QChartView *ClientStat::creerGraphiqueTypeClient()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);

    QSqlQuery query;
    query.exec("SELECT TYPE_CLIENT, COUNT(*) FROM ZIT.CLIENT GROUP BY TYPE_CLIENT");

    QList<QPair<QString, int>> resultats;
    while (query.next())
        resultats.append({ query.value(0).toString(), query.value(1).toInt() });

    int total = 0;
    for (const auto &r : resultats)
        total += r.second;

    for (int i = 0; i < resultats.size(); i++) {
        QString label = resultats[i].first;
        int     count = resultats[i].second;
        double  pct   = (total > 0) ? (count * 100.0 / total) : 0;

        QPieSlice *slice = series->append(
            QString("%1\n%2 (%3%)").arg(label).arg(count).arg(pct, 0, 'f', 1),
            count);

        QColor couleur = getCouleurDegradeVert(i, qMax(resultats.size(), 2));
        slice->setBrush(couleur);
        slice->setLabelColor(QColor("#1b5e20"));
        slice->setLabelFont(QFont("Arial", 10, QFont::Bold));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(2);

        if (i == 0)
            slice->setExploded(true);
        slice->setExplodeDistanceFactor(0.06f);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Répartition des clients par type");
    chart->legend()->setVisible(false);

    return wrapInView(chart, QSize(520, 420));
}

// ============================================================
//  2) BARRES — Volume d'achat par client (carnet Oracle + fichier)
// ============================================================

QChartView *ClientStat::creerGraphiqueVolumeAchat()
{
    const QVector<Achat>        tous = ClientHistorique::chargerTousLesAchats();
    const QMap<int, double>     vol  = volumesParClientId(tous);

    QBarSeries *series = new QBarSeries();

    QList<QPair<QString, double>> clients;
    QSet<int>                     vus;

    QSqlQuery query;
    query.exec("SELECT ID_CLIENT, NOM, PRENOM FROM ZIT.CLIENT ORDER BY NOM");
    while (query.next()) {
        const int id = query.value(0).toInt();
        const double v = vol.value(id, 0.0);
        if (v <= 0.0)
            continue;
        vus.insert(id);
        clients.append({ query.value(1).toString() + QLatin1Char('\n') + query.value(2).toString(), v });
    }

    for (auto it = vol.constBegin(); it != vol.constEnd(); ++it) {
        if (it.value() <= 0.0 || vus.contains(it.key()))
            continue;
        clients.append({ QStringLiteral("Client #%1").arg(it.key()), it.value() });
    }

    if (clients.isEmpty())
        clients.append({ QStringLiteral("Aucun achat"), 0.0 });

    const int n = clients.size();
    QStringList categories;
    for (int i = 0; i < n; ++i)
        categories << clients[i].first;

    for (int i = 0; i < n; ++i) {
        auto *set = new QBarSet(clients[i].first);
        for (int j = 0; j < n; ++j)
            *set << (j == i ? clients[i].second : 0.0);
        set->setColor(getCouleurDegradeVert(i, qMax(n, 2)));
        set->setBorderColor(QColor("#1b5e20"));
        set->setLabelFont(QFont("Arial", 9));
        series->append(set);
    }

    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value kg");

    QChart *chart = new QChart();
    chart->addSeries(series);
    applyChartStyle(chart, "Volume d'achat total par client (kg)");
    chart->legend()->setVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Clients");
    axisX->setLabelsAngle(-20);
    axisX->setLabelsFont(QFont("Arial", 9));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité totale (kg)");
    axisY->setLabelFormat("%.0f");
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return wrapInView(chart, QSize(620, 420));
}

// ============================================================
//  3) COURBE — Évolution mensuelle (somme des quantités par mois)
// ============================================================

QChartView *ClientStat::creerGraphiqueEvolutionMensuelle()
{
    const QVector<Achat> tous  = ClientHistorique::chargerTousLesAchats();
    const QVector<double> moisKg = totauxQuantiteParMois(tous);

    QLineSeries *series = new QLineSeries();
    series->setName("Volume mensuel (kg)");
    QPen pen(QColor("#2e7d32"));
    pen.setWidth(3);
    series->setPen(pen);
    series->setPointsVisible(true);
    series->setPointLabelsVisible(false);

    QLineSeries *lower = new QLineSeries();

    QStringList moisNoms = { "Jan", "Fév", "Mar", "Avr", "Mai", "Juin",
                            "Juil", "Aoû", "Sep", "Oct", "Nov", "Déc" };

    double maxVal = 0;
    for (int m = 1; m <= 12; m++) {
        const double total = moisKg[m - 1];
        series->append(m, total);
        lower->append(m, 0);
        maxVal = qMax(maxVal, total);
    }

    QAreaSeries *area = new QAreaSeries(series, lower);
    QLinearGradient grad(QPointF(0, 0), QPointF(0, 1));
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);
    grad.setColorAt(0.0, QColor(46, 125, 50, 180));
    grad.setColorAt(1.0, QColor(200, 230, 201, 40));
    area->setBrush(grad);
    area->setPen(QPen(Qt::NoPen));
    area->setName("Volume mensuel (kg)");

    QChart *chart = new QChart();
    chart->addSeries(area);
    chart->addSeries(series);
    applyChartStyle(chart, "Évolution mensuelle du volume d'achat");

    QCategoryAxis *axisX = new QCategoryAxis();
    for (int i = 0; i < 12; i++)
        axisX->append(moisNoms[i], i + 1);
    axisX->setTitleText("Mois");
    axisX->setMin(1);
    axisX->setMax(12);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    area->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité (kg)");
    axisY->setLabelFormat("%.1f");
    axisY->setMin(0);
    const double ymax = (maxVal <= 1e-9) ? 1.0 : maxVal * 1.15 + 0.5;
    axisY->setMax(ymax);
    axisY->setMinorTickCount(4);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    area->attachAxis(axisY);

    chart->legend()->setVisible(false);

    return wrapInView(chart, QSize(700, 450));
}
