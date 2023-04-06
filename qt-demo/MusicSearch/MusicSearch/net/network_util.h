#ifndef NETWORK_UTIL_H
#define NETWORK_UTIL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "common.h"
/**
 * @brief The 网络请求管理类
 */
class NetworkUtil : public QObject {
    Q_OBJECT
   public:
    explicit NetworkUtil(QObject *parent = nullptr);
    QNetworkAccessManager *manager;
    QNetworkReply *m_ptrReplySreach;
    QNetworkReply *m_ptrReplyDownLoadUrl;
    QNetworkReply *m_ptrReplyDownLoadFile;
    void postSreach(QString MuiscName, int page);

    void postDownloadMuisc(AbsList info);
    void postDouwLoadMuisc(QString Muiscurl);

   private:
    void initConnect();

   signals:
    void sigSearchList(SreachListInfo info);
    void sigDownLoadFinish(AbsListLocal info);
   public slots:
    void slotSearchList();
    void slotGetDownLoadUrl();
    void slotGetMusicFile();

    void error(QNetworkReply::NetworkError);
    void sslErrors(const QList<QSslError> &errors);
};

#endif  // NETWORK_UTIL_H
