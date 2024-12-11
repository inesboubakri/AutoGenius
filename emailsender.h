#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QObject>
#include <QSslSocket>
#include <QString>
#include <QTextStream>

class EmailSender : public QObject {
    Q_OBJECT

public:
    EmailSender(const QString &from, const QString &to, const QString &subject, const QString &body,
                const QString &smtpServer = "smtp.gmail.com", int port = 465);
    void sendMail();

private slots:
    void onConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QSslSocket *socket;
    QTextStream stream;
    QString from;
    QString to;
    QString subject;
    QString body;
    QString smtpServer;
    int port;
    QString appPassword ;
    bool authenticated = false;

    void sendCommand(const QString &cmd);
};

#endif // EMAILSENDER_H
