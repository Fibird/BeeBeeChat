#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent, const std::string& brokerURI, string nickname, int numMessages, bool useTopic, bool sessionTransacted) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sender(brokerURI, nickname, numMessages, useTopic, sessionTransacted),
    receiver(brokerURI, nickname, numMessages, useTopic)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::createSession()
{
    return sender.createSession();
}

void MainWindow::on_sendBtn_clicked()
{
    QString qs = ui->msgSendTextEdit->toPlainText();
    if (!qs.isEmpty())
    {
        std::string msg = qs.toStdString();
        sender.sendMessage("fibird", msg);
    }
}

