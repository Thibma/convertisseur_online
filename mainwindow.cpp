#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MainWindow::MainWindow(QString m_token, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->droneSelectedList->setAcceptDrops(true);
    this->setEnabled(false);
    this->setCursor(Qt::WaitCursor);

    token = m_token;

    network = new Network;
    network->getAllDrones(token);

    connect(network, SIGNAL(managerGood()), this, SLOT(droneOK()));
    //connect(network, SIGNAL(managerBad()), this, SLOT(connexionRefused()));
    //connect(network, SIGNAL(managerFailed()), this, SLOT(connexionFailed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::droneOK() {
    QJsonDocument jsonDocument = network->getQJsonDocument();
    QJsonArray jsonArray = jsonDocument.array();
    foreach (const QJsonValue &v, jsonArray) {
        QJsonObject object = v.toObject();
        QString model = object.value("productType").toArray().at(0).toString();
        QString id = object.value("_id").toString();
        QString sn = object.value("sn").toString();
        QString dateStr = object.value("flightStartTime").toString();
        QDateTime formatDate = QDateTime::fromString(dateStr, "yyyy-MM-ddThh:mm:ss.zzzZ");
        QDate date = formatDate.date();
        Drone *drone = new Drone(id, sn, model, formatDate, token);
        totalDrone.append(drone);
        listDates.append(date);
    }
    ui->calendarWidget->setDates(listDates);
    ui->calendarWidget->update();
    this->setCursor(Qt::ArrowCursor);
    this->setEnabled(true);

    connect(ui->addDroneButton, SIGNAL(clicked()), this, SLOT(addDrone()));
    connect(ui->deleteDroneButton, SIGNAL(clicked()), this, SLOT(deleteDrone()));
    connect(ui->convertButton, SIGNAL(clicked()), this, SLOT(convertFile()));
    connect(ui->droneList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemChange(QListWidgetItem *)));
    connect(ui->droneSelectedList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemSelectedChange(QListWidgetItem *)));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(selectedDate()));
    ui->deleteDroneButton->setEnabled(false);
    ui->convertButton->setEnabled(false);
    selectedDate();
}

void MainWindow::selectedDate()
{
    ui->droneList->clear();
    ui->informationListWidget->clear();
    listDrone.clear();
    for (int i = 0; i < totalDrone.size(); i++) {
        if (totalDrone[i]->getFirstDate().date() == ui->calendarWidget->selectedDate()) {
            listDrone.append(totalDrone[i]);
            displayList(totalDrone[i]);
        }
    }
    if (listDrone.size() == 0) {
        ui->addDroneButton->setEnabled(false);
    }
}

void MainWindow::addDrone()
{
    ui->convertButton->setEnabled(true);
    if (selectedDrone.contains(listDrone[ui->droneList->currentRow()])) {
        return;
    }
    else {
        selectedDrone.append(listDrone[ui->droneList->currentRow()]);
        ui->droneSelectedList->addItem(ui->droneList->currentItem()->text());
    }
}

void MainWindow::deleteDrone()
{
    selectedDrone.remove(ui->droneSelectedList->currentRow());
    delete ui->droneSelectedList->takeItem(ui->droneSelectedList->currentRow());
    if (selectedDrone.size() == 0) {
        ui->deleteDroneButton->setEnabled(false);
        ui->convertButton->setEnabled(false);
    }
}

void MainWindow::itemChange(QListWidgetItem *item)
{
    ui->addDroneButton->setEnabled(true);
    displayInformation(listDrone[ui->droneList->currentRow()]);
}

void MainWindow::itemSelectedChange(QListWidgetItem *item)
{
    ui->deleteDroneButton->setEnabled(true);
    displayInformation(selectedDrone[ui->droneSelectedList->currentRow()]);
}

void MainWindow::displayList(Drone *drone) {
    ui->droneList->addItem(drone->getSn() + " - " + drone->getModel() + " à " + drone->getFirstDate().time().toString());
}

void MainWindow::displayInformation(Drone *drone)
{
    droneTemp = drone;
    QMap<QString,QVariant> params;
    params["osm.geocoding.host"] = "https://nominatim.openstreetmap.org";
    QGeoServiceProvider *geoSrv = new QGeoServiceProvider("osm", params);
    QGeoCodingManager *geoCoder = geoSrv->geocodingManager();
    geoResponse = geoCoder->reverseGeocode(droneTemp->getFirstCoordinates());
    connect(geoResponse, SIGNAL(finished()), this, SLOT(geoFinished()));
}

void MainWindow::geoFinished()
{
    ui->informationListWidget->clear();
    disconnect(geoResponse);
    ui->informationListWidget->addItem("ID : " + droneTemp->getSn());
    ui->informationListWidget->addItem("Modèle : " + droneTemp->getModel());
    ui->informationListWidget->addItem("Date de début de vol : " + droneTemp->getFirstDate().toString());
    qDebug() << geoResponse->locations().at(0).address().text();
    if (geoResponse->locations().at(0).address().city() == "") {
        ui->informationListWidget->addItem("Lieu du vol : Inconnu (coordonnées 0.0)");
    }
    else {
        ui->informationListWidget->addItem("Lieu du vol : " + geoResponse->locations().at(0).address().city());
    }
}

void MainWindow::convertFile()
{
    //this->setCursor(Qt::WaitCursor);
    Conversion *convertion = new Conversion(selectedDrone);
    //delete convertion;
}
