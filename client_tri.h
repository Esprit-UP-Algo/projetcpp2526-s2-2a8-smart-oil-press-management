#ifndef CLIENT_TRI_H
#define CLIENT_TRI_H

#include "client.h"
#include <QList>

class ClientTri
{
public:
    ClientTri();

    // Méthodes statiques de tri
    static QList<Client> trierParNom(const QList<Client> &clients, bool ascendant = true);
    static QList<Client> trierParTypeClient(const QList<Client> &clients);
    static QList<Client> trierParVolumeAchat();
    static QList<Client> trierParPrenom(const QList<Client> &clients, bool ascendant = true);
    static QList<Client> resetAffichage();

private:
    static double getVolumeTotalAchats(int idClient);
};

#endif // CLIENT_TRI_H
