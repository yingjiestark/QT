#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget(this))
    , m_ptrLayoutMain(new QGridLayout)
    , m_ptrListContent(new QListWidget)
    , m_ptrLineEditContent(new QLineEdit)
    , m_ptrBtnSend(new QPushButton("发送"))
    , m_ptrLabUserName(new QLabel("用户名"))
    , m_ptrLineEditUserName(new QLineEdit)
    , m_ptrLabAddress(new QLabel("服务器地址"))
    , m_ptrLineEditAddress(new QLineEdit)
    , m_ptrLabPort(new QLabel("端口号："))
    , m_ptrLineEditPort(new QLineEdit)
    , m_ptrBtnEnter(new QPushButton(tr("进入聊天室")))
    , m_ptrClientTcpSocket(new QTcpSocket(this))
    , m_status(false)
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    m_ptrLayoutMain->addWidget(m_ptrListContent, 0, 0, 1, 2);
    m_ptrLayoutMain->addWidget(m_ptrLineEditContent, 1, 0);
    m_ptrLayoutMain->addWidget(m_ptrBtnSend, 1, 1);

    m_ptrLayoutMain->addWidget(m_ptrLabUserName, 2, 0);
    m_ptrLayoutMain->addWidget(m_ptrLineEditUserName, 2, 1);
    m_ptrLayoutMain->addWidget(m_ptrLabAddress, 3, 0);
    m_ptrLayoutMain->addWidget(m_ptrLineEditAddress, 3, 1);
    m_ptrLayoutMain->addWidget(m_ptrLabPort, 4, 0);
    m_ptrLayoutMain->addWidget(m_ptrLineEditPort, 4, 1);
    m_ptrLayoutMain->addWidget(m_ptrBtnEnter, 5, 0, 1, 2);
    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnEnter, SIGNAL(clicked()), this, SLOT(slotClickEnter()));
    connect(m_ptrBtnSend, SIGNAL(clicked()), this,
            SLOT(slotClickSendContent()));
    connect(m_ptrClientTcpSocket, SIGNAL(connected()), this,
            SLOT(slotConnected()));
    connect(m_ptrClientTcpSocket, SIGNAL(disconnected()), this,
            SLOT(slotDisConnected()));
    connect(m_ptrClientTcpSocket, SIGNAL(readyRead()), this,
            SLOT(slotDataReveived()));
}

void MainWindow::slotClickEnter()
{
    QString strAddress = m_ptrLineEditAddress->text();
    QString strPort = m_ptrLineEditPort->text();
    if (!m_status) {
        m_ptrBtnEnter->setText(tr("离开"));
        m_ptrClientTcpSocket->connectToHost(strAddress, strPort.toUShort());
    } else {
        m_ptrClientTcpSocket->disconnectFromHost();
        m_ptrBtnEnter->setText(tr("进入聊天室"));
    }
    m_status = !m_status;
}

void MainWindow::slotClickSendContent()
{
    QString strUserName = m_ptrLineEditUserName->text();
    QString strContent = m_ptrLineEditContent->text();
    QString msg = strUserName + ":" + strContent;
    m_ptrClientTcpSocket->write(msg.toStdString().c_str(),
                                msg.toStdString().length());
}

void MainWindow::slotConnected()
{
    qInfo() << "slotConnected";
    QString strUserName = m_ptrLineEditUserName->text();
    QString msg = "用户：" + strUserName + ",进入聊天室";
    m_ptrClientTcpSocket->write(msg.toStdString().c_str(), msg.length());
}

void MainWindow::slotDisConnected()
{
    qInfo() << "slotDisConnected";
    QString strUserName = m_ptrLineEditUserName->text();
    QString msg = "用户：" + strUserName + ",离开聊天室";
    m_ptrClientTcpSocket->write(msg.toStdString().c_str(), msg.length());
}

void MainWindow::slotDataReveived()
{
    while (m_ptrClientTcpSocket->bytesAvailable() > 0) {
        QByteArray datagram;
        datagram.resize(m_ptrClientTcpSocket->bytesAvailable());
        m_ptrClientTcpSocket->read(datagram.data(), datagram.size());
        QString msg = datagram.data();
        m_ptrListContent->addItem(msg);
    }
}
