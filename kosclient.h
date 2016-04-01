#ifndef KOSCLIENT_H
#define KOSCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class KOSClient : public QThread
{
    Q_OBJECT
public:
    explicit KOSClient(qintptr ID, QObject *parent = 0);

    void run();

    void parsePacket(qint8 packet, QDataStream &dataStream);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    quint16 blockSize;
};

#endif // KOSCLIENT_H
