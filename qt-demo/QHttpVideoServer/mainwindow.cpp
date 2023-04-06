#include "mainwindow.h"
#include <QTcpSocket>
#include <QPen>
#include <QPainter>
#include <QDateTime>
#include <QBuffer>
#include <QDebug>
#include <QTimer>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_pTcpServer(new QTcpServer(this))
    , m_fTimer(new QTimer(this))
{
    connect(m_pTcpServer, &QTcpServer::newConnection, this,
            &MainWindow::slotNewConnection);
    connect(m_pTcpServer, &QTcpServer::acceptError, this,
            &MainWindow::slotDisplayError);
    m_fTimer->setInterval(1000);
    connect(m_fTimer, &QTimer::timeout, this, &MainWindow::slotUpdateImage);
    if (!m_pTcpServer->listen(QHostAddress::Any, 8884)) {
        qDebug() << "Server Could Not be Started";
        return;
    } else {
        qDebug() << "Server Started";
    }
}

MainWindow::~MainWindow() {}

QByteArray MainWindow::createImage()
{
    QImage image(400, 100, QImage::Format_RGB32);
    image.fill(Qt::transparent);
    QPainter p(&image);
    QString str = QDateTime::currentDateTimeUtc().toString();
    // p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    p.setPen(QPen(QColor(255, 0, 0, 255)));
    p.drawText(10, 10, QFontMetrics(str).width(str), QFontMetrics(str).height(),
               1, str);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPEG", 80);
    return ba;
}

QByteArray MainWindow::getReciveData()
{
    QByteArray text;
    auto blob = createImage();

    text += "Content-Type: image/jpeg\r\n";
    text += "Content-length: " + QString::number(blob.size()) + "\r\n\r\n";
    text.append(blob);
    text += "\r\n--myboundary\r\n";
    //  text += "\r\n\r\n";
    return text;
}

void MainWindow::slotNewConnection()
{
    QTcpSocket* pClientConnection = m_pTcpServer->nextPendingConnection();
    m_listTcpClient.push_back(pClientConnection);
    m_fTimer->start();
    connect(pClientConnection, SIGNAL(disconnected()), this,
            SLOT(slotDisconnected()));

    qInfo() << "slotNewConnection" << QDateTime::currentDateTimeUtc();
    QByteArray text =
        "HTTP/1.1 200 OK\r\nContent-Type: multipart/x-mixed-replace;"
        "boundary=myboundary\r\n";
    text += "\r\n--myboundary\r\n";
    text += getReciveData();
    pClientConnection->write(text);
}

void MainWindow::slotDisconnected()
{
    QTcpSocket* pQTcpSocket = static_cast<QTcpSocket*>(sender());
    m_listTcpClient.removeOne(pQTcpSocket);
    qInfo() << "receive disconnect!" << pQTcpSocket;
    pQTcpSocket->deleteLater();
}

void MainWindow::slotDisplayError(QAbstractSocket::SocketError socketError)
{
    qInfo() << "SimpleTcpSocketServerDemo::displayError " << socketError;
}

void MainWindow::slotUpdateImage()
{
    QByteArray text = getReciveData();

    foreach (auto item, m_listTcpClient) {
        item->write(text);
    }
}
