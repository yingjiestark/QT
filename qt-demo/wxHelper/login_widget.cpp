#include "login_widget.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QDomDocument>
#include <QJsonDocument>
#include "url.h"
#include <QJsonObject>
QLoginWidget::QLoginWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrQrCodeToken(new QNetworkAccessManager)
    , m_ptrQrCodeImage(new QNetworkAccessManager)
    , m_ptrLoginUrl(new QNetworkAccessManager)
    , m_ptrLoginInfo(new QNetworkAccessManager)
    , m_ptrLabQrCodeImage(new QLabel(this))
    , m_mainLayout(new QHBoxLayout)
    , m_Time(new QTimer)
    , m_strLoginToken("")

{
    initUI();
    initConnect();
    postQrCodeToken();
    // pareseUserInfoXml("");
    // test
    //    getLoginInfoUrl("");
}

void QLoginWidget::postQrCodeToken()
{
    QSslConfiguration config;
    QNetworkRequest request;
    QByteArray post_Array;
    QSslConfiguration conf = request.sslConfiguration();

    QString strQtCodeUrApi =
        "https://login.weixin.qq.com/"
        "jslogin?appid=wx782c26e4c19acffb&fun=new&lang=zh_CN";
    request.setUrl(QUrl(strQtCodeUrApi));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json"));

    QByteArray postData;

    m_ptrQrCodeToken->post(request, postData);
}

int QLoginWidget::postQrCodeImage(QString token)
{
    QSslConfiguration config;
    QNetworkRequest request;
    QByteArray post_Array;
    QSslConfiguration conf = request.sslConfiguration();

    QString strQtCodeUrApi = "https://login.weixin.qq.com/qrcode/" + token;
    request.setUrl(QUrl(strQtCodeUrApi));

    QByteArray postData;

    m_ptrQrCodeImage->post(request, postData);
    return 0;
}

void QLoginWidget::postLoginInfo(QString url)
{
    QSslConfiguration config;
    QNetworkRequest request;
    QByteArray post_Array;
    QSslConfiguration conf = request.sslConfiguration();

    QString strQtCodeUrApi = url;
    request.setUrl(QUrl(strQtCodeUrApi));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/xml"));
    QByteArray postData;

    m_ptrLoginInfo->post(request, postData);
}

QString QLoginWidget::getLoginUrl(QString res)
{
    //    res =
    //        "window.code=200;\nwindow.redirect_uri=\"https://wx2.qq.com/cgi-bin/"
    //        "mmwebwx-bin/"
    //        "webwxnewloginpage?ticket=A7o_UGbp_w9aUl3ZHXI-6rfo@qrticket_0&uuid="
    //        "4dP2BO0mpg==&lang=zh_CN&scan=1652086574\";";
    QStringList list = res.split(";");
    if (list.size() == 2) {
        QRegExp rx("window.code=(\\d+);");
        rx.indexIn(res);
        qInfo() << "code:" << rx.cap(1);

        return "";
    }
    QRegExp rx(
        "window.code=(\\d+);\\nwindow.redirect_uri="
        "\"(.*)\";");
    rx.indexIn(res);
    int code = rx.cap(1).toInt();
    if (code == 200) {
        m_Time->stop();
    }
    qInfo() << rx.cap(2);

    return rx.cap(2);
}

void QLoginWidget::postLoginUrl()
{
    QSslConfiguration config;
    QNetworkRequest request;
    QByteArray post_Array;
    QSslConfiguration conf = request.sslConfiguration();

    QString strQtCodeUrApi =
        "https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?uuid=" +
        m_strLoginToken + "&tip=1";
    qInfo() << strQtCodeUrApi;
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("Content-Type:text/xml"));
    request.setUrl(QUrl(strQtCodeUrApi));
    QByteArray postData;

    m_ptrLoginUrl->post(request, postData);
}

void QLoginWidget::initConnect()
{
    connect(m_Time, SIGNAL(timeout()), this, SLOT(postLoginUrl()));

    connect(m_ptrQrCodeToken, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotQrCodeToken(QNetworkReply *)));
    connect(m_ptrQrCodeImage, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotQrCodeImage(QNetworkReply *)));
    connect(m_ptrLoginUrl, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotGetLoginUrl(QNetworkReply *)));

    connect(m_ptrLoginInfo, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotGetUserInfo(QNetworkReply *)));
}

void QLoginWidget::initUI()
{
    setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_ptrLabQrCodeImage);
}

QString QLoginWidget::getUUID(QString res)
{
    QRegExp rx(
        "window.QRLogin.code = (\\d+); window.QRLogin.uuid = "
        "\"(.*)\";");
    rx.indexIn(res);
    int code = rx.cap(1).toInt();
    if (code != 200) return "";
    m_Time->stop();
    QString strToken = rx.cap(2);
    m_strLoginToken = strToken;
    return strToken;
}

userTokenInfo QLoginWidget::pareseUserInfoXml(QByteArray xml, xmlErr &err)
{
    userTokenInfo userInfo;
    QDomDocument doc;
    qInfo() << "xml:" << xml;
    if (!doc.setContent(xml)) {
        qInfo() << "加载xml数据失败";
        err.code = -1;
        err.message = "加载xml数据失败";
        return userInfo;
    }

    QDomElement elem_root = doc.documentElement();
    QDomElement elem_ret = elem_root.firstChildElement("ret");
    int code = elem_ret.text().toInt();

    qInfo() << "elem_ret:" << elem_ret.text();
    QDomElement elem_message = elem_root.firstChildElement("message");
    qInfo() << "elem_message:" << elem_message.text();

    if (code != 0) {
        err.code = code;
        err.message = elem_message.text();
        return userInfo;
    }

    QDomElement elem_skey = elem_root.firstChildElement("skey");
    qInfo() << "elem_skey:" << elem_skey.text();
    QDomElement elem_wxsid = elem_root.firstChildElement("wxsid");
    qInfo() << "elem_wxsid:" << elem_wxsid.text();
    QDomElement elem_wxuin = elem_root.firstChildElement("wxuin");
    qInfo() << "elem_wxuin:" << elem_wxuin.text();
    QDomElement elem_pass_ticket = elem_root.firstChildElement("pass_ticket");
    qInfo() << "elem_pass_ticket:" << elem_pass_ticket.text();
    QDomElement elem_isgrayscale = elem_root.firstChildElement("isgrayscale");
    qInfo() << "elem_isgrayscale:" << elem_isgrayscale.text();

    userInfo.skey = elem_skey.text();
    userInfo.wxsid = elem_wxsid.text();
    userInfo.wxuin = elem_wxuin.text();
    userInfo.pass_ticket = elem_pass_ticket.text();
    userInfo.isgrayscale = elem_isgrayscale.text();
    return userInfo;
}

void QLoginWidget::slotQrCodeToken(QNetworkReply *reply)
{
    QString strRes = reply->readAll();
    QString strToken = getUUID(strRes);
    qInfo() << "strToken:" << strToken;
    if (strToken.isEmpty()) {
        return;
    }

    postQrCodeImage(strToken);
}

void QLoginWidget::slotQrCodeImage(QNetworkReply *reply)
{
    qInfo() << "slotQrCodeImage start";
    if (reply->error() == QNetworkReply::NoError) {
        qInfo() << "slotQrCodeImage start2";
        // qInfo() << reply->readAll();
        QByteArray bytes = reply->readAll();
        QPixmap pmd;
        pmd.loadFromData(bytes);
        m_ptrLabQrCodeImage->setPixmap(pmd);
        m_ptrLabQrCodeImage->setVisible(true);
        m_Time->start(1000);
    }
}

void QLoginWidget::slotGetLoginUrl(QNetworkReply *reply)
{
    QString res = reply->readAll();
    QString url = getLoginUrl(res);
    if (url.isEmpty()) return;
    postLoginInfo(url);
    //    qInfo() << "url=" << url;
}

void QLoginWidget::slotGetUserInfo(QNetworkReply *reply)
{
    QByteArray x = reply->readAll();

    qInfo() << "slotGetUserInfo1 :" << x;
    xmlErr err;
    userTokenInfo userInfo = pareseUserInfoXml(x, err);
    if (err.code != 0) {
        return;
    }

    //   emit finishLogin(userInfo, reply->request());
    postContactsList(userInfo);
}

void QLoginWidget::postContactsList(userTokenInfo userInfo)
{
    //  QNetworkRequest request;
    QByteArray post_Array;
    //    QSslConfiguration conf = request.sslConfiguration();
    QNetworkRequest req;
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
                  "&lang=zh_CN&pass_ticket=" + userInfo.pass_ticket;
    qInfo() << "url:" << url;
    req.setUrl(QUrl(url));
    QJsonDocument json_res;
    QJsonObject jsonValue;
    QJsonObject jsonBaseRequest;

    jsonValue.insert("Uid", userInfo.wxuin);

    jsonValue.insert("Sid", userInfo.wxsid);

    jsonValue.insert("Skey", userInfo.skey);
    // DeiveceID = math.random.tofixed(15).subtring(2,17);
    QString strDeviceID = "e" + getRandom(15);
    jsonValue.insert("DeviceID", strDeviceID);

    jsonBaseRequest.insert("BaseRequest", jsonValue);
    json_res.setObject(jsonBaseRequest);
    QByteArray post_data = json_res.toJson(QJsonDocument::Compact);
    qInfo() << "post_data:" << post_data;
    m_ptrLoginInfo->post(req, post_data);
}

QString QLoginWidget::getRandom(int len)
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
