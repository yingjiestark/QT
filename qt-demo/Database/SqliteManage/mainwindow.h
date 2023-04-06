#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "main_widget.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainWidget *m_ptrMainWdg;
};

#endif  // MAINWINDOW_H
