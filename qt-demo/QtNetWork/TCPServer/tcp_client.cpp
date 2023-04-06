#include "tcp_client.h"

TCPClient::TCPClient(QObject *parent):QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

void TCPClient::slotDataReceived()
{
    while (bytesAvailable() > 0) {
        qint64 len = bytesAvailable();
        char buf[1024] = {0};
        read(buf, len);
        QString msg = buf;
        emit sigUpdateClients(msg, len);
    }
}

void TCPClient::slotDisconnected()
{
    emit sigDisconnected(this->socketDescriptor());
}
