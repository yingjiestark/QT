#include "main_window.h"
#include "main_widget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrMainWidget(new MainWidget(this))
{
    resize(800, 600);
    setWindowTitle(tr("文件二进制读取"));
    setCentralWidget(m_ptrMainWidget);
}

MainWindow::~MainWindow() {}
