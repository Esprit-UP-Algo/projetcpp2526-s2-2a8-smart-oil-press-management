#include "arduino.h"
#include <QDateTime>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────────────────────────────────────
ArduinoInterface::ArduinoInterface(QObject *parent)
    : QObject(parent)
    , m_serialPort(nullptr)
    , m_timeoutTimer(nullptr)
    , m_ventilateurActif(false)
    , m_temperature(0.0)
    , m_humidite(0.0)
    , m_surchauffe(false)
    , m_temperatureRecue(false)
    , m_humiditeRecue(false)
    , m_donneesRecuesUneFois(false)
{
    m_timeoutTimer = new QTimer(this);
    m_timeoutTimer->setSingleShot(true);
    connect(m_timeoutTimer, &QTimer::timeout,
            this, &ArduinoInterface::onTimeout);
}

ArduinoInterface::~ArduinoInterface()
{
    disconnectArduino();
}

// ─────────────────────────────────────────────────────────────────────────────
//  setDatabase
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::setDatabase(const QSqlDatabase &db)
{
    m_db = db;
}

// ─────────────────────────────────────────────────────────────────────────────
//  trouverPortArduino
// ─────────────────────────────────────────────────────────────────────────────
QString ArduinoInterface::trouverPortArduino() const
{
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &port : ports) {
        if (port.portName() == "COM5") {
            qDebug() << "[Arduino] Port COM5 trouvé.";
            return port.portName();
        }
    }

    qDebug() << "[Arduino] COM5 non trouvé.";
    return QString();
}

// ─────────────────────────────────────────────────────────────────────────────
//  connectToArduino
// ─────────────────────────────────────────────────────────────────────────────
bool ArduinoInterface::connectToArduino()
{
    if (m_serialPort && m_serialPort->isOpen()) {
        qDebug() << "[Arduino] Déjà connecté.";
        return true;
    }

    QString portName = trouverPortArduino();
    if (portName.isEmpty()) {
        emit erreurSurvenue(
            "Aucun port Arduino trouvé.\n"
            "Vérifiez la connexion USB et les drivers (CH340 / FTDI).");
        return false;
    }

    m_serialPort = new QSerialPort(this);
    m_serialPort->setPortName(portName);
    m_serialPort->setBaudRate(BAUD_RATE);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        emit erreurSurvenue(
            QString("Impossible d'ouvrir le port %1 : %2\n\n"
                    "➡ Fermez le Serial Monitor d'Arduino IDE\n"
                    "➡ Fermez tout autre logiciel utilisant ce port")
                .arg(portName, m_serialPort->errorString()));
        delete m_serialPort;
        m_serialPort = nullptr;
        return false;
    }

    // Reset des flags à chaque nouvelle connexion
    m_temperatureRecue    = false;
    m_humiditeRecue       = false;
    m_donneesRecuesUneFois = false;

    connect(m_serialPort, &QSerialPort::readyRead,
            this, &ArduinoInterface::onReadyRead);

    connect(m_serialPort,
            QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::errorOccurred),
            this, &ArduinoInterface::onErrorOccurred);

    qDebug() << "[Arduino] Connecté sur" << portName;

    m_timeoutTimer->start(TIMEOUT_MS);
    emit connexionChangee(true);
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  disconnectArduino
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::disconnectArduino()
{
    if (m_timeoutTimer && m_timeoutTimer->isActive())
        m_timeoutTimer->stop();

    if (m_serialPort) {
        if (m_serialPort->isOpen())
            m_serialPort->close();
        m_serialPort->deleteLater();
        m_serialPort = nullptr;
        emit connexionChangee(false);
        qDebug() << "[Arduino] Déconnecté.";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  allumerVentilateur / eteindreVentilateur
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::allumerVentilateur()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        emit erreurSurvenue("Arduino non connecté.");
        return;
    }
    m_serialPort->write("VENTILO_ON\n");
    if (!m_serialPort->waitForBytesWritten(500))
        emit erreurSurvenue("Échec envoi commande VENTILO_ON.");
    else
        qDebug() << "[Arduino] Commande VENTILO_ON envoyée.";
}

void ArduinoInterface::eteindreVentilateur()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        emit erreurSurvenue("Arduino non connecté.");
        return;
    }
    m_serialPort->write("VENTILO_OFF\n");
    if (!m_serialPort->waitForBytesWritten(500))
        emit erreurSurvenue("Échec envoi commande VENTILO_OFF.");
    else
        qDebug() << "[Arduino] Commande VENTILO_OFF envoyée.";
}

// ─────────────────────────────────────────────────────────────────────────────
//  onReadyRead
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::onReadyRead()
{
    if (!m_serialPort) return;

    while (m_serialPort->canReadLine()) {
        QByteArray line    = m_serialPort->readLine();
        QString    message = QString::fromUtf8(line).trimmed();

        if (!message.isEmpty()) {
            qDebug() << "[Arduino] Reçu:" << message;
            parserMessageArduino(message);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  parserMessageArduino
//
//  FIX TIMEOUT : dès qu'on reçoit n'importe quel message valide, on arrête
//  le timer — l'Arduino répond même si ARDUINO_PRET arrive tard.
//
//  FIX HUMIDITE : on attend température ET humidité du même cycle avant
//  d'émettre donneesRecues, pour éviter humidité = 0.0.
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::parserMessageArduino(const QString &message)
{
    // ── Stopper le timeout dès le premier message valide reçu ───────────────
    if (m_timeoutTimer->isActive())
        m_timeoutTimer->stop();

    // ── ARDUINO_PRET ─────────────────────────────────────────────────────────
    if (message == "ARDUINO_PRET") {
        m_donneesRecuesUneFois = true;
        emit arduinoPret();
        qDebug() << "[Arduino] Prêt.";
        return;
    }

    // ── Température normale ───────────────────────────────────────────────────
    if (message.startsWith("NORMAL:")) {
        m_temperature          = message.mid(7).toDouble();
        m_surchauffe           = false;
        m_temperatureRecue     = true;
        m_donneesRecuesUneFois = true;

        if (m_humiditeRecue) {
            emit donneesRecues(m_temperature, m_humidite, false);
            insererDonneesEnBD(m_temperature, m_humidite, false);
            m_temperatureRecue = false;
            m_humiditeRecue    = false;
        }
        return;
    }

    // ── Surchauffe ────────────────────────────────────────────────────────────
    if (message.startsWith("SURCHAUFFE:")) {
        m_temperature          = message.mid(11).toDouble();
        m_surchauffe           = true;
        m_temperatureRecue     = true;
        m_donneesRecuesUneFois = true;

        if (m_humiditeRecue) {
            emit donneesRecues(m_temperature, m_humidite, true);
            insererDonneesEnBD(m_temperature, m_humidite, true);
            m_temperatureRecue = false;
            m_humiditeRecue    = false;
        }
        return;
    }

    // ── Humidité — arrive toujours APRÈS NORMAL/SURCHAUFFE ───────────────────
    if (message.startsWith("HUMIDITE:")) {
        m_humidite             = message.mid(9).toDouble();
        m_humiditeRecue        = true;
        m_donneesRecuesUneFois = true;

        if (m_temperatureRecue) {
            emit donneesRecues(m_temperature, m_humidite, m_surchauffe);
            insererDonneesEnBD(m_temperature, m_humidite, m_surchauffe);
            m_temperatureRecue = false;
            m_humiditeRecue    = false;
        }
        return;
    }

    // ── Ventilateur ───────────────────────────────────────────────────────────
    if (message == "VENTILATEUR:ON") {
        m_ventilateurActif = true;
        emit ventilateurChange(true);
        return;
    }

    if (message == "VENTILATEUR:OFF") {
        m_ventilateurActif = false;
        emit ventilateurChange(false);
        return;
    }

    // ── Erreur capteur DHT ────────────────────────────────────────────────────
    if (message.startsWith("ERREUR:")) {
        m_temperatureRecue = false;
        m_humiditeRecue    = false;
        emit erreurSurvenue("Erreur capteur DHT11 : " + message);
        return;
    }

    qDebug() << "[Arduino] Message inconnu ignoré:" << message;
}

// ─────────────────────────────────────────────────────────────────────────────
//  insererDonneesEnBD
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::insererDonneesEnBD(double temperature,
                                          double humidite,
                                          bool   surchauffe)
{
    // Fallback fichier texte si BD non disponible
    auto logToFile = [&]() {
        QFile logFile("arduino_log.txt");
        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                << " | Temp:" << temperature << "°C"
                << " | Hum:"  << humidite    << "%"
                << " | Surchauffe:"    << (surchauffe        ? "OUI" : "NON")
                << " | Ventilateur:"   << (m_ventilateurActif ? "ON"  : "OFF")
                << "\n";
            logFile.close();
        }
    };

    if (!m_db.isOpen()) {
        qDebug() << "[Arduino] BD non ouverte — sauvegarde dans arduino_log.txt";
        logToFile();
        return;
    }

    // ── Obtenir le prochain ID via MAX+1 ────────────────────────────────────
    int nextId = 1;
    QSqlQuery maxQuery(m_db);
    if (maxQuery.exec("SELECT NVL(MAX(ID_CAPTURE), 0) + 1 FROM CAPTURES_ARDUINO")
        && maxQuery.next()) {
        nextId = maxQuery.value(0).toInt();
    } else {
        qDebug() << "[Arduino] Erreur MAX ID:" << maxQuery.lastError().text();
        logToFile();
        return;
    }

    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO CAPTURES_ARDUINO "
        "(ID_CAPTURE, DATE_CAPTURE, TEMPERATURE, HUMIDITE, SURCHAUFFE, VENTILATEUR_ACTIF) "
        "VALUES (:id, SYSDATE, :temp, :hum, :surch, :vent)"
        );
    query.bindValue(":id",    nextId);
    query.bindValue(":temp",  temperature);
    query.bindValue(":hum",   humidite);
    query.bindValue(":surch", surchauffe         ? 1 : 0);
    query.bindValue(":vent",  m_ventilateurActif  ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "[Arduino] Erreur insertion BD:" << query.lastError().text();
        logToFile();
    } else {
        qDebug() << "[Arduino] BD ← ID:" << nextId
                 << "| Temp:" << temperature
                 << "°C | Hum:" << humidite
                 << "% | Surchauffe:" << (surchauffe ? "OUI" : "NON");
    }
}

//  onErrorOccurred
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;

    if (error == QSerialPort::ResourceError ||
        error == QSerialPort::DeviceNotFoundError)
    {
        emit erreurSurvenue(
            QString("Erreur port série : %1")
                .arg(m_serialPort ? m_serialPort->errorString() : "inconnu"));
        disconnectArduino();
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  onTimeout
//  FIX : si des données ont déjà été reçues, on ne déconnecte pas —
//        le timeout est juste résiduel (ARDUINO_PRET arrivé tard)
// ─────────────────────────────────────────────────────────────────────────────
void ArduinoInterface::onTimeout()
{
    // Si on a déjà reçu des données valides → tout va bien, on ignore
    if (m_donneesRecuesUneFois) {
        qDebug() << "[Arduino] Timeout ignoré — données déjà reçues.";
        return;
    }

    // Aucune donnée reçue du tout → vraie erreur
    emit erreurSurvenue(
        "Timeout : l'Arduino n'a pas répondu dans les 8 secondes.\n"
        "Vérifiez que le sketch Arduino est bien chargé.\n"
        "Broches attendues : DHT11→pin 2 | Buzzer→pin 8 | Relais→pin 7"
        );
    disconnectArduino();
}
