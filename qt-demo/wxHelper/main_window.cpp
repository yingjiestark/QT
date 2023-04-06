#include "main_window.h"
#include <QtDebug>
#include <QNetworkRequest>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrMainWiget(new QLoginWidget(this))
    , m_ptrContentWidget(new ContentWidget(this))
{
    initConnect();
    setCentralWidget(m_ptrMainWiget);
}

MainWindow::~MainWindow() {}

void MainWindow::initConnect()
{
    connect(m_ptrMainWiget, &QLoginWidget::finishLogin, this,
            &MainWindow::finishLogin);
}

void MainWindow::finishLogin(userTokenInfo userInfo, QNetworkRequest req)
{
    qInfo() << "userInfo " << userInfo.skey;
    m_ptrContentWidget->setUserInfo(userInfo);
    m_ptrContentWidget->initData(req);
    setCentralWidget(m_ptrContentWidget);
}
