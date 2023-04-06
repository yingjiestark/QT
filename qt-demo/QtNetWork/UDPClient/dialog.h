#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QUdpSocket>
#include <QVBoxLayout>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QUdpSocket *m_ptrUdpClient;
    QTimer *m_ptrTimer;
    QPushButton *m_ptrBtn;
    QVBoxLayout *m_ptrLayoutMain;
    int num ;
    ~Widget();
private:
    void initUI();
    void initConnect();
public slots:
    void slotTimeOut();
    void slotClickBtn();
};
#endif // DIALOG_H
