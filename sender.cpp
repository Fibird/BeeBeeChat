#include "sender.h"
#include <QDebug>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <memory>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;

Sender::Sender(const std::string &brokerURI, std::string qname, int numMessages, bool useTopic, bool sessionTransacted) :
    destination(NULL),
    numMessages(numMessages),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    brokerURI(brokerURI),
    queueName(qname)
{
}

bool Sender::createSession()
{
    try
    {
        // Create a ConnectionFactory
        std::auto_ptr<ConnectionFactory> connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
        // Create a Connection
        connection = connectionFactory->createConnection();
        connection->start();

        // Create a Session
        if (this->sessionTransacted)
        {
            session = connection->createSession(Session::SESSION_TRANSACTED);
        }
        else
        {
            session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
        }

        // Create a MessageProducer from the Session to the topic or queue
        producer = session->createProducer(destination);
        //producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        return true;
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
        return false;
    }
}

void Sender::close()
{
    this->cleanup();
}

void Sender::cleanup()
{
    if (connection != NULL)
    {
        try
        {
            connection->close();
        }
        catch (cms::CMSException& ex)
        {
            ex.printStackTrace();
        }
    }

    // Destroy resources.
    try
    {
        delete destination;
        destination = NULL;
        delete producer;
        producer = NULL;
        delete session;
        session = NULL;
        delete connection;
        connection = NULL;
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}

Sender::~Sender()
{
    cleanup();
}

void Sender::sendMessage(string queueOrTopic, std::string msg)
{
    try
    {
        // Create the destination (Topic or Queue)
        if (useTopic)
        {
            destination = session->createTopic(queueOrTopic);
        }
        else
        {
            destination = session->createQueue(queueOrTopic);
        }

        // Create a MessageProducer from the Session to the topic or queue
        producer = session->createProducer(destination);
        producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);

        std::auto_ptr<TextMessage> message(session->createTextMessage(msg));
        producer->send(message.get());
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}
