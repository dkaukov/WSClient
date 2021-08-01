#pragma once

#include <WebSocket.h>

#include <QTcpSocket>
#include <QDebug>
#include <QThread>
#include <QMetaEnum>
#include <QAbstractSocket>
#include <QString>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void init();
    QString hostIP = "127.0.0.1";
    quint16 hostPort = 40001;
signals:
    void failed();

public slots:
    void sendMsg1();
    //void run(); // this is for multithread

private slots:

    void handshakeSucceed();
    void handshakeFailed(const QString & reason);
    void clientReadData();
    void tcpHandshakeError(QAbstractSocket::SocketError socketError);
    void error(QAbstractSocket::SocketError socketError);

private:
    WebSocket::Wrapper* ws_wrapper = nullptr;
    QTcpSocket tcp_socket;
};
