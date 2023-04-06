#include "mainwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget())
    , m_ptrLabAppSecret(new QLabel("AppSecret"))
    , m_ptrLineEditAppSecret(new QLineEdit())
    , m_ptrLabAppToken(new QLabel("Token"))
    , m_ptrLineEditToken(new QLineEdit())
    , m_ptrLayoutApp(new QGridLayout())
    , m_ptrLayoutMain(new QVBoxLayout())
    , m_ptrTextEditInput(new QTextEdit())
    , m_ptrTextEditOutput(new QTextEdit())
    , m_ptrCmbSource(new QComboBox())
    , m_ptrCmbTraget(new QComboBox())
    , m_ptrLabText(new QLabel("翻译成"))
    , m_ptrLayoutConfig(new QHBoxLayout())
    , m_ptrBtnDowork(new QPushButton("翻译"))
    , m_strApiUrl("https://aip.baidubce.com/rpc/2.0/mt/texttrans/v1")
    , m_strTokenUrl("https://aip.baidubce.com/oauth/2.0/token")
    //  , m_strTokenUrl("https://www.baidu.com")
    , manager(new QNetworkAccessManager(this))
    , managerData(new QNetworkAccessManager(this))

{
    initUI();
    initConnect();
    readConfig();
}

MainWindow::~MainWindow() {}

void MainWindow::readConfig()
{
    QString Path = QCoreApplication::applicationDirPath();
    QString endPath = Path + "/config.ini";
    QFileInfo fileinfo(endPath);
    if (!fileinfo.isFile()) {
        qDebug() << "文件不存在";
    }
    QSettings setting(endPath, QSettings::IniFormat);
    setting.beginGroup("APP");
    QString strAppSecret = setting.value("AppSecret", "").toString();
    QString strToken = setting.value("Token", "").toString();

    m_ptrLineEditAppSecret->setText(strAppSecret);
    m_ptrLineEditToken->setText(strToken);
}

void MainWindow::saveConfig()
{
    QString Path = QCoreApplication::applicationDirPath();
    QString endPath = Path + "/config.ini";
    QFileInfo fileinfo(endPath);
    if (!fileinfo.isFile()) {
        qDebug() << "文件不存在";
    }
    QSettings setting(endPath, QSettings::IniFormat);
    setting.beginGroup("APP");
    //读配置文件
    //写入配置文件
    setting.setValue("AppSecret", m_ptrLineEditAppSecret->text());
    setting.setValue("Token", m_ptrLineEditToken->text());
}

void MainWindow::initUI()
{
    m_ptrLayoutApp->addWidget(m_ptrLabAppSecret, 0, 0);
    m_ptrLayoutApp->addWidget(m_ptrLineEditAppSecret, 0, 1);
    m_ptrLineEditAppSecret->setEchoMode(QLineEdit::Password);
    m_ptrLayoutApp->addWidget(m_ptrLabAppToken, 1, 0);
    m_ptrLayoutApp->addWidget(m_ptrLineEditToken, 1, 1);
    m_ptrLineEditToken->setEchoMode(QLineEdit::Password);
    m_ptrLayoutMain->addLayout(m_ptrLayoutApp);

    m_ptrLayoutMain->addWidget(m_ptrTextEditInput);

    m_ptrLayoutConfig->addWidget(m_ptrCmbSource);
    m_ptrLayoutConfig->addWidget(m_ptrLabText);
    m_ptrLayoutConfig->addWidget(m_ptrCmbTraget);
    m_ptrLayoutMain->addLayout(m_ptrLayoutConfig);

    m_ptrCmbTraget->addItem("英语");
    m_ptrCmbTraget->addItem("日语");

    m_ptrLayoutMain->addWidget(m_ptrTextEditOutput);
    m_ptrLayoutMain->addWidget(m_ptrBtnDowork);

    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_ptrBtnDowork, SIGNAL(clicked()), this, SLOT(slotDowork()));
    connect(managerData, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotGetOuput(QNetworkReply *)));
    connect(manager, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(slotGetToken(QNetworkReply *)));
}

void MainWindow::getToken()
{
    // 发送https请求前准备工作;
    QSslConfiguration config;
    QNetworkRequest request;
    QByteArray post_Array;
    QJsonDocument doc;
    QSslConfiguration conf = request.sslConfiguration();
    //    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    //    conf.setProtocol(QSsl::TlsV1_1);
    //    request.setSslConfiguration(conf);

    request.setUrl(QUrl(m_strTokenUrl));  // "https://www.temp.com"
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json"));

    QByteArray postData;
    postData.append("grant_type=client_credentials&client_id=" +
                    m_ptrLineEditAppSecret->text() +
                    "&client_secret=" + m_ptrLineEditToken->text());

    qInfo() << "post_Array:" << post_Array;
    QNetworkReply *pReply = manager->post(request, postData);
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this,
            SLOT(onHttpGetError(QNetworkReply::NetworkError)));
}

void MainWindow::slotGetToken(QNetworkReply *reply)
{
    QVariant variant;
    QJsonParseError jsonError;

    QByteArray rece = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(rece, &jsonError);
    QJsonObject json_obj = json_doc.object();
    QJsonValue jsonRefresh_token = json_obj.value("refresh_token");
    QJsonValue jsonAccess_token = json_obj.value("access_token");
    qInfo() << "Refresh_token:" << jsonRefresh_token.toString();
    qInfo() << "Access_token:" << jsonAccess_token.toString();
    qInfo() << QString(rece);
    QString url = m_strApiUrl + "?access_token=" + jsonAccess_token.toString();
    QJsonObject jsonPostData;
    jsonPostData.insert(
        "q",
        QJsonValue(m_ptrTextEditInput->toPlainText().toStdString().c_str()));
    jsonPostData.insert("from", "auto");
    jsonPostData.insert("to", getTarget());
    QByteArray strpostData = QJsonDocument(jsonPostData).toJson();
    qInfo() << "strpostData:" << strpostData;
    QNetworkRequest request;
    request.setUrl(QUrl(url));  // "https://www.temp.com"
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json"));
    QNetworkReply *pReply = managerData->post(request, strpostData);
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this,
            SLOT(onHttpGetError(QNetworkReply::NetworkError)));
}

void MainWindow::slotGetOuput(QNetworkReply *reply)
{
    QByteArray rece = reply->readAll();
    qInfo() << rece;
    QJsonParseError jsonError;
    QJsonDocument json_doc = QJsonDocument::fromJson(rece, &jsonError);
    QJsonObject jsonPostData = json_doc.object();
    QJsonObject jsonResult = jsonPostData.value("result").toObject();
    QJsonValue jsontRans_result = jsonResult.value("trans_result");
    QJsonArray jsontRans_resulta = jsontRans_result.toArray();
    qInfo() << "jsontRans_resulta" << jsontRans_resulta;

    QJsonObject jsonDst = jsontRans_resulta.at(0).toObject();
    qInfo() << "json_doc2:" << jsonDst;
    QString strDst = jsonDst.value("dst").toString();
    qInfo() << "jsonDst:" << strDst;
    m_ptrTextEditOutput->setText(strDst);
}

void MainWindow::onHttpGetError(QNetworkReply::NetworkError code)
{
    QMetaEnum metaMnum = QMetaEnum::fromType<QNetworkReply::NetworkError>();
    QString error = metaMnum.valueToKey(code);
    qWarning() << "地址调用失败 ：" << error;
}

QString MainWindow::getTarget()
{
    switch (m_ptrCmbTraget->currentIndex()) {
        case 0:
            return "en";
        case 1:
            return "jp";
    }
    return "jp";
}
void MainWindow::slotDowork()
{
    saveConfig();
    getToken();
}
