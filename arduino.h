#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

/*
 * ArduinoInterface — Communication avec Arduino via USB série
 *
 * Protocole Arduino (DHT11 sur pin 2, Buzzer pin 8, Relais pin 7) :
 *   ARDUINO_PRET          → Arduino prêt
 *   NORMAL:<temp>         → Température normale
 *   SURCHAUFFE:<temp>     → Température > seuil
 *   HUMIDITE:<hum>        → Humidité (envoyée après NORMAL/SURCHAUFFE)
 *   VENTILATEUR:ON/OFF    → État ventilateur
 *   ERREUR:<val>          → Erreur capteur DHT
 *
 * Commandes envoyées à l'Arduino :
 *   VENTILO_ON\n          → Allumer ventilateur
 *   VENTILO_OFF\n         → Éteindre ventilateur
 */

class ArduinoInterface : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoInterface(QObject *parent = nullptr);
    ~ArduinoInterface();

    void setDatabase(const QSqlDatabase &db);
    bool connectToArduino();
    void disconnectArduino();
    void allumerVentilateur();
    void eteindreVentilateur();

    bool   isConnected()      const { return m_serialPort && m_serialPort->isOpen(); }
    bool   ventilateurActif() const { return m_ventilateurActif; }
    double getTemperature()   const { return m_temperature; }
    double getHumidite()      const { return m_humidite; }
    bool   isSurchauffe()     const { return m_surchauffe; }

signals:
    void donneesRecues(double temperature, double humidite, bool surchauffe);
    void ventilateurChange(bool actif);
    void connexionChangee(bool connecte);
    void erreurSurvenue(const QString &message);
    void arduinoPret();

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);
    void onTimeout();

private:
    void    parserMessageArduino(const QString &message);
    void    insererDonneesEnBD(double temperature, double humidite, bool surchauffe);
    QString trouverPortArduino() const;

    QSerialPort  *m_serialPort;
    QTimer       *m_timeoutTimer;
    QSqlDatabase  m_db;

    bool   m_ventilateurActif;
    double m_temperature;
    double m_humidite;
    bool   m_surchauffe;

    // Flags pour synchroniser température + humidité avant d'émettre donneesRecues
    bool m_temperatureRecue;
    bool m_humiditeRecue;

    // Flag : au moins une donnée valide reçue (pour ignorer timeout résiduel)
    bool m_donneesRecuesUneFois;

    static constexpr int BAUD_RATE  = 9600;
    static constexpr int TIMEOUT_MS = 8000;  // 8 s — DHT11 lent au démarrage
};

#endif // ARDUINO_H
