#ifndef FACEAPICLIENT_H
#define FACEAPICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class FaceAPIClient : public QObject
{
    Q_OBJECT

public:
    explicit FaceAPIClient(QObject *parent = nullptr);
    void sendFaceRecognitionRequest(const QString &imageBase64); // Envoie la requête pour la reconnaissance faciale

signals:
    void recognitionCompleted(const QString &result); // Signal émis quand la reconnaissance est terminée

private slots:
    void onRequestFinished(QNetworkReply *reply); // Slot pour traiter la réponse de l'API

private:
    QNetworkAccessManager *m_networkManager; // Gestionnaire des requêtes réseau
};

#endif // FACEAPICLIENT_H
