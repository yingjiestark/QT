#include "widget.h"
#include <QNetworkDatagram>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrTextEditContent(new QTextEdit(this))
    , m_ptrUdpServer(new QUdpSocket(this))
{
    initUI();
    initServerSokcet();
}

void Widget::initUI()
{
    setWindowTitle("UDP服务器");
    resize(500, 500);
}

Widget::~Widget() {}

void Widget::initServerSokcet()
{
    m_ptrUdpServer->bind(QHostAddress("127.0.0.1"), 7755);

    connect(m_ptrUdpServer, &QUdpSocket::readyRead, this,
            &Widget::readPendingDatagrams);
}

void Widget::readPendingDatagrams()
{
    while (m_ptrUdpServer->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_ptrUdpServer->receiveDatagram();
        qInfo() << datagram.data().toStdString().c_str();
        QString data = m_ptrTextEditContent->toPlainText() + "\r\n";
        m_ptrTextEditContent->setText(data +
                                      datagram.data().toStdString().c_str());
    }
}
