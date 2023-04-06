#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QTcpSocket>
#include <QObject>
class TCPClient : public QTcpSocket {
    Q_OBJECT
   public:
    TCPClient(QObject *parent = 0);

   public slots:
    void slotDataReceived();
    void slotDisconnected();
   signals:
    void sigUpdateClients(QString msg, qint64 length);
    void sigDisconnected(qintptr);
};

#endif  // TCP_CLIENT_H
