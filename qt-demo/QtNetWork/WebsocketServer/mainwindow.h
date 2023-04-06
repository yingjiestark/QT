#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include "websocket_server.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QWidget *m_ptrWdgMain;
    QPushButton *m_ptrBtnCreator;
    QLineEdit *m_ptrLineEditPort;
    QLabel *m_ptrLabPort;
    QVBoxLayout *m_ptrLayoutMain;
    QHBoxLayout *m_ptrLayoutPort;

    WebsocketServer *m_ptrWebsocketServer;
private:
    void initUI();
    void initConnect();
public slots:
    void slotClickCreateServer();


};

#endif // MAINWINDOW_H
