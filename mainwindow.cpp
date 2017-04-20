#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent, const std::string& brokerURI, int numMessages, bool useTopic, bool sessionTransacted, string nickname) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//,
    //sender(nickname, brokerURI, numMessages, useTopic, sessionTransacted),
    //receiver(brokerURI, numMessages, useTopic)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendBtn_clicked()
{
    QString qs = ui->msgSendTextEdit->toPlainText();
    if (!qs.isEmpty())
    {
        std::string msg = qs.toStdString();
        //sender.sendMessage("BeeBee.talk", msg);
    }
}
