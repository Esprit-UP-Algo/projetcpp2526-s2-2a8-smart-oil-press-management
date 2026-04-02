#ifndef CLIENT_EXPORT_H
#define CLIENT_EXPORT_H

#include <QObject>
#include <QTableWidget>
#include <QWidget>

class ClientExport : public QObject
{
    Q_OBJECT

public:
    explicit ClientExport(QObject *parent = nullptr);
    ~ClientExport();

    void exporterPDF(QTableWidget *table, const QString &cheminFichier);
    void exporterExcel(QTableWidget *table, const QString &cheminFichier);
    void afficherDialogExport(QTableWidget *table, QWidget *parent);

private:
    void exporterEnPDF(QTableWidget *table, const QString &chemin);
    void exporterEnExcel(QTableWidget *table, const QString &chemin);
};

#endif // CLIENT_EXPORT_H
