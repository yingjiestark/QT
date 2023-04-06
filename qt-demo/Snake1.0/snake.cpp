#include "snake.h"
#include "config.h"
snake::snake(QObject *parent)
    : QObject(parent)
{
    SnakeBoy a;
    a.x = 10;
    a.y = 10;
    m_bodys.push_back(a);
}

void snake::move(MoveDirection diretion)
{
    // 保持第一个蛇头不变，先移动蛇的身体
    for (int i = m_bodys.size() - 1; i > 0; i--) {
        if (i != 0) {
            m_bodys[i] = m_bodys[i - 1];
        }
    }
    // 根据移动方向，移动蛇的头部
    switch (diretion) {
        case moveRight:
            m_bodys[0].x += 1;
            break;
        case moveLeft:
            m_bodys[0].x -= 1;
            break;
        case moveTop:
            m_bodys[0].y -= 1;
            break;
        case moveBottom:
            m_bodys[0].y += 1;
            break;
    }
}

bool snake::isHitItself()
{
    for (int i = m_bodys.size() - 1; i > 0; i--) {
        if (i != 0) {
            if (m_bodys.at(0).x == m_bodys[i].x &&
                m_bodys.at(0).y == m_bodys[i].y) {
                return true;
            }
        }
    }
    return false;
}

bool snake::isBeyoudBoundary()
{
    if (m_bodys.at(0).x < 0 || m_bodys.at(0).x >= GAME_MAX_W ||
        m_bodys.at(0).y < 0 || m_bodys.at(0).y >= GAME_MAX_H) {
        return true;
    }
    return false;
}

bool snake::isEatFood(Food food)
{
    if (m_bodys.first().x == food.x && m_bodys.first().y == food.y) {
        SnakeBoy body;
        body.x = food.x;
        body.y = food.y;
        m_bodys.push_front(body);
        return true;
    }
    return false;
}

void snake::init()
{
    m_bodys.clear();
    SnakeBoy a;
    a.x = 10;
    a.y = 10;
    m_bodys.push_back(a);
}
