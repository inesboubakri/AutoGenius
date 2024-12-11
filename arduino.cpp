// Arduino.cpp

#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent)
    : QObject(parent), serial(nullptr), connected(false) {
}

Arduino::~Arduino() {
    if (serial) {
        if (serial->isOpen()) {
            serial->close();
        }
        delete serial;
    }
}

int Arduino::connectArduino() {
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.vendorIdentifier() == arduinoUnoVendorId &&
            serialPortInfo.productIdentifier() == arduinoUnoProductId) {
            portName = serialPortInfo.portName();
            serial = new QSerialPort(portName);

            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite)) {
                connected = true;
                qDebug() << "Connexion Arduino réussie sur le port" << portName;
                connect(serial, &QSerialPort::readyRead, this, [this]() {
                    emit dataReceived(serial->readAll());
                });
                return 0;
            } else {
                delete serial;
                serial = nullptr;
                return -2;
            }
        }
    }
    return -1;
}

void Arduino::disconnectArduino() {
    if (serial && serial->isOpen()) {
        serial->close();
        delete serial;
        serial = nullptr;
        connected = false;
        qDebug() << "Déconnexion Arduino réussie";
    }
}

void Arduino::writeToArduino(const QByteArray &data) {
    if (serial && serial->isOpen()) {
        serial->write(data);
    } else {
        qDebug() << "Impossible d'écrire sur le port série : Arduino non connecté";
    }
}

QByteArray Arduino::readFromArduino() {
    if (serial && serial->isOpen()) {
        return serial->readAll();
    }
    return QByteArray(); // Retourne une donnée vide si le port n'est pas ouvert
}

QString Arduino::getArduinoPortName() const {
    return portName;
}

bool Arduino::isConnected() const {
    return connected;
}

QSerialPort* Arduino::getSerialPort() const {
    return serial;
}
