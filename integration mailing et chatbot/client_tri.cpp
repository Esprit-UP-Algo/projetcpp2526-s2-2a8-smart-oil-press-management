#include "client_tri.h"
#include <QSqlQuery>
#include <QDebug>
#include <algorithm>

ClientTri::ClientTri() {}

QList<Client> ClientTri::trierParNom(const QList<Client> &clients, bool ascendant)
{
    QList<Client> result = clients;
    std::sort(result.begin(), result.end(),
              [ascendant](const Client &a, const Client &b) {
                  if (ascendant)
                      return a.getNom() < b.getNom();
                  else
                      return a.getNom() > b.getNom();
              });
    return result;
}

QList<Client> ClientTri::trierParTypeClient(const QList<Client> &clients)
{
    QList<Client> result = clients;
    std::sort(result.begin(), result.end(),
              [](const Client &a, const Client &b) {
                  return a.getTypeClient() < b.getTypeClient();
              });
    return result;
}

double ClientTri::getVolumeTotalAchats(int idClient)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(quantite) FROM ZIT.ACHATS WHERE ID_CLIENT = :id");
    query.bindValue(":id", idClient);
    if (query.exec() && query.next())
        return query.value(0).toDouble();
    return 0.0;
}

QList<Client> ClientTri::trierParVolumeAchat()
{
    QList<Client> liste;
    QSqlQuery query;
    query.exec("SELECT c.ID_CLIENT, c.NOM, c.PRENOM, c.EMAIL, c.TELEPHONE, c.TYPE_CLIENT, c.AVIS, "
               "NVL(SUM(a.QUANTITE), 0) as VOLUME "
               "FROM ZIT.CLIENT c "
               "LEFT JOIN ZIT.ACHATS a ON c.ID_CLIENT = a.ID_CLIENT "
               "GROUP BY c.ID_CLIENT, c.NOM, c.PRENOM, c.EMAIL, c.TELEPHONE, c.TYPE_CLIENT, c.AVIS "
               "ORDER BY VOLUME DESC");

    while (query.next()) {
        Client c(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString()
            );
        liste.append(c);
    }
    return liste;
}

QList<Client> ClientTri::trierParPrenom(const QList<Client> &clients, bool ascendant)
{
    QList<Client> result = clients;
    std::sort(result.begin(), result.end(),
              [ascendant](const Client &a, const Client &b) {
                  if (ascendant)
                      return a.getPrenom() < b.getPrenom();
                  else
                      return a.getPrenom() > b.getPrenom();
              });
    return result;
}

QList<Client> ClientTri::resetAffichage()
{
    Client c;
    return c.afficherTous();
}
