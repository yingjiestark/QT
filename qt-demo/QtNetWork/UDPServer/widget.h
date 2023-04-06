#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QUdpSocket>

class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = nullptr);
    QTextEdit *m_ptrTextEditContent;
    QUdpSocket *m_ptrUdpServer;
    ~Widget();

   private:
    void initUI();
    void initServerSokcet();
    void readPendingDatagrams();
};
#endif  // WIDGET_H
