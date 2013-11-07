#import <QDebug>

#include "osclistenercontroller.h"

OscListenerController::OscListenerController(int port)
    : port(port)
{
    workerThread = new QThread;
    worker = new OscListenerWorker(port);
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(Start()));
    connect(worker, SIGNAL(messageReceived(OscMessageContainer*)), this, SLOT(handleMessage(OscMessageContainer*)));

    running = false;
}

int OscListenerController::Port()
{
    return port;
}

void OscListenerController::Start()
{
    if (!running) {
        workerThread->start();
        running = true;
    }
}

void OscListenerController::Stop()
{
    if (running) {
        worker->Stop();
        workerThread->quit();
        workerThread->wait();
        running = false;
    }
}

void OscListenerController::handleMessage(OscMessageContainer *msg)
{
    emit messageReceived(msg);
}