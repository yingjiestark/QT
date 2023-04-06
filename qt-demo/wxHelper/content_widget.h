#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QListView>
#include <QNetworkAccessManager>
#include "userinfo.h"
#include <QNetworkRequest>
class ContentWidget : public QWidget {
    Q_OBJECT
   public:
    explicit ContentWidget(QWidget *parent = nullptr);
    QListView *m_ptrListView;
    QNetworkAccessManager *m_ptrNetworkContactsList;
    userTokenInfo m_userInfo;

    void setUserInfo(userTokenInfo info);
    void initUI();
    void initConnect();
    void initData(QNetworkRequest req);
    void postContactsList(QNetworkRequest req);
    QString getRandom(int len);
   public slots:
    void slotContactsList(QNetworkReply *replay);
   signals:
};

#endif  // CONTENTWIDGET_H
