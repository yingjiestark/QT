#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include "snake.h"
class QPainter;
class QTimer;
class GameWidget : public QWidget {
    Q_OBJECT
   public:
    explicit GameWidget(QWidget *parent = nullptr);

    // 开始游戏
    void start();
    // 结束游戏
    void stop();
    // 暂停游戏
    void pause();

   private:
    void paintBackground(QPainter *painter);
    void paintSnakeBody(QPainter *painter);
    void paintGameInit(QPainter *painter);
    void paintGameOver(QPainter *painter);
    void paintCentreStr(QPainter *painter, QString str);
    void paintFood(QPainter *painter);
    int getRandom(int max);  // 获取0 - max-1的随机数
    Food createFood();

    // 初始化游戏数据
    void init();
   public slots:
    void slotTimeout();

   private:
    QTimer *m_timer;
    snake m_snake;
    Food m_food;
    MoveDirection m_direction;
    int m_score;   // 用户分数
    int m_status;  // 游戏状态
                   // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
   signals:
    void sigUpdateScore(int score);
};

#endif  // GAME_WIDGET_H
