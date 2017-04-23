#include "logindialog.h"
#include "ui_logindialog.h"
#include <QString>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    dlgUi(new Ui::LoginDialog)
{
    dlgUi->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete dlgUi;
}

std::string LoginDialog::getUserName()
{
    QString qs = dlgUi->nicknamelineEdit->text();
    return qs.toStdString();
}


