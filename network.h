#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

class Network : public QObject
{
    Q_OBJECT

public:
    explicit Network();
    ~Network();

    void logIn(QString email, QString password);
    void getAllDrones(QString token);
    void getDetections(QString token, QString id);

    QJsonDocument getQJsonDocument();

public slots:
    void managerFinished();

signals:
    void managerGood();
    void managerBad();
    void managerFailed();


private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest networkRequest;
    QNetworkReply *reply;

    QJsonDocument documentReceive;
};

#endif // NETWORK_H
