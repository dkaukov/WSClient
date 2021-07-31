#include "client.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.init();

    //client.sendMsg1();

    QObject::connect(&client, &Client::failed, &a, [&a]{ a.exit(1); });

    return a.exec();

}
