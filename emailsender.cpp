#include "emailsender.h"
#include <QDebug>

EmailSender::EmailSender(const QString &from, const QString &to, const QString &subject, const QString &body, const QString &smtpServer, int port)
    : from(from), to(to), subject(subject), body(body), smtpServer(smtpServer), port(port) {

    appPassword = "rlum xazp qfhh zenw"; // Remplacez par un mot de passe d'application valide
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::encrypted, this, &EmailSender::onConnected);
    connect(socket, &QSslSocket::readyRead, this, &EmailSender::onReadyRead);
    connect(socket, &QAbstractSocket::errorOccurred, this, &EmailSender::onError);
}

void EmailSender::sendMail() {
    qDebug() << "Connecting to SMTP server...";
    socket->connectToHostEncrypted(smtpServer, port);
}

void EmailSender::onConnected() {
    qDebug() << "Connected to server. Sending EHLO...";
    stream.setDevice(socket);
    sendCommand("EHLO " + smtpServer);
}

void EmailSender::onReadyRead() {
    QString username = "issmailchouikhi6@gmail.com";
    QString password = "rlum xazp qfhh zenw"; // Preferably use an App Password

    QString encodedUsername = username.toUtf8().toBase64();
    QString encodedPassword = password.toUtf8().toBase64();

    qDebug() << "Encoded username: " << encodedUsername;
    qDebug() << "Encoded password: " << encodedPassword;

    QString response = socket->readAll();
    qDebug() << "Server response:" << response;

    if (response.startsWith("220")) {
        sendCommand("EHLO " + smtpServer);
    } else if (response.startsWith("250")) {
        if (!authenticated) {
            sendCommand("AUTH LOGIN");
        } else if (response.contains("MAIL FROM")) {
            sendCommand("MAIL FROM:<" + from + ">");
        } else if (response.contains("RCPT TO")) {
            sendCommand("RCPT TO:<" + to + ">");
        } else if (response.contains("DATA")) {
            sendCommand("DATA");
        }
    } else if (response.startsWith("334")) {
        if (response.contains("VXNlcm5hbWU6")) { // Username request
            sendCommand(encodedUsername);
        } else if (response.contains("UGFzc3dvcmQ6")) { // Password request
            sendCommand(encodedPassword);
            authenticated = true;
        }
    } else if (response.startsWith("354")) {
        sendCommand("Subject: " + subject + "\r\n"
                                            "From: " + from + "\r\n"
                             "To: " + to + "\r\n\r\n"
                    + body + "\r\n.");
    } else if (response.startsWith("250 OK")) {
        qDebug() << "Email sent successfully!";
        socket->disconnectFromHost();
    } else {
        qDebug() << "Unexpected response:" << response;
    }
}


void EmailSender::sendCommand(const QString &cmd) {
    qDebug() << "Sending command:" << cmd;
    stream << cmd << "\r\n";
    stream.flush();
}

void EmailSender::onError(QAbstractSocket::SocketError socketError) {
    qDebug() << "Socket Error:" << socketError << socket->errorString();
}
