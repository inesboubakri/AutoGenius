#ifndef FACEID_H
#define FACEID_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class FaceID {
public:
    FaceID(const QString& modelPath);

    // Méthodes
    bool enregistrerFace(int cin_employee, const QString& imagePath);
    QString genererEmbeddings(const QString& imagePath);

private:
    QString m_modelPath; // Chemin vers le modèle OpenCV
    cv::Ptr<cv::face::FaceRecognizer> m_recognizer; // Utilisation d'un reconnaisseur de visages OpenCV
};

#endif // FACEID_H
