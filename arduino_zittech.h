#ifndef ARDUINO_ZITTECH_H
#define ARDUINO_ZITTECH_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class ArduinoZitTech : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoZitTech(QObject *parent = nullptr);
    ~ArduinoZitTech();

    // Connexion / déconnexion
    // 0 = OK, 1 = trouvé mais open failed, -1 = non trouvé
    int connectArduino();
    int closeArduino();

    // Envoi IDs anomalies
    // Format: "IDS:id1,id2,...\n" ou "IDS:\n"
    void sendAnomalyIds(const QList<int> &ids);

    // IO brutes
    void       write_to_arduino(const QByteArray &data);
    QByteArray read_from_arduino();

    // Accesseurs
    QSerialPort* getserial()   { return serial; }
    QString      getPortName() { return arduino_port_name; }
    bool         isConnected() { return serial && serial->isOpen(); }

signals:
    void idConfirmed(int confirmedId);
    void idInvalid(int typedId);
    void serialError(const QString &message);

private slots:
    void onDataReceived();

private:
    QSerialPort *serial;
    QByteArray   m_readBuffer;

    QString      arduino_port_name;
    bool         arduino_is_available;

    // Helpers
    bool matchesKnownArduino(const QSerialPortInfo &info) const;
    bool matchesByDescription(const QSerialPortInfo &info) const;
};

#endif // ARDUINO_ZITTECH_H
