#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sender.h"
#include "receiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, const std::string& brokerURI = "failover:(tcp://localhost:61616)", std::string nickname = "Fibird",
                        int numMessages = 0, bool useTopic = false, bool sessionTransacted = false);
    ~MainWindow();
private slots:
    void on_sendBtn_clicked();
    void on_addContactBtn_clicked();

private:
    Ui::MainWindow *ui;
public:
    Sender sender;
    Receiver receiver;
public:
    bool createSession();
    std::string getReceiver();
    void showMessage(const QString &msg);
};

#endif // MAINWINDOW_H
