#include "loginform.h"
#include "ui_loginform.h"

#include "mainwindow.h"


LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    network = new Network();
    connect(network, SIGNAL(managerGood()), this, SLOT(connexionAccepted()));
    connect(network, SIGNAL(managerBad()), this, SLOT(connexionRefused()));
    connect(network, SIGNAL(managerFailed()), this, SLOT(connexionFailed()));
    connect(ui->passwordLineEdit, SIGNAL(returnPressed()), ui->connexionButton, SIGNAL(clicked()));
    connect(ui->connexionButton, SIGNAL(clicked()), this, SLOT(connexionButton()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::connexionButton() {
    if (ui->emailLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty()) {
        ui->labelConnexion->setText("Email ou mot de passe vide");
    }
    else {
        ui->labelConnexion->setText("Connexion en cours...");
        this->setCursor(Qt::WaitCursor);
        network->logIn(ui->emailLineEdit->text(), ui->passwordLineEdit->text());
    }
}

void LoginForm::connexionAccepted() {
    this->hide();
    QJsonDocument getDocument = network->getQJsonDocument();
    QJsonObject getObject = getDocument.object();
    QString token = getObject["token"].toString();
    MainWindow *mainWindow = new MainWindow(token);
    mainWindow->show();
    delete network;
}

void LoginForm::connexionRefused() {
    this->setCursor(Qt::ArrowCursor);
    ui->labelConnexion->setText("Login ou mot de passe incorrect");
}

void LoginForm::connexionFailed() {
    this->setCursor(Qt::ArrowCursor);
    ui->labelConnexion->setText("Erreur de connexion avec le serveur");
}
