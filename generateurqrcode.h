#ifndef GENERATEURQRCODE_H
#define GENERATEURQRCODE_H
#include <QrCodeGenerator.h>
#include <QImage>

class GenerateurQRCode
{
public:
    GenerateurQRCode();
    QImage genererCodeQR(const QString &donnees);
};

#endif // GENERATEURQRCODE_H
