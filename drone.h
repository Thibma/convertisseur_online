#ifndef DRONE_H
#define DRONE_H

#include <QString>
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QGeoCoordinate>

#include "dronevalue.h"
#include "network.h"

class Drone : public QObject {

    Q_OBJECT

public:
    Drone(QString m_id, QString m_sn, QString m_model, QDateTime m_firstFly, QString token);
    ~Drone();

    QString getSn();
    QString getModel();
    QDateTime getFirstDate();
    QDateTime getLastDate();
    QGeoCoordinate getFirstCoordinates();
    QGeoCoordinate getLastCoordinates();
    QVector <DroneValue> getDroneValue();

private slots:
    void accepted();

private:
    QString id;
    QString sn;
    QString model;
    QDateTime firstFlyDate;
    QVector<DroneValue> droneValue;

    Network *network;

    //Q_DISABLE_COPY(Drone)
};

#endif // DRONE_H
