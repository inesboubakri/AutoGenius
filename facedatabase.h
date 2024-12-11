#ifndef FACEDATA_H
#define FACEDATA_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QByteArray>

class FaceData {
    QString CIN;         // Identifiant unique de la personne
    QByteArray image;    // Données de l'image en BLOB

public:
    // Constructeurs
    FaceData() {}
    FaceData(QString cin, QByteArray img);

    // Getters
    QString getCIN() { return CIN; }
    QByteArray getImage() { return image; }

    // Setters
    void setCIN(QString cin) { CIN = cin; }
    void setImage(QByteArray img) { image = img; }

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString cin);
    QByteArray chercherImage(QString cin);
};

#endif // FACEDATA_H
