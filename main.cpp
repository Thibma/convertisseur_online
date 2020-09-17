#include "mainwindow.h"
#include "loginform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm loginform;
    loginform.setWindowTitle("Convertisseur Aéroscope - KML Online");
    loginform.show();
    return a.exec();
}
