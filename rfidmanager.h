#ifndef RFIDMANAGER_H
#define RFIDMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RfidManager : public QObject
{
    Q_OBJECT

public:
    explicit RfidManager(QObject *parent = nullptr);
    ~RfidManager();

    bool connectToArduino(const QString &portName, int baudRate = 9600);
    void setDatabase(const QSqlDatabase &db);
    void disconnectArduino();
    QStringList availablePorts();

signals:
    void employeDetecte(const QString &nom, const QString &prenom, const QString &poste);
    void carteInconnue(const QString &uid);
    void erreurConnexion(const QString &message);

private slots:
    void onDataReceived();

private:
    QSerialPort *serial;
    QSqlDatabase db;
    QString buffer;

    void processUID(const QString &uid);
    void sendToArduino(const QString &message);
};

#endif // RFIDMANAGER_H
