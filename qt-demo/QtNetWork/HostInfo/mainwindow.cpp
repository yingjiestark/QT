#include "mainwindow.h"
#include <QHostInfo>
#include <QNetworkInterface>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrLabHost(new QLabel("主机名:"))
    , m_ptrLineEditHostName(new QLineEdit())
    , m_ptrBtnDetail(new QPushButton("详细信息"))
    , m_ptrWdgMain(new QWidget(this))
    , m_ptrLayoutMain(new QGridLayout(m_ptrWdgMain))

{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    m_ptrLayoutMain->addWidget(m_ptrLabHost, 0, 0);
    m_ptrLayoutMain->addWidget(m_ptrLineEditHostName, 0, 1);
    m_ptrLayoutMain->addWidget(m_ptrBtnDetail, 2, 0, 1, 2);
    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnDetail, SIGNAL(clicked()), this,
            SLOT(slotGetNetWorkDetail()));
}

void MainWindow::slotGetNetWorkDetail()
{
    QString strHostName = QHostInfo::localHostName();
    QString strHostDomain = QHostInfo::localDomainName();
    m_ptrLineEditHostName->setText(strHostName);
    QHostInfo hostInfo = QHostInfo::fromName(strHostName);

    QList<QHostAddress> list = hostInfo.addresses();
    foreach (auto item, list) {
        qInfo() << item.toString();
    }
    QList<QHostAddress> listAddress = QNetworkInterface::allAddresses();
    foreach (auto item, listAddress) {
        qInfo() << item.toString();
    }
    QList<QNetworkInterface> listNetworkInterface =
        QNetworkInterface::allInterfaces();

    foreach (auto item, listNetworkInterface) {
        qInfo() << tr("设备：") + item.name();
        qInfo() << tr("硬件地址：") + item.hardwareAddress();

        foreach (auto item2, item.addressEntries()) {
            qInfo() << "    " + tr("ip地址：") + item2.ip().toString();
            qInfo() << "    " + tr("子网掩码：") + item2.netmask().toString();
            qInfo() << "    " + tr("广播地址：") + item2.broadcast().toString();
        }
    }
}
