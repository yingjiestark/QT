#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "struct.h"
#include <QVector>

class snake : public QObject {
    Q_OBJECT
   public:
    explicit snake(QObject *parent = nullptr);
    /**
     * @brief 小蛇移动算法
     * @param 小蛇移动方向
     */
    void move(MoveDirection direction);
    /**
     * @brief 是否碰撞到自己的身体
     * @return true：碰撞到了，false：没有碰撞到
     */
    bool isHitItself();
    /**
     * @brief 是否超出游戏边界
     * @return true超出游戏边界，false未超出游戏边界
     */
    bool isBeyoudBoundary();
    /**
     * @brief 是否吃到了食物，如果吃到了，将食物坐标添加到蛇头
     * @param food
     * @return
     */
    bool isEatFood(Food food);
    // 初始化蛇的长度以及位置W
    void init();
    QVector<SnakeBoy> m_bodys;
};

#endif  // SNAKE_H
