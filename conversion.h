#ifndef CONVERSION_H
#define CONVERSION_H

#include <QVector>
#include <QFileDialog>

#include "drone.h"

class Conversion
{
public:
    Conversion(QVector<Drone *> listDrone);

private:
    QVector<Drone *> drones;
    QString fileName;
    QString file;

    void miseEnPage();
    void save();

};

#endif // CONVERSION_H
