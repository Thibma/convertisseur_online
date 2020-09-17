#include "drone.h"

Drone::Drone(QString m_id, QString m_sn, QString m_model, QDateTime m_firstFly, QString token)
{
    id = m_id;
    sn = m_sn;
    model = m_model;
    firstFlyDate = m_firstFly;

    network = new Network;
    network->getDetections(token, id);

    connect(network, SIGNAL(managerGood()), this, SLOT(accepted()));
}

Drone::~Drone() {

}

QString Drone::getSn() {
    return sn;
}

QString Drone::getModel() {
    return model;
}

QDateTime Drone::getFirstDate() {
    return firstFlyDate;
}

QDateTime Drone::getLastDate()
{
    return droneValue.last().getDate();
}

QGeoCoordinate Drone::getFirstCoordinates()
{
    return droneValue[0].getCoordinates();
}

QGeoCoordinate Drone::getLastCoordinates()
{
    return droneValue.last().getCoordinates();
}

QVector<DroneValue> Drone::getDroneValue()
{
    return droneValue;
}

void Drone::accepted() {
    QJsonDocument jsonDocument = network->getQJsonDocument();
    QJsonObject jsonObject = jsonDocument.object();
    QJsonArray jsonArray = jsonObject["logs"].toArray();
    foreach (const QJsonValue &v, jsonArray) {
        QJsonObject object = v.toObject();
        QJsonObject location = object["location"].toObject();
        QJsonArray coordinates = location["coordinates"].toArray();
        double longitude = coordinates.at(0).toDouble();
        double latitude = coordinates.at(1).toDouble();
        double height = object["absoluteHeight"].toDouble();
        QString dateStr = object["lastDronePushUpdateTime"].toString();
        QDateTime formatDate = QDateTime::fromString(dateStr, "yyyy-MM-ddThh:mm:ss.zzzZ");
        DroneValue droneV(longitude, latitude, height, formatDate);
        droneValue.append(droneV);
    }
}
