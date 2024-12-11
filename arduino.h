// Arduino.h

#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QByteArray>

class Arduino : public QObject {
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino();

    int connectArduino();
    void disconnectArduino();
    void writeToArduino(const QByteArray &data);  // Déclaration correcte de la méthode
    QByteArray readFromArduino();

    QString getArduinoPortName() const;
    bool isConnected() const;

    QSerialPort* getSerialPort() const;

signals:
    void dataReceived(const QByteArray &data);

private:
    QSerialPort *serial;
    QString portName;
    bool connected;

    static const quint16 arduinoUnoVendorId = 9025;
    static const quint16 arduinoUnoProductId = 67;
};

#endif // ARDUINO_H
