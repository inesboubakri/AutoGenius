#include "faceid.h"

// Définition du réseau de reconnaissance faciale
template <template <typename> class BLOCK, int N, typename SUBNET>
using residual = dlib::add_prev1<dlib::block<BLOCK, N, SUBNET>>;

template <template <typename> class BLOCK, int N, typename SUBNET>
using residual_down = dlib::add_prev2<dlib::block<BLOCK, N, dlib::downsample<SUBNET>>>;

template <int N, typename SUBNET>
using block = dlib::con<dlib::relu<dlib::con<N, 3, 3, 1, 1, SUBNET>>>;

template <typename SUBNET>
using ares = residual<block, 8, SUBNET>;

template <typename SUBNET>
using ares_down = residual_down<block, 16, SUBNET>;

using net_type = dlib::loss_metric<dlib::fc<128, ares_down<ares_down<ares<ares_down<dlib::input_rgb_image_sized<150>>>>>>>>;

// Constructeur
FaceID::FaceID(const QString& modelPath)
    : m_modelPath(modelPath) {}

// Générer les embeddings faciaux à partir d'une image
QString FaceID::genererEmbeddings(const QString& imagePath) {
    try {
        // Charger l'image
        dlib::matrix<dlib::rgb_pixel> img;
        dlib::load_image(img, imagePath.toStdString());

        // Charger le modèle Dlib
        net_type net;
        dlib::deserialize(m_modelPath.toStdString()) >> net;

        // Détecter le visage
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
        std::vector<dlib::rectangle> faces = detector(img);

        if (faces.empty()) {
            qDebug() << "Aucun visage détecté.";
            return "";
        }

        // Extraire les caractéristiques faciales
        dlib::matrix<dlib::rgb_pixel> face_chip;
        dlib::extract_image_chip(img, dlib::get_face_chip_details(faces[0]), face_chip);
        std::vector<dlib::matrix<float, 0, 1>> face_descriptor = net(face_chip);

        // Convertir les embeddings en une chaîne de caractères
        QString faceData;
        for (float value : face_descriptor[0])
            faceData += QString::number(value) + ",";

        faceData.chop(1); // Supprimer la dernière virgule
        return faceData;

    } catch (const std::exception& e) {
        qDebug() << "Erreur lors de la génération des embeddings :" << e.what();
        return "";
    }
}

// Enregistrer les données faciales dans la base de données
bool FaceID::enregistrerFace(int cin_employee, const QString& imagePath) {
    QString faceData = genererEmbeddings(imagePath);
    if (faceData.isEmpty()) {
        qDebug() << "Impossible de générer les embeddings.";
        return false;
    }

    // Utiliser la connexion existante à la base de données
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE_FACE_DATA (CIN_EMPLOYEE, FACE_DATA) "
                  "VALUES (:cin_employee, :face_data) "
                  "ON CONFLICT (CIN_EMPLOYEE) DO UPDATE SET FACE_DATA = :face_data");
    query.bindValue(":cin_employee", cin_employee);
    query.bindValue(":face_data", faceData);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion dans la base de données :" << query.lastError().text();
        return false;
    }

    qDebug() << "Face ID enregistré avec succès dans la base de données.";
    return true;
}
