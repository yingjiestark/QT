#include "game_widget.h"
#include <QPainter>
#include "config.h"
#include <QTimer>
#include <QtDebug>
#include <QKeyEvent>
#include <QTime>
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , m_timer(new QTimer(this))
    , m_direction(moveTop)
    , m_status(0)
{
    qsrand(static_cast<uint>(QTime(0, 0, 0).secsTo(QTime::currentTime())));
    setFocusPolicy(Qt::ClickFocus);
    setFixedSize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::slotTimeout);
    m_food = createFood();
}

void GameWidget::start()
{
    setFocus();
    init();
    m_timer->start();
    m_status = 1;
}

void GameWidget::stop()
{
    setFocus();
    init();
    m_timer->stop();
}

void GameWidget::pause() { m_timer->stop(); }

void GameWidget::paintBackground(QPainter *painter)
{
    QPen pen = painter->pen();
    pen.width();
    painter->drawLine(0, 0, 0, this->height());
    painter->drawLine(GAME_WINDOW_WIDTH - pen.width(), 0,
                      GAME_WINDOW_WIDTH - pen.width(), this->height());
    painter->drawLine(0, 0, this->width(), 0);
    painter->drawLine(0, GAME_WINDOW_HEIGHT - pen.width(), this->width(),
                      GAME_WINDOW_HEIGHT - pen.width());
}

void GameWidget::paintSnakeBody(QPainter *painter)
{
    QPainterPath path;
    int i = 0;
    foreach (auto item, m_snake.m_bodys) {
        QRectF body = QRectF(item.x * BLOCK_WIDHT, item.y * BLOCK_WIDHT,
                             BLOCK_WIDHT, BLOCK_WIDHT);
        // 绘画蛇头
        if (i == 0) {
            painter->setBrush(Qt::red);
            painter->setPen(Qt::red);
            painter->drawRect(body);
        } else {
            // 绘画蛇身
            painter->setBrush(Qt::transparent);
            painter->setPen(Qt::red);
            painter->drawRect(body);
        }
        i = 1;
    }
}

void GameWidget::paintGameInit(QPainter *painter)
{
    paintCentreStr(painter, "贪吃蛇");
}

void GameWidget::paintGameOver(QPainter *painter)
{
    paintCentreStr(painter, "Game Over!");
}

void GameWidget::paintCentreStr(QPainter *painter, QString str)
{
    QFont font;
    font.setPixelSize(50);
    painter->setFont(font);
    QFontMetrics fm(font);
    painter->drawText((GAME_WINDOW_WIDTH / 2) - (fm.width(str) / 2),
                      (GAME_WINDOW_HEIGHT / 2), str);
}
void GameWidget::paintFood(QPainter *painter)
{
    QPainterPath path;
    path.addEllipse(QRectF(m_food.x * BLOCK_WIDHT + 2,
                           m_food.y * BLOCK_WIDHT + 2, BLOCK_WIDHT - 4,
                           BLOCK_WIDHT - 4));
    painter->fillPath(path, QBrush(QColor(0, 255, 0)));
}

int GameWidget::getRandom(int max)
{
    int res = qrand();
    res = res % max;
    qInfo() << "random:" << res;
    return res;
}

Food GameWidget::createFood()
{
    Food food;
    bool flat = false;
    do {
        flat = false;
        food.x = getRandom(GAME_MAX_W);
        food.y = getRandom(GAME_MAX_H);
        foreach (auto item, m_snake.m_bodys) {
            if (food.x == item.x && food.y == item.y) {
                flat = true;
            }
        }
        qInfo()<<"food.x:"<<food.x;
        qInfo()<<"food.y:"<<food.y;
    } while (flat);
    return food;
}

void GameWidget::init()
{
    // 初始化食物位置
    m_food = createFood();
    // 初始化用户分数
    m_score = 0;
    emit sigUpdateScore(m_score);
    // 初始化蛇的长度
    m_snake.init();
}

void GameWidget::slotTimeout()
{
    if (m_snake.isEatFood(m_food)) {
        m_food = createFood();
        m_score++;
        emit sigUpdateScore(m_score);
    }
    m_snake.move(m_direction);
    // 判断是否是撞到自己
    if (m_snake.isHitItself()) {
        m_status = gameOver;
        m_timer->stop();
    } else if (m_snake.isBeyoudBoundary()) {  // 判断是否超出游戏边框
        m_status = gameOver;
        m_timer->stop();
    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintBackground(&painter);
    if (gameStart == m_status) {
        paintFood(&painter);
        paintSnakeBody(&painter);
    } else if (gameInit == m_status) {
        paintGameInit(&painter);
    } else {
        paintGameOver(&painter);
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    qInfo() << "keyPressEvent start";
    switch (event->key()) {
        case Qt::Key_Up:
            if (m_direction != moveBottom) m_direction = moveTop;
            break;
        case Qt::Key_Left:
            qInfo() << "moveLeft";
            if (m_direction != moveRight) m_direction = moveLeft;
            break;
        case Qt::Key_Right:
            qInfo() << "moveRight";
            if (m_direction != moveLeft) m_direction = moveRight;
            break;
        case Qt::Key_Down:
            qInfo() << "moveBottom";
            if (m_direction != moveTop) m_direction = moveBottom;
            break;
    }
}
