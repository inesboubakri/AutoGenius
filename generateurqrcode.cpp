#include "generateurqrcode.h"
#include <QPainter>
#include <QrCodeGenerator.h>
GenerateurQRCode::GenerateurQRCode()
{

}


QImage GenerateurQRCode::genererCodeQR(const QString &donnees)
{
    using namespace qrcodegen;

    QrCodeGenerator generator;
    QImage qrCodeImage = generator.generateQr(donnees,200);
    return qrCodeImage;}
