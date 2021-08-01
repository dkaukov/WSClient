#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "client deconstructed";
}

void Client::init()
{
    qInfo() << "starting Init";

    // create the to-be-wrapped socket (this is the real socket)
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, [this, socket]
    {
        // create the socket wrapper
        ws_wrapper = new WebSocket::Wrapper(socket, this);
        // 'socket' is now reparented to 'ws_wrapper', and 'ws_wrapper' wraps 'socket'.
        // (do not use 'socket' directly anymore, instead use 'ws_wrapper').

        // We start the handshake process below via local void
        connect(ws_wrapper, &WebSocket::Wrapper::handshakeFinished, this, &Client::handshakeSucceed);
        // At this point the conneciton is "speaking" the web socket
        // save the active socket here and use it...
        // You can call ws_wrapper->write(), to send
        // Use the `messagesReady()` or `readyReady()` signal to receive

        // Handling the Failure and Disconned below
        connect(ws_wrapper, &WebSocket::Wrapper::handshakeFailed, this, &Client::handshakeFailed);
        connect(ws_wrapper, &WebSocket::Wrapper::disconnected, this, &Client::failed);
        connect(ws_wrapper,&QTcpSocket::errorOccurred,this, &Client::tcpHandshakeError);

        // Reading data from ws server
        connect(ws_wrapper, &WebSocket::Wrapper::messagesReady, this ,&Client::clientReadData);
        auto res = ws_wrapper->startClientHandshake("/", "localhost");
        if (!res) ws_wrapper->deleteLater();
    });
    connect(socket, &QTcpSocket::disconnected, this, &Client::failed);

    socket->connectToHost(hostIP, hostPort);
    //socket->connectToHost("127.0.0.1", 40001);
}

void Client::handshakeSucceed()
{
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qDebug() << "ws connected";
    // sends below config message immediately after handshake
    const QString msg  = QString("volume:-5;");
    ws_wrapper->write(msg.toUtf8());

    // seems like I need to create while loop here for further config messages
    // something like
    //while (&WebSocket::Wrapper::connected){
    //
    //}
}

void Client::handshakeFailed(const QString & reason)
{
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qDebug() << "ws error: " << reason;
    emit failed();
}

void Client::tcpHandshakeError(QAbstractSocket::SocketError socketError)
{
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    qInfo() << "Error:" << socketError << " " << ws_wrapper->errorString();
    emit failed();
}

void Client::clientReadData()
{
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    while (ws_wrapper->messagesAvailable() > 0) {
        auto msg = ws_wrapper->readNextMessage();
        qDebug() << "Msg received:" << QString::fromUtf8(msg);
    }
}

void Client::sendMsg1(){
    qInfo() << Q_FUNC_INFO << QThread::currentThread();
    const QString msg  = QString("volume:-10;");
    ws_wrapper->write(msg.toUtf8());
}

//void Client::run()
//{
//    //Thread is running the code here.
//}
