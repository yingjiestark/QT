#include "network_util.h"
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QDir>
#include "db/db_manager.h"
#include <QMessageBox>
NetworkUtil::NetworkUtil(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
{
    initConnect();
}

void NetworkUtil::postSreach(QString MuiscName, int page)
{
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    QString url = QString(
                      "https://search.kuwo.cn/"
                      "r.s?all=%0&ft=music&client=kt&pn=%1&rn=10&"
                      "rformat=json&encoding=utf8")
                      .arg(MuiscName)
                      .arg(QString::number(page));
    qInfo() << "url:" << url;
    request.setUrl(QUrl(url));
    request.setSslConfiguration(conf);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json"));
    m_ptrReplySreach = manager->get(request);

    connect(m_ptrReplySreach, SIGNAL(finished()), this, SLOT(slotSearchList()));
    connect(m_ptrReplySreach, SIGNAL(error(QNetworkReply::NetworkError)), this,
            SLOT(error(QNetworkReply::NetworkError)));
    connect(m_ptrReplySreach, SIGNAL(sslErrors(const QList<QSslError>)), this,
            SLOT(sslErrors(const QList<QSslError>)));
}
/**
 * @brief 根据获取的音乐的数据,下子对应的音乐
 * @param info 某一首音乐的数据.
 */
void NetworkUtil::postDownloadMuisc(AbsList info)
{
    qInfo() << "MUSICRID" << info.MUSICRID;

    QString rid = info.MUSICRID;
    QString format = info.FORMATS;
    QNetworkRequest request;
    QString url = QString(
                      "https://antiserver.kuwo.cn/"
                      "anti.s?type=convert_url&rid=%0&format=mp3&response=url")
                      .arg(rid)
                      .arg(format);

    QSslConfiguration conf = request.sslConfiguration();
    request.setUrl(QUrl(url));
    request.setSslConfiguration(conf);

    m_ptrReplyDownLoadUrl = manager->get(request);
    info.URL = url;

    m_ptrReplyDownLoadUrl->setProperty("info", QVariant::fromValue(info));
    connect(m_ptrReplyDownLoadUrl, SIGNAL(finished()), this,
            SLOT(slotGetDownLoadUrl()));
}

void NetworkUtil::initConnect()
{
    //    connect(manager, SIGNAL(finished(QNetworkReply *)), this,
    //            SLOT(slo(QNetworkReply *)));
}

void NetworkUtil::slotSearchList()
{
    qInfo() << "slotSearchList start";
    QByteArray data = m_ptrReplySreach->readAll();
    QString strData = QString(data);
    strData.replace("'", "\"");

    QJsonDocument json_doc = QJsonDocument::fromJson(strData.toUtf8());

    if (json_doc.isEmpty() || json_doc.isNull()) {
        qInfo() << "json解析失败!";
        return;
    }
    QJsonObject json_root_object = json_doc.object();
    SreachListInfo info;
    info.pn = json_root_object.value("pn").toString().toInt();
    info.show = json_root_object.value("SHOW").toString().toInt();
    info.total = json_root_object.value("TOTAL").toString().toInt();
    qInfo() << "slotSearchList error:" << json_root_object;

    QJsonArray json_abslist_array = json_root_object.value("abslist").toArray();

    foreach (auto item, json_abslist_array) {
        AbsList item_info;
        QJsonObject json_item_object = item.toObject();
        item_info.NAME = json_item_object.value("NAME").toString();
        item_info.ARTIST = json_item_object.value("ARTIST").toString();
        item_info.AARTIST = json_item_object.value("AARTIST").toString();
        item_info.MUSICRID = json_item_object.value("MUSICRID").toString();
        item_info.FORMATS = json_item_object.value("FORMATS").toString();
        item_info.IMAGE = json_item_object.value("hts_MVPIC").toString();
        info.absList.append(item_info);
    }
    sigSearchList(info);
}

void NetworkUtil::slotGetDownLoadUrl()
{
    qInfo() << " slotGetDownLoadUrl start";
    QByteArray data = m_ptrReplyDownLoadUrl->readAll();
    if (data.isNull() || data.isEmpty()) {
        qInfo() << "未获取下载地址";
        return;
    }
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    request.setUrl(QUrl(data));
    request.setSslConfiguration(conf);

    m_ptrReplyDownLoadFile = manager->get(request);
    m_ptrReplyDownLoadFile->setProperty(
        "info", m_ptrReplyDownLoadUrl->property("info"));
    connect(m_ptrReplyDownLoadFile, SIGNAL(finished()), this,
            SLOT(slotGetMusicFile()));
}

void NetworkUtil::slotGetMusicFile()
{
    qInfo() << " slotGetMusicFile start";
    QByteArray data = m_ptrReplyDownLoadFile->readAll();
    AbsList info = m_ptrReplyDownLoadFile->property("info").value<AbsList>();
    QString fullPath = QDir::homePath() + "/Desktop/1/";
    // 音乐本地路径
    QString fileName = fullPath + info.NAME + ".mp3";
    QDir dir(fullPath);
    if (!dir.exists()) {
        dir.mkpath(fullPath);
    }
    QFile f(fileName);
    f.open(QFile::WriteOnly);
    f.write(data);
    f.close();

    AbsListLocal localInfo;
    localInfo = info;
    localInfo.localPath = fileName;
    qInfo() << "localInfo.IMAGE" << localInfo.IMAGE;
    localInfo.localImage = localInfo.IMAGE;

    DBManager::instance()->insertData(localInfo);
    emit sigDownLoadFinish(localInfo);
    qInfo() << " slotGetMusicFile end";
}

void NetworkUtil::error(QNetworkReply::NetworkError e) { qInfo() << e; }

void NetworkUtil::sslErrors(const QList<QSslError> &errors)
{
    qInfo() << errors;
}
