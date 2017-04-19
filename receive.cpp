#include "receive.h"

Receive::Receiver( string name, CmsTemplate* cmsTemplate ) :
    name(name), ready(1), isClosing(false), cmsTemplate(cmsTemplate), asyncReceiverThread(NULL) {

    asyncReceiverThread = new Thread( this, "AsyncReceiver" );
    asyncReceiverThread->start();

    waitUntilReady();
}
