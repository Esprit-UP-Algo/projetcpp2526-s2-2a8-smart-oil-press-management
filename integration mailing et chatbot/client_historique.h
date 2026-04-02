#ifndef CLIENT_HISTORIQUE_H
#define CLIENT_HISTORIQUE_H

#include <QObject>
#include <QTableWidget>
#include <QTextEdit>
#include "client_achat.h"

class ClientHistorique : public QObject
{
    Q_OBJECT

public:
    explicit ClientHistorique(QObject *parent = nullptr);
    ~ClientHistorique();

    void afficherHistoriqueAchats(int idClient, QTableWidget *table);
    void afficherResumeAchats(int idClient, QTextEdit *textEdit);
    QString getHistoriqueTexte(int idClient);

private:
    ClientAchat *m_achatService;
};

#endif // CLIENT_HISTORIQUE_H
