#ifndef CLIENT_RECHERCHE_H
#define CLIENT_RECHERCHE_H

#include <QObject>
#include <QTableWidget>

class ClientRecherche : public QObject
{
    Q_OBJECT

public:
    explicit ClientRecherche(QObject *parent = nullptr);
    ~ClientRecherche();

    void rechercherParNom(QTableWidget *table, const QString &nom);
    void rechercherParTelephone(QTableWidget *table, const QString &telephone);
    void rechercherParEmail(QTableWidget *table, const QString &email);
    void rechercherParType(QTableWidget *table, const QString &type);
};

#endif // CLIENT_RECHERCHE_H
