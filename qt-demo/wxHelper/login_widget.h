#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "userinfo.h"
#include <QNetworkRequest>
class QNetworkAccessManager;
class QNetworkReply;
class QHBoxLayout;
class QLabel;
class QTimer;
class QLoginWidget : public QWidget {
    Q_OBJECT
   public:
    explicit QLoginWidget(QWidget *parent = nullptr);

   private:
    void initConnect();
    void initUI();
    // 发送数据请求
    void postQrCodeToken();
    int postQrCodeImage(QString token);
    void postLoginInfo(QString url);

    // 提取结果中的url登陆地址.
    QString getLoginUrl(QString res);
    //
    QString getUUID(QString res);
    userTokenInfo pareseUserInfoXml(QByteArray xml, xmlErr &err);

   private:
    QNetworkAccessManager *m_ptrQrCodeToken;
    QNetworkAccessManager *m_ptrQrCodeImage;
    QNetworkAccessManager *m_ptrLoginUrl;
    // 通过接口url获取xml文件,包含了用户的信息token
    QNetworkAccessManager *m_ptrLoginInfo;
    // 显示扫描登陆二维码，
    QLabel *m_ptrLabQrCodeImage;
    QHBoxLayout *m_mainLayout;
    QTimer *m_Time;
    QString m_strLoginToken;

   signals:
    void finishLogin(userTokenInfo userInfo, QNetworkRequest req);

   public slots:
    void postLoginUrl();
    // 获取token
    void slotQrCodeToken(QNetworkReply *reply);
    // 获取二维码图片地址
    void slotQrCodeImage(QNetworkReply *reply);
    void slotGetLoginUrl(QNetworkReply *reply);
    // 通过定时器获取用户信息
    void slotGetUserInfo(QNetworkReply *reply);

    void postContactsList(userTokenInfo userInfo);
    QString getRandom(int len);
};

#endif  // LOGINWIDGET_H
