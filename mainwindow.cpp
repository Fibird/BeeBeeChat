#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>

MainWindow::MainWindow(QWidget *parent, const std::string& brokerURI, string nickname, int numMessages, bool useTopic, bool sessionTransacted) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sender(brokerURI, nickname, numMessages, useTopic, sessionTransacted),
    receiver(brokerURI, nickname, numMessages, useTopic)
{
    ui->setupUi(this);
    connect(&receiver, &Receiver::showMessage, this, &MainWindow::showMessage);
    QString qnn = QString::fromStdString(nickname);
    QTableWidgetItem *cnt = new QTableWidgetItem(qnn);
    QTableWidgetItem *sts = new QTableWidgetItem("Online");
    ui->contactList->insertRow(0);
    ui->contactList->setItem(0, 0, cnt);
    ui->contactList->setItem(0, 1, sts);
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
    std::string rn = getReceiver();
    std::string msg;
    if (!qs.isEmpty())
    {       
        msg = qs.toStdString();
        sender.sendMessage(rn, msg);
        ui->msgSendTextEdit->clear();
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-ddhh:mm:ss");
        ui->MsgReceiveTextBrowser->setTextColor(Qt::blue);
        ui->MsgReceiveTextBrowser->append("<li>[ Me ]" + time + "</li>");
        ui->MsgReceiveTextBrowser->append("<li><i>" + qs + "</i></li>");
        ui->MsgReceiveTextBrowser->append("\n");
    }
    else
    {
        QMessageBox::information(this, tr("info"), tr("Message can't be null!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void MainWindow::showMessage(const QString& msg)
{
    std::string rn = getReceiver();
    QString qrn = QString::fromStdString(rn);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-ddhh:mm:ss");
    ui->MsgReceiveTextBrowser->setTextColor(Qt::red);
    ui->MsgReceiveTextBrowser->append("<li>[ " + qrn + " ]" + time+ "</li>");
    ui->MsgReceiveTextBrowser->append("<li>" + msg + "</li>");
    ui->MsgReceiveTextBrowser->append("\n");
}

std::string MainWindow::getReceiver()
{
    int row = ui->contactList->currentColumn();
    if (row < 0)
    {
        row = 0;
    }
    QString rn = ui->contactList->item(row, 0)->text();
    return rn.toStdString();
}

void MainWindow::on_addContactBtn_clicked()
{
    bool ok;
    QString CntName = QInputDialog::getText(this, tr("Add Contact"),
                                            tr("Name:"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);
    if (ok && !CntName.isEmpty())
    {
        QTableWidgetItem *cnt = new QTableWidgetItem(CntName);
        QTableWidgetItem *sts = new QTableWidgetItem("Online");
        ui->contactList->insertRow(0);
        ui->contactList->setItem(0, 0, cnt);
        ui->contactList->setItem(0, 1, sts);
    }
}
