#include "arduino_zittech.h"

ArduinoZitTech::ArduinoZitTech(QObject *parent)
    : QObject(parent)
    , serial(new QSerialPort(this))
    , arduino_is_available(false)
{
    connect(serial, &QSerialPort::readyRead,
            this,   &ArduinoZitTech::onDataReceived);

    connect(serial, &QSerialPort::errorOccurred,
            this, [this](QSerialPort::SerialPortError error) {
                if (error != QSerialPort::NoError) {
                    emit serialError(
                        QString("Erreur série (%1) : %2")
                            .arg(error)
                            .arg(serial->errorString()));
                }
            });
}

ArduinoZitTech::~ArduinoZitTech()
{
    closeArduino();
}

bool ArduinoZitTech::matchesKnownArduino(const QSerialPortInfo &info) const
{
    if (!info.hasVendorIdentifier() || !info.hasProductIdentifier())
        return false;

    const quint16 vid = info.vendorIdentifier();
    const quint16 pid = info.productIdentifier();

    // Arduino Uno officiels + clones fréquents
    // Uno R3 officiel:
    if ((vid == 0x2341 && (pid == 0x0043 || pid == 0x0001)) ||  // Arduino LLC
        (vid == 0x2A03 && (pid == 0x0043 || pid == 0x0001)) ||  // Arduino SRL
        (vid == 0x1A86 && pid == 0x7523) ||                      // CH340 clone
        (vid == 0x10C4 && pid == 0xEA60))                        // CP210x clone
    {
        return true;
    }

    return false;
}

bool ArduinoZitTech::matchesByDescription(const QSerialPortInfo &info) const
{
    const QString d = info.description().toLower();
    const QString m = info.manufacturer().toLower();
    const QString p = info.portName().toLower();

    return d.contains("arduino") || d.contains("ch340") || d.contains("usb serial") ||
           m.contains("arduino") || m.contains("wch")   || m.contains("silicon labs") ||
           p.contains("ttyusb") || p.contains("ttyacm") || p.startsWith("com");
}

int ArduinoZitTech::connectArduino()
{
    arduino_is_available = false;
    arduino_port_name.clear();

    // Si déjà ouvert, fermer proprement avant nouvelle détection
    if (serial->isOpen())
        serial->close();

    const auto ports = QSerialPortInfo::availablePorts();

    qDebug() << "=== Available serial ports ===";
    for (const QSerialPortInfo &p : ports) {
        qDebug() << "Port:" << p.portName()
        << "| Desc:" << p.description()
        << "| Manufacturer:" << p.manufacturer()
        << "| VID:" << (p.hasVendorIdentifier() ? QString("0x%1").arg(p.vendorIdentifier(), 4, 16, QLatin1Char('0')) : "N/A")
        << "| PID:" << (p.hasProductIdentifier() ? QString("0x%1").arg(p.productIdentifier(), 4, 16, QLatin1Char('0')) : "N/A");
    }

    // 1) Match VID/PID connus
    for (const QSerialPortInfo &info : ports) {
        if (matchesKnownArduino(info)) {
            arduino_is_available = true;
            arduino_port_name = info.portName();
            qDebug() << "[ArduinoZitTech] Matched by VID/PID on port:" << arduino_port_name;
            break;
        }
    }

    // 2) Fallback description/manufacturer
    if (!arduino_is_available) {
        for (const QSerialPortInfo &info : ports) {
            if (matchesByDescription(info)) {
                arduino_is_available = true;
                arduino_port_name = info.portName();
                qDebug() << "[ArduinoZitTech] Matched by description/manufacturer on port:" << arduino_port_name;
                break;
            }
        }
    }

    if (!arduino_is_available || arduino_port_name.isEmpty()) {
        qDebug() << "arduino_port_name is : \"\"";
        qDebug() << "arduino is not available";
        return -1;
    }

    serial->setPortName(arduino_port_name);

    if (!serial->open(QSerialPort::ReadWrite)) {
        qDebug() << "arduino is available but not connected to :" << arduino_port_name
                 << "| error:" << serial->errorString();
        return 1;
    }

    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    qDebug() << "[ArduinoZitTech] Connected successfully on" << arduino_port_name;
    return 0;
}

int ArduinoZitTech::closeArduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

void ArduinoZitTech::write_to_arduino(const QByteArray &d)
{
    if (serial->isWritable()) {
        serial->write(d);
        serial->flush();
    } else {
        qDebug() << "[ArduinoZitTech] Couldn't write to serial!";
    }
}

QByteArray ArduinoZitTech::read_from_arduino()
{
    if (serial->isReadable()) {
        return serial->readAll();
    }
    return QByteArray();
}

void ArduinoZitTech::sendAnomalyIds(const QList<int> &ids)
{
    if (!serial->isOpen()) {
        qDebug() << "[ArduinoZitTech] Cannot send IDs — serial port not open.";
        return;
    }

    QString idString;
    for (int i = 0; i < ids.size(); ++i) {
        if (i > 0) idString += ",";
        idString += QString::number(ids[i]);
    }

    const QByteArray message = ("IDS:" + idString + "\n").toUtf8();
    write_to_arduino(message);

    qDebug() << "[ArduinoZitTech] Sent to Arduino:" << message.trimmed();
}

void ArduinoZitTech::onDataReceived()
{
    m_readBuffer += serial->readAll();

    while (m_readBuffer.contains('\n')) {
        const int idx = m_readBuffer.indexOf('\n');
        const QByteArray line = m_readBuffer.left(idx).trimmed();
        m_readBuffer = m_readBuffer.mid(idx + 1);

        const QString message = QString::fromUtf8(line);
        qDebug() << "[ArduinoZitTech] Received:" << message;

        if (message.startsWith("CONFIRM:")) {
            bool ok = false;
            const int id = message.mid(8).toInt(&ok);
            if (ok) emit idConfirmed(id);
        }
        else if (message.startsWith("INVALID:")) {
            bool ok = false;
            const int id = message.mid(8).toInt(&ok);
            if (ok) emit idInvalid(id);
        }
    }
}
