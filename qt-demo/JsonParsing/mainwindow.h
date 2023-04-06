#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void parseObject();
    void parseArray();
    void parseObjectArray();
    void parseArrayObject();

    // 构建 对象类型的json字符串
    void buildObject();
    // 构建 数组类型的json字符串
    void buildArray();
    // 构建 对象中包含数组
    void buildObjectArray();
    // 构建 数组中包含对象
    void buildArrayObject();
};

#endif  // MAINWINDOW_H
