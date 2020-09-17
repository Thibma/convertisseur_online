#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMimeData>
#include <QListWidgetItem>
#include <QGeoCodingManager>
#include <QGeoServiceProvider>
#include <QGeoAddress>

#include "drone.h"
#include "network.h"
#include "conversion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString token, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void droneOK();
    void selectedDate();
    void addDrone();
    void deleteDrone();
    void itemChange(QListWidgetItem *item);
    void itemSelectedChange(QListWidgetItem *item);
    void geoFinished();
    void convertFile();

private:
    void displayList(Drone *drone);
    void displayInformation(Drone *drone);

    Ui::MainWindow *ui;

    Network *network;

    QVector<Drone *> totalDrone;
    QVector<Drone *> listDrone;
    QVector<Drone *> selectedDrone;

    QVector<QDate> listDates;

    QString token;

    Drone *droneTemp;
    QGeoCodeReply *geoResponse;
};
#endif // MAINWINDOW_H
