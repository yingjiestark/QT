#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcp_client.h"
class TCPServer : public QTcpServer {
    Q_OBJECT
   public:
    TCPServer(QObject *parent, int port = 0);

   private:
    QList<TCPClient *> m_listTcpClient;
    // QTcpServer interface
   protected:
    void incomingConnection(qintptr handle);
   signals:
    void sigUpdateServer(QString, qint64);
   public slots:
    void updateClients(QString, qint64);
    void slotDisconnect(qintptr);
};

#endif  // TCP_SERVER_H
