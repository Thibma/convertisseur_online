#include "network.h"
static QString URL = "http://10.10.10.100:8000/";

Network::Network()
{
    networkAccessManager = new QNetworkAccessManager();
}

Network::~Network() {

}

// authentication/login
// Authentification au serveur
void Network::logIn(QString email, QString password) {
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject loginJson;
    loginJson.insert("email", QJsonValue::fromVariant(email));
    loginJson.insert("password", QJsonValue::fromVariant(password));
    QJsonDocument jsonDocument(loginJson);

    networkRequest.setUrl(QUrl(URL + "authentication/login"));

    reply = networkAccessManager->post(networkRequest, jsonDocument.toJson());
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinished()));
}

// detections
// Permet d'obtenir tous les drones de la bdd
void Network::getAllDrones(QString token) {
    networkRequest.setRawHeader(QByteArray("Authorization"), token.toUtf8());
    networkRequest.setUrl(QUrl(URL + "detections"));
    reply = networkAccessManager->get(networkRequest);
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinished()));
}

// dectection?detection_id="id"
// Permet d'avoir les détections d'un drone
void Network::getDetections(QString token, QString id) {
    networkRequest.setRawHeader(QByteArray("Authorization"), token.toUtf8());
    networkRequest.setUrl(QUrl(URL + "detection?detection_id=" + id));
    reply = networkAccessManager->get(networkRequest);
    connect(reply, SIGNAL(finished()), this, SLOT(managerFinished()));
}

// Lorsqu'une tâche est terminée
void Network::managerFinished() {
    disconnect(reply, SIGNAL(finished()), this, SLOT(managerFinished()));
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid()) {
        QString status = statusCode.toString();
        if (status == "200") {
            QByteArray array = reply->readAll();
            documentReceive = QJsonDocument::fromJson(array);
            emit managerGood();
        }
        else if (status == "400") {
            QMessageBox error;
            error.setText("Erreur de connexion.");
            error.setInformativeText(reply->errorString());
            error.setStandardButtons(QMessageBox::Ok);
            error.setDefaultButton(QMessageBox::Ok);
            error.setIcon(QMessageBox::Warning);
            error.exec();
            emit managerFailed();
        }
        else {
            emit managerBad();
        }
    }
}

// Récupère le retour
QJsonDocument Network::getQJsonDocument() {
    return documentReceive;
}
