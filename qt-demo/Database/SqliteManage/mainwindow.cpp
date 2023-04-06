#include "mainwindow.h"

#include <QtDebug>
#include <QSqlTableModel>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrMainWdg(new MainWidget(parent))
{
    setCentralWidget(m_ptrMainWdg);
}

MainWindow::~MainWindow() {}
