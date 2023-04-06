#ifndef NUM_ITEM_H
#define NUM_ITEM_H

#include <QWidget>
class QTimer;
class NumItem : public QWidget {
    Q_OBJECT
   public:
    NumItem(int num = 8);
    void setSpeed(int speed);
    void setBackground(QImage img);
    void setColor(QColor color);
    void startRun();
    void stopRun(int num = -1);
    int getNum();
   public slots:
    void on_timer_timeout();

   private:
    int m_num;  // 初始化数据
    int m_resNum; // 设置指定数据,停止
    QTimer *m_timer;
    int m_speed;
    int m_height;
    QColor m_color;
    QImage m_imgBackground;
    bool m_status;  // 记录抽奖状态
                    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);
   signals:
    void sigStop(int num);
};

#endif  // NUM_ITEM_H
