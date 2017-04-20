#include "logindialog.h"
#include "ui_logindialog.h"

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
