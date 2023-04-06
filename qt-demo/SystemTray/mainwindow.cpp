#include "mainwindow.h"
#include <QSystemTrayIcon>
#include <QTimer>
#include <QtDebug>
#include <QEvent>
#include <QMenu>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainView(new QWidget(this))
    , m_timer(new QTimer)
    , m_num(0)
    , m_systemTray(new QSystemTrayIcon(this))
    , m_mainLayout(new QVBoxLayout())
    , m_btnShow(new QPushButton("展示托盘"))
    , m_btnAction(new QPushButton("托盘消息"))

{
    m_timer->setInterval(500);
    m_timer->stop();
    m_systemTray->setIcon(QIcon(":/Resources/直播.png"));
    m_systemTray->setToolTip("SystemTray Program");
    m_pPreMenu = new QMenu(this);
    m_pPreMenu->addAction(QString::fromLocal8Bit("50万"));
    m_pPreMenu->addAction(QString::fromLocal8Bit("100万"));
    m_pPreMenu->addAction(QString::fromLocal8Bit("500万"));
    m_pPreMenu->addAction(QString::fromLocal8Bit("1000万"));
    m_systemTray->setContextMenu(m_pPreMenu);

    connect(m_btnShow, &QPushButton::clicked, this, &MainWindow::slotShowTray);
    connect(m_btnAction, &QPushButton::clicked, this,
            &MainWindow::slotActionTray);
    connect(m_timer, &QTimer::timeout, this,
            &MainWindow::slotActionTrayTimeout);
    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(slotActionSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    m_mainLayout->addWidget(m_btnShow);
    m_mainLayout->addWidget(m_btnAction);
    m_mainView->setLayout(m_mainLayout);
    setCentralWidget(m_mainView);
}

MainWindow::~MainWindow() {}

void MainWindow::slotShowTray() { m_systemTray->show(); }

void MainWindow::slotActionTray() { m_timer->start(); }

void MainWindow::slotActionTrayTimeout()
{
    qInfo() << m_num;
    if (m_num % 2 == 0) {
        m_num = 0;
        m_systemTray->setIcon(QIcon(":/Resources/action.jpg_"));
        m_systemTray->show();
    } else {
        m_systemTray->setIcon(QIcon(":/Resources/直播.png"));
        m_systemTray->show();
    }

    m_num++;
}

void MainWindow::slotActionSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            //单击托盘图标
            this->showNormal();
            break;
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            //双击后显示主程序窗口
            this->showNormal();
            break;
        default:
            break;
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() != QEvent::WindowStateChange) return;
    qInfo() << windowFlags();
    if (this->windowState() == Qt::WindowMinimized) {
        qInfo() << "窗口最小化";
        m_systemTray->show();
        setWindowFlag(Qt::Tool);
    } else if (this->windowState() == Qt::WindowMaximized) {
        qInfo() << "窗口最大化";
    } else {
        qInfo() << "窗口状态变化:" << this->windowState();
        m_systemTray->hide();
        setWindowFlags(Qt::Window | Qt::WindowTitleHint |
                       Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint |
                       Qt::WindowCloseButtonHint |
                       Qt::WindowFullscreenButtonHint);
    }
}
