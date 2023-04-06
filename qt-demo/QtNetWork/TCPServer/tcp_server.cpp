#include "tcp_server.h"

TCPServer::TCPServer(QObject *parent, int port)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any, port);
}

void TCPServer::incomingConnection(qintptr handle)
{
    TCPClient *tcpClient = new TCPClient(this);
    connect(tcpClient, SIGNAL(sigUpdateClients(QString, qint64)), this,
            SLOT(updateClients(QString, qint64)));
    connect(tcpClient, SIGNAL(sigDisconnected(qintptr)), this,
            SLOT(slotDisconnect(qintptr)));
    tcpClient->setSocketDescriptor(handle);
    m_listTcpClient.append(tcpClient);
}

void TCPServer::updateClients(QString msg, qint64 lenght)
{
    emit sigUpdateServer(msg, lenght);
    qInfo() << "msg" << msg;
    qInfo() << "len" << lenght;
    foreach( auto item , m_listTcpClient){
        // 广播所以的Tcp链接客户端。
        item->write(msg.toStdString().c_str(),msg.toStdString().length());
    }
}

void TCPServer::slotDisconnect(qintptr descrition)
{

    foreach (auto item, m_listTcpClient) {
        // 当断开时，找到对应的断开的句柄
        if (descrition == item->socketDescriptor()) {
            m_listTcpClient.removeOne(item);
            return;
        }
    }
}
