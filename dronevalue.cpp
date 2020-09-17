#include "dronevalue.h"

DroneValue::DroneValue(double m_longitude, double m_latitude, double m_altitude, QDateTime m_date)
{
    longitude = m_longitude;
    latitude = m_latitude;
    altitude = m_altitude;
    date = m_date;
}

QGeoCoordinate DroneValue::getCoordinates()
{
    return QGeoCoordinate (latitude, longitude, altitude);
}

QDateTime DroneValue::getDate()
{
    return date;
}
