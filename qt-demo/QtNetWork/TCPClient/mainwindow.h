#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTcpSocket>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    void initUI();
    void initConnect();

   public slots:
    /**
     * @brief 进入聊天室
     */
    void slotClickEnter();
    /**
     * @brief 发送数据
     */
    void slotClickSendContent();

    void slotConnected();
    void slotDisConnected();
    void slotDataReveived();

   private:
    QWidget *m_ptrWdgMain;
    QGridLayout *m_ptrLayoutMain;
    QListWidget *m_ptrListContent;
    QLineEdit *m_ptrLineEditContent;
    QPushButton *m_ptrBtnSend;
    QLabel *m_ptrLabUserName;
    QLineEdit *m_ptrLineEditUserName;
    QLabel *m_ptrLabAddress;
    QLineEdit *m_ptrLineEditAddress;
    QLabel *m_ptrLabPort;
    QLineEdit *m_ptrLineEditPort;
    QPushButton *m_ptrBtnEnter;
    QTcpSocket *m_ptrClientTcpSocket;
    bool m_status;
};

#endif  // MAINWINDOW_H
