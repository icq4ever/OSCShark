#include "osclistenerworker.h"
#include "osclistener.h"

OscListenerWorker::OscListenerWorker(int port)
    : port(port)
{
    OscListener listener;
    receiveSocket = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, this->port),
                                                  &listener);

    connect(&listener, SIGNAL(messageReceived()), this, SLOT(onMessageReceived()));
}

void OscListenerWorker::doWork()
{
    // TODO
    receiveSocket->Run();
}