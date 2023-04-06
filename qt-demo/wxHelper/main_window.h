#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login_widget.h"
#include "content_widget.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initConnect();
   public slots:
    void finishLogin(userTokenInfo userInfo, QNetworkRequest req);

   private:
    QLoginWidget *m_ptrMainWiget;
    ContentWidget *m_ptrContentWidget;
};

#endif  // MAINWINDOW_H
