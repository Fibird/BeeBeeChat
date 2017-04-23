#include "mainwindow.h"
#include "sender.h"
#include "receiver.h"
#include "logindialog.h"
#include <QApplication>

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
        //String userName =
        MainWindow w(0, brokerURI, "fibird", 0, useTopic, sessionTransacted);
        w.show();
        //LoginDialog lgDlg;

        //lgDlg.show();
        // Start the consumer thread
        //Thread consumerThread(&consumer);
        //consumerThread.start();

        // Wait for the consumer to indicate that its ready to go.
        //consumer.waitUntilReady();

        // Start the producer thread.
        //Thread producerThread(&producer);
        //producerThread.start();
        //producer.sendMessage("Hello!");

        // Wait for the threads to complete
        //producerThread.join();
        //consumerThread.join();

        //long long endTime = System::currentTimeMillis();
        //double totalTime = (double)(endTime - startTime) / 1000.0;

        //consumer.close();
        //producer.close();
        return a.exec();
    } 
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
