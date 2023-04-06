#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QByteArray createImage();

   private:
    QTcpServer* m_pTcpServer;
    QList<QTcpSocket*> m_listTcpClient;
    QTimer* m_fTimer;
    QByteArray getReciveData();
   public slots:
    void slotNewConnection();
    void slotDisconnected();
    void slotDisplayError(QAbstractSocket::SocketError socketError);
    void slotUpdateImage();
    //   void slotTimerTimeout();
   signals:
    void sendMessage(const QString& msg);
    void sendMessageBinary(const QByteArray& msg);
};

#endif  // MAINWINDOW_H
