#ifndef CLIENT_STAT_H
#define CLIENT_STAT_H

#include <QObject>
#include <QColor>
#include <QtCharts>

class ClientStat : public QObject
{
    Q_OBJECT

public:
    explicit ClientStat(QObject *parent = nullptr);
    ~ClientStat();

    // Graphiques (style professionnel vert dégradé)
    QChartView* creerGraphiqueTypeClient();
    QChartView* creerGraphiqueVolumeAchat();
    QChartView* creerGraphiqueEvolutionMensuelle();

    // Utilitaire couleur (accessible depuis d'autres classes si besoin)
    static QColor getCouleurDegradeVert(int index, int total);

};

#endif // CLIENT_STAT_H
