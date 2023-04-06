#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbus_server.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    DBUSServer server;
    ~MainWindow();
};

#endif  // MAINWINDOW_H
