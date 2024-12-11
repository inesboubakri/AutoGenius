#ifndef MAILER_H
#define MAILER_H
#include <QString>

class mailer
{
public:
    mailer();
    mailer(QString, QString, QString);

    static int sendEmail(QString,QString,QString);
private:
    QString destinataire;
    QString object,body;
};

#endif // MAILER_H
