#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include "logger.h"
#include "client.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "Log File location:" << Logger::filename;
    Logger::attach(); // turns ON logging
    //Logger::logging = false; // turns OFF logging
    //Logger::logging = true; // turns logging back ON


    QThread::currentThread()->setObjectName("Main thread");

    // --- for potenrial future use for multithreading ---
    //QThread thread;
    //thread.setObjectName("Client thread");
    //Client* client = new Client;
    //client->moveToThread(&thread);
    //thread.start();
    //client->init();

    Client client;
    client.init();
    //client.sendMsg1(); // <<< crashes app when uncommented

    //QObject::connect(&client, &Client::failed, &a, [&a]{ a.exit(1); });

    return a.exec();

}
