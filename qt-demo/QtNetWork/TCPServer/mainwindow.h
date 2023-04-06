#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include "tcp_server.h"
#include <QListWidget>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    void initUI();
    void initConnect();

   private:
    QWidget *m_ptrWdgMain;
    QLabel *m_ptrLabPort;
    QListWidget *m_ptrListContent;
    QPushButton *m_ptrBtnCreate;
    QLineEdit *m_ptrLineEditPort;
    QGridLayout *m_ptrGridLayoutMain;
    TCPServer *m_ptrTcpServer;

   public slots:
    void slotClickCreate();
    void slotUpdateServer(QString, qint64);
};

#endif  // MAINWINDOW_H
