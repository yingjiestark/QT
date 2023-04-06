#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QNetworkReply>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readConfig();  // 保存配置文件
    void saveConfig();  // 读取配置文件
    void initUI();
    void initConnect();
    void getToken();
   public slots:
    void slotGetToken(QNetworkReply *reply);
    void slotGetOuput(QNetworkReply *reply);
    void onHttpGetError(QNetworkReply::NetworkError code);

   private:
    QWidget *m_ptrWdgMain;
    QLabel *m_ptrLabAppSecret;
    QLineEdit *m_ptrLineEditAppSecret;
    QLabel *m_ptrLabAppToken;
    QLineEdit *m_ptrLineEditToken;
    QGridLayout *m_ptrLayoutApp;
    QVBoxLayout *m_ptrLayoutMain;
    QTextEdit *m_ptrTextEditInput;
    QTextEdit *m_ptrTextEditOutput;
    QComboBox *m_ptrCmbSource;
    QComboBox *m_ptrCmbTraget;
    QLabel *m_ptrLabText;
    QHBoxLayout *m_ptrLayoutConfig;
    QPushButton *m_ptrBtnDowork;
    QString m_strApiUrl;
    QString m_strTokenUrl;
    QNetworkAccessManager *manager;      // = new QNetworkAccessManager(this);
    QNetworkAccessManager *managerData;  // = new QNetworkAccessManager(this);
    QString getTarget();
   public slots:

    void slotDowork();
};

#endif  // MAINWINDOW_H
