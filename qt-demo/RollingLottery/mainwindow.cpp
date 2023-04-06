#include "mainwindow.h"
#include "rolling_lottery_view.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QtDebug>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainview(new RollingLotteryView(5))
    , m_btn(new QPushButton("开始"))
    , m_status(false)
    , m_windowStatus(false)

{

    m_mainview->setBackground(QImage(":/res/backgroud.jpeg"));
    m_mainview->setItemColor(QColor("#ffffff"));
    setCentralWidget(m_mainview);

    connect(m_mainview, &RollingLotteryView::sigStop, this,
            &MainWindow::slotStop);
    connect(m_btn, &QPushButton::clicked, this, &MainWindow::slotClickBtn);
}

MainWindow::~MainWindow() {}

void MainWindow::slotClickBtn()
{
    if (!m_status) {
        m_mainview->start();
        m_status = true;
    } else {
        m_status = false;
        m_mainview->stop();
    }
}

void MainWindow::slotStop(int num)
{
    qInfo() << "MainWindow::slotStop num:" << num;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F11){
        if(m_windowStatus){
            m_windowStatus = false;
            this->setWindowFlag(Qt::Window);
            this->showFullScreen();
        }else {
            m_windowStatus = true;
            this->setWindowFlag(Qt::SubWindow);
            this->showNormal();
        }

    }else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Space){

        slotClickBtn();
    }
}
