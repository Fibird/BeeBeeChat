#include "receiver.h"

Receiver::Receiver(const std::string& brokerURI, int numMessages, bool useTopic, bool sessionTransacted, int waitMillis) :
    latch(1),
    doneLatch(numMessages),
    connection(NULL),
    session(NULL),
    destination(NULL),
    consumer(NULL),
    waitMillis(waitMillis),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    brokerURI(brokerURI)
{
}

Receiver::~Receiver()
{
    cleanup();
}

void Receiver::close()
{
    this->cleanup();
}

void Receiver::waitUntilReady()
{
    latch.await();
}

void Receiver::run()
{
    try
    {
        // Create a ConnectionFactory
        std::auto_ptr<ConnectionFactory> connectionFactory(
                    ConnectionFactory::createCMSConnectionFactory(brokerURI));

        // Create a Connection
        connection = connectionFactory->createConnection();
        connection->start();
        connection->setExceptionListener(this);

        // Create a Session
        if (this->sessionTransacted == true)
        {
            session = connection->createSession(Session::SESSION_TRANSACTED);
        } else
        {
            session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
        }

        // Create the destination (Topic or Queue)
        if (useTopic)
        {
            destination = session->createTopic("BeeBee.talk");
        }
        else
        {
            destination = session->createQueue("BeeBee.talk");
        }

        // Create a MessageConsumer from the Session to the Topic or Queue
        consumer = session->createConsumer(destination);

        consumer->setMessageListener(this);

        std::cout.flush();
        std::cerr.flush();

        // Indicate we are ready for messages.
        latch.countDown();

        // Wait while asynchronous messages come in.
        doneLatch.await(waitMillis);

    } catch (CMSException& e)
    {
        // Indicate we are ready for messages.
        latch.countDown();
        e.printStackTrace();
    }
}

void Receiver::onMessage(const Message *message)
{
    static int count = 0;

    try
    {
        count++;
        const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
        std::string text = "";

        if (textMessage != NULL)
        {
            text = textMessage->getText();
        }
        else
        {
            text = "NOT A TEXTMESSAGE!";
        }

        printf("Message #%d Received: %s\n", count, text.c_str());

    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }

    // Commit all messages.
    if (this->sessionTransacted)
    {
        session->commit();
    }

    // No matter what, tag the count down latch until done.
    doneLatch.countDown();
}

void Receiver::onException(const CMSException &ex)
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}

void Receiver::cleanup()
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
        delete consumer;
        consumer = NULL;
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

