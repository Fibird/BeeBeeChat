#include "mainwindow.h"
#include "sender.h"
#include "receiver.h"
#include "logindialog.h"
#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    activemq::library::ActiveMQCPP::initializeLibrary();
    {
        QApplication a(argc, argv);
        std::string brokerURI = "failover:(tcp://localhost:61616)";
        //============================================================
        // set to true to use topics instead of queues
        // Note in the code above that this causes createTopic or
        // createQueue to be used in both consumer an producer.
        //============================================================
        bool useTopic = false;
        bool sessionTransacted = false;
        std::string userName;
        MainWindow *w;
        Thread *consumerThread;
        LoginDialog lgDlg;
        lgDlg.show();
        if (lgDlg.exec() == QDialog::Accepted)
        {
            userName = lgDlg.getUserName();
            if (userName != "")
            {
                w = new MainWindow(0, brokerURI, userName, 0, useTopic, sessionTransacted);
                w->createSession();
                w->show();
                // create connection with activemq and create a session
                consumerThread = new Thread(&w->receiver);
                consumerThread->start();
            }
            else
            {
                QMessageBox::information(&lgDlg, QObject::tr("info"), QObject::tr("User name can't be null!"));
            }
        }
        consumerThread->join();
        return a.exec();
    } 
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
