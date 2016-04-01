#include "kosclient.h"
#include <QDataStream>
#include <QCryptographicHash>

KOSClient::KOSClient(qintptr ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
    this->blockSize = 0;
}

void KOSClient::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void KOSClient::readyRead()
{
    QDataStream in(socket);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;

    qint8 packet;
    in >> packet;

    parsePacket(packet, in);

    // get the information
    //QByteArray Data = socket->readAll();
    /*QByteArray Data = socket->readAll();

    QDataStream dataStream(Data);
    qint8 packet;
    dataStream >> packet;

    parsePacket(packet, dataStream);

    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << packet;

    socket->write(Data);*/
}

void KOSClient::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}

void KOSClient::parsePacket(qint8 packet, QDataStream &dataStream){
    switch(packet){
        //Authenthication packet
        case 0x01:{
            QString authenthication;
            dataStream >> authenthication;
            if(authenthication.compare(QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Sha3_256).toBase64())) == 0)
                qDebug() << "test";
            break;
        }
    }
}
