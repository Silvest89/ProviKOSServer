#include "kosserver.h"
#include "kosclient.h"

KOSServer::KOSServer(QObject *parent) :
    QTcpServer(parent)
{

}

void KOSServer::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

void KOSServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    KOSClient *thread = new KOSClient(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
