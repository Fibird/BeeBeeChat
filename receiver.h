#ifndef RECEIVER_H
#define RECEIVER_H
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <QObject>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;

class Receiver : public QObject,
                 public Runnable,
                 public ExceptionListener,
                 public MessageListener
{
    Q_OBJECT
private:
    CountDownLatch latch;
    CountDownLatch doneLatch;
    Connection* connection;
    Session* session;
    Destination* destination;
    MessageConsumer* consumer;
    long waitMillis;
    bool useTopic;
    bool sessionTransacted;
    std::string brokerURI;
    std::string userName;
private:
    Receiver(const Receiver&);
    Receiver& operator =(const Receiver&);
public:
    Receiver(const std::string& brokerURI, std::string userName, int numMessages, bool useTopic = false,
             bool sessionTransacted = false, int waitMillis = 30000, QObject *parent = 0);
    virtual ~Receiver();
    void close();
    void waitUntilReady();
    virtual void run();
    virtual void onMessage(const Message *message);
    virtual void onException(const CMSException &ex);
private:
    void cleanup();
signals:
    void showMessage(std::string& msg);
};

#endif // RECEIVER_H
