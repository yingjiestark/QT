#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include "websocket_server.h"
#include <iostream>

using namespace std;
WebsocketServer::WebsocketServer(quint16 port, bool debug, QObject *parent)
    : QObject(parent)
    , m_pWebSocketServer(new QWebSocketServer(
          QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this))
    , m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        printf("start success!\n");

        printf("Echoserver listening on port %d\n", port);
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this,
                &WebsocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this,
                &WebsocketServer::closed);
    } else {
        printf("start error!\n");
    }
}

WebsocketServer::~WebsocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebsocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this,
            &WebsocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this,
            &WebsocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this,
            &WebsocketServer::socketDisconnected);

    m_clients << pSocket;
}

//! [processTextMessage]
void WebsocketServer::processTextMessage(QString message)
{
    qInfo() << "Message received3:" << message;
    printf("processTextMessage finish!");
}
//! [processTextMessage]

//! [processBinaryMessage]
void WebsocketServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug) qInfo() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void WebsocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug) qInfo() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
