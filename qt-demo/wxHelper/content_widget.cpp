#include "content_widget.h"
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "url.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <qrandom.h>
#include <QJsonValue>
#include <QDateTime>
#include <QtGlobal>
#include <QTime>
#include <stdio.h>
ContentWidget::ContentWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrListView(new QListView(this))
    , m_ptrNetworkContactsList(new QNetworkAccessManager)
{
    initConnect();
}

void ContentWidget::setUserInfo(userTokenInfo info) { m_userInfo = info; }

void ContentWidget::initUI() {}

void ContentWidget::initConnect()
{
    connect(m_ptrNetworkContactsList, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotContactsList(QNetworkReply *)));
}

void ContentWidget::initData(QNetworkRequest req) { postContactsList(req); }

void ContentWidget::postContactsList(QNetworkRequest req)
{
    //  QNetworkRequest request;
    QByteArray post_Array;
    //    QSslConfiguration conf = request.sslConfiguration();

    req.setHeader(
        QNetworkRequest::UserAgentHeader,
        QVariant("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, "
                 "like Gecko) Chrome/86.0.4240.198 Safari/537.36"));
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/json"));
    QDateTime current_time = QDateTime::currentDateTime();
    quint32 t = static_cast<quint32>(current_time.toTime_t());
    fprintf(stderr, "t:%x\r\n", t);
    fprintf(stderr, "t:%d\r\n", t);
    quint32 r = 11557725;
    //  r = r | 0x100000000;
    fprintf(stderr, "r:%x\r\n", r);
    fprintf(stderr, "r:%d\r\n", r);
    // new date();
    QString random = QString::number(r);

    QString url = QString(kWebwxinit) + "?r=" + random +
                  "&lang=zh_CN&pass_ticket=" + m_userInfo.pass_ticket;
    qInfo() << "url:" << url;
    req.setUrl(QUrl(url));
    QJsonDocument json_res;
    QJsonObject jsonValue;
    QJsonObject jsonBaseRequest;

    jsonValue.insert("Uid", m_userInfo.wxuin);

    jsonValue.insert("Sid", m_userInfo.wxsid);

    jsonValue.insert("Skey", m_userInfo.skey);
    // DeiveceID = math.random.tofixed(15).subtring(2,17);
    QString strDeviceID = "e" + getRandom(15);
    jsonValue.insert("DeviceID", strDeviceID);

    jsonBaseRequest.insert("BaseRequest", jsonValue);
    json_res.setObject(jsonBaseRequest);
    QByteArray post_data = json_res.toJson(QJsonDocument::Compact);
    qInfo() << "post_data:" << post_data;
    m_ptrNetworkContactsList->post(req, post_data);
}

QString ContentWidget::getRandom(int len)
{
    const char c_szRandom[] = "0123456789\0";
    qsrand(QTime(0, 0, 0, 0).secsTo(QTime::currentTime()));
    QString tmp = "";
    for (int i = 0; i < len; i++) {
        int a = qrand() % 10;
        tmp += (QChar(c_szRandom[a]));
    }
    return tmp;
}

void ContentWidget::slotContactsList(QNetworkReply *reply)
{
    qInfo() << "reply:" << reply->readAll();
}
