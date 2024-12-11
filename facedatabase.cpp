#include "facedatabase.h"
#include <QSqlError>
#include <QDebug>

// Constructeur
FaceData::FaceData(QString cin, QByteArray img) {
    CIN = cin;
    image = img;
}

// Ajouter une nouvelle entrée
bool FaceData::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO FACEDATA (CIN, IMAGE) VALUES (:cin, :image)");
    query.bindValue(":cin", CIN);
    query.bindValue(":image", image);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de données de visage:" << query.lastError().text();
        return false;
    }
    return true;
}

// Afficher toutes les données
QSqlQueryModel* FaceData::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN FROM FACEDATA");  // Seuls les CIN sont affichés
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}

// Supprimer une entrée par CIN
bool FaceData::supprimer(QString cin) {
    QSqlQuery query;
    query.prepare("DELETE FROM FACEDATA WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des données de visage:" << query.lastError().text();
        return false;
    }
    return true;
}

// Chercher une image par CIN
QByteArray FaceData::chercherImage(QString cin) {
    QSqlQuery query;
    query.prepare("SELECT IMAGE FROM FACEDATA WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        return query.value(0).toByteArray();  // Retourne les données de l'image en BLOB
    } else {
        qDebug() << "Erreur lors de la récupération de l'image:" << query.lastError().text();
        return QByteArray();
    }
}
