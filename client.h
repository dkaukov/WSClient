#pragma once

#include <WebSocket.h>

#include <QTcpSocket>
#include <QDebug>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void init();
    QString hostIP = "127.0.0.1";
    int hostPort = 40001;
signals:
    void failed();

public slots:
    void sendMsg1();

private slots:

    void handshakeSucceed();
    void handshakeFailed(const QString & reason);
    void clientReadData();

private:
    WebSocket::Wrapper *ws_wrapper = nullptr;
};
