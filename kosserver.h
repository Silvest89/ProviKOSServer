#ifndef KOSSERVER_H
#define KOSSERVER_H

#include <QTcpServer>
#include "kosclient.h"

class KOSServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit KOSServer(QObject *parent = 0);
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // KOSSERVER_H
