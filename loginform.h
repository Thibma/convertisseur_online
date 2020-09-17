#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

#include "network.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

public slots:
    void connexionButton();
    void connexionAccepted();
    void connexionRefused();
    void connexionFailed();

private:
    Ui::LoginForm *ui;
    Network *network;
};

#endif // LOGINFORM_H
