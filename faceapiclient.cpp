#include "FaceAPIClient.h"

FaceAPIClient::FaceAPIClient(QObject *parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this))
{
    // Connexion du gestionnaire réseau à l'événement de fin de la requête
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &FaceAPIClient::onRequestFinished);
}

void FaceAPIClient::sendFaceRecognitionRequest(const QString &imageBase64)
{
    // URL de l'API de reconnaissance faciale (Remplacer par l'URL de l'API que vous utilisez)
    QUrl url("https://api.example.com/recognize_face");
    QNetworkRequest request(url);

    // Ajouter les en-têtes nécessaires (ex. pour l'authentification)
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer YOUR_API_KEY"); // Utiliser votre clé API

    // Créer le corps de la requête JSON
    QJsonObject json;
    json["image"] = imageBase64;  // Remplacer avec l'image encodée en base64

    QJsonDocument doc(json);  // Convertir le JSON en document

    // Envoyer la requête POST avec les données JSON
    m_networkManager->post(request, doc.toJson());
}

void FaceAPIClient::onRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Lire la réponse de l'API en JSON
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject jsonResponse = doc.object();

        // Exemple de traitement de la réponse de reconnaissance faciale
        // Adaptez cette partie en fonction de la réponse de l'API
        QString result = jsonResponse["recognized_face"].toString(); // Extrait l'information selon la structure de la réponse

        // Émettre le signal de fin de traitement avec le résultat
        emit recognitionCompleted(result);
    } else {
        // Gérer les erreurs en cas de problème avec la requête
        qDebug() << "Erreur lors de la requête: " << reply->errorString();
        emit recognitionCompleted("Erreur de reconnaissance");
    }

    reply->deleteLater(); // Supprimer l'objet reply une fois qu'il a été traité
}
