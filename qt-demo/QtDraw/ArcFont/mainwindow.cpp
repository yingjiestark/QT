#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m(new LArcFont("你好,欢迎来到arv000的博客", 200, 200))
{
    setCentralWidget(m);
}

MainWindow::~MainWindow() {}
