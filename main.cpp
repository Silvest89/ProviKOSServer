#include <QCoreApplication>
#include "kosserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KOSServer server;
    server.startServer();

    return a.exec();
}
