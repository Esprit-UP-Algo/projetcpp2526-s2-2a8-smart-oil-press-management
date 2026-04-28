#include "rfidmanager.h"
#include <QSqlError>

// ─────────────────────────────────────────
// Constructeur
// ─────────────────────────────────────────
RfidManager::RfidManager(QObject *parent)
    : QObject(parent)
    , serial(new QSerialPort(this))
{
    connect(serial, &QSerialPort::readyRead,
            this, &RfidManager::onDataReceived);
}

// ─────────────────────────────────────────
// Destructeur — NE PAS appeler disconnect()
// ─────────────────────────────────────────
RfidManager::~RfidManager()
{
    if (serial->isOpen())
        serial->close();
}

// ─────────────────────────────────────────
// Setter base de données
// ─────────────────────────────────────────
void RfidManager::setDatabase(const QSqlDatabase &database)
{
    this->db = database;
}

// ─────────────────────────────────────────
// Liste des ports série disponibles
// ─────────────────────────────────────────
QStringList RfidManager::availablePorts()
{
    QStringList ports;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ports << info.portName();
    return ports;
}

// ─────────────────────────────────────────
// Connexion à l'Arduino
// ─────────────────────────────────────────
bool RfidManager::connectToArduino(const QString &portName, int baudRate)
{
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Arduino connecté sur" << portName;
        return true;
    }

    emit erreurConnexion("Impossible d'ouvrir " + portName
                         + ": " + serial->errorString());
    return false;
}

// ─────────────────────────────────────────
// Déconnexion — renommée disconnectArduino
// pour éviter le conflit avec QObject::disconnect()
// ─────────────────────────────────────────
void RfidManager::disconnectArduino()
{
    if (serial->isOpen())
        serial->close();
}

// ─────────────────────────────────────────
// Réception des données série
// ─────────────────────────────────────────
void RfidManager::onDataReceived()
{
    buffer += serial->readAll();

    while (buffer.contains('\n')) {
        int idx = buffer.indexOf('\n');
        QString line = buffer.left(idx).trimmed();
        buffer = buffer.mid(idx + 1);

        if (line.startsWith("RFID:")) {
            QString uid = line.mid(5).trimmed();
            qDebug() << "UID reçu:" << uid;
            processUID(uid);
        }
    }
}

// ─────────────────────────────────────────
// Recherche de l'employé dans Oracle
// ─────────────────────────────────────────
void RfidManager::processUID(const QString &uid)
{
    if (!db.isOpen()) {
        sendToArduino("DB_ERROR");
        return;
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT NOM, PRENOM, POSTE FROM ZIT.EMPLOYE "
        "WHERE UPPER(UID_RFID) = UPPER(:uid)"
        );
    query.bindValue(":uid", uid);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        sendToArduino("DB_ERROR");
        return;
    }

    if (query.next()) {
        QString nom    = query.value("NOM").toString();
        QString prenom = query.value("PRENOM").toString();
        QString poste  = query.value("POSTE").toString();

        qDebug() << "Employé trouvé:" << nom << prenom;
        sendToArduino("OK:" + nom + ":" + prenom + ":" + poste);
        emit employeDetecte(nom, prenom, poste);

    } else {
        qDebug() << "Carte inconnue:" << uid;
        sendToArduino("NOT_FOUND");
        emit carteInconnue(uid);
    }
}

// ─────────────────────────────────────────
// Envoi d'un message à l'Arduino
// ─────────────────────────────────────────
void RfidManager::sendToArduino(const QString &message)
{
    if (serial->isOpen()) {
        serial->write((message + "\n").toUtf8());
        serial->flush();
    }
}
