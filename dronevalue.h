#ifndef DRONEVALUE_H
#define DRONEVALUE_H

#include <QString>
#include <QDate>
#include <QGeoCoordinate>

class DroneValue {

public:
    DroneValue(double m_longitude, double m_latitude, double m_altitude, QDateTime m_date);
    QGeoCoordinate getCoordinates();
    QDateTime getDate();

private:
    double longitude;
    double latitude;
    double altitude;
    QDateTime date;
};

#endif // DRONEVALUE_H
