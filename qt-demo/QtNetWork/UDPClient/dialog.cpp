#include "dialog.h"
#include <QtDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrUdpClient(new QUdpSocket(this))
    , m_ptrTimer(new QTimer(this))
    , m_ptrBtn(new QPushButton("发送"))
    , m_ptrLayoutMain(new QVBoxLayout(this))
    , num(0)

{
    setWindowTitle("UDPClient");
    initUI();
    initConnect();
}

Widget::~Widget() {}

void Widget::initUI()
{
    m_ptrLayoutMain->addWidget(m_ptrBtn);
    resize(500, 500);
}

void Widget::initConnect()
{
    connect(m_ptrTimer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
    connect(m_ptrBtn, SIGNAL(clicked()), this, SLOT(slotClickBtn()));
}

void Widget::slotTimeOut()
{
    num++;
    qInfo() << "slotTimeOut";
    QString strData = "您好！" + QString::number(num);
    m_ptrUdpClient->writeDatagram(strData.toStdString().c_str(),
                                  strData.toStdString().length(),
                                  QHostAddress::LocalHost, 7755);
    return;
}

void Widget::slotClickBtn() { m_ptrTimer->start(1000); }
