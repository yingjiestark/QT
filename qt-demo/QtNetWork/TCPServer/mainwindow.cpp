#include "mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget(this))
    , m_ptrLabPort(new QLabel("端口"))
    , m_ptrListContent(new QListWidget())
    , m_ptrBtnCreate(new QPushButton("创建聊天室"))
    , m_ptrLineEditPort(new QLineEdit())
    , m_ptrGridLayoutMain(new QGridLayout)
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    m_ptrGridLayoutMain->addWidget(m_ptrListContent, 0, 0, 1, 2);
    m_ptrGridLayoutMain->addWidget(m_ptrLabPort, 1, 0);
    m_ptrGridLayoutMain->addWidget(m_ptrLineEditPort, 1, 1);
    m_ptrGridLayoutMain->addWidget(m_ptrBtnCreate, 2, 0, 1, 2);
    m_ptrWdgMain->setLayout(m_ptrGridLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnCreate, SIGNAL(clicked()), this, SLOT(slotClickCreate()));
}

void MainWindow::slotClickCreate()
{
    // 创建一个新的TcpServer,TcpServer的构造函数中，创建了监听。
    m_ptrTcpServer = new TCPServer(this, m_ptrLineEditPort->text().toInt());

    connect(m_ptrTcpServer, SIGNAL(sigUpdateServer(QString, qint64)), this,
            SLOT(slotUpdateServer(QString, qint64)));
    qInfo() << "slotCreate";
    m_ptrBtnCreate->setEnabled(false);
}

void MainWindow::slotUpdateServer(QString msg, qint64 length)
{
    qInfo() << "msg:" << msg;
    qInfo() << "len:" << length;
    m_ptrListContent->addItem(msg);
}
