#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget)
    , m_ptrBtnCreator(new QPushButton("创建Websocket服务"))
    , m_ptrLineEditPort(new QLineEdit)
    , m_ptrLabPort(new QLabel("端口"))
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrLayoutPort(new QHBoxLayout)
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    m_ptrLayoutPort->addWidget(m_ptrLabPort);
    m_ptrLayoutPort->addWidget(m_ptrLineEditPort);
    m_ptrLayoutMain->addLayout(m_ptrLayoutPort);
    m_ptrLayoutMain->addWidget(m_ptrBtnCreator);
    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnCreator, SIGNAL(clicked()), this,
            SLOT(slotClickCreateServer()));
}

void MainWindow::slotClickCreateServer()
{
    quint16 port = m_ptrLineEditPort->text().toUShort();
    m_ptrWebsocketServer = new WebsocketServer(port);
    m_ptrBtnCreator->setEnabled(false);
}
