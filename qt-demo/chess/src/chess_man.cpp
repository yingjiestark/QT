#include "chess_man.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
Chessman::Chessman(int width, ChessType type, QObject *parent)
    : QObject(parent)
    , m_type(type)
    , m_width(width / 13)
    , m_Selectedstatus(false)
    , m_isLive(true)
{
}

bool Chessman::getLive() { return m_isLive; }

void Chessman::setLive(bool live) { m_isLive = live; }

void Chessman::setSelectedStatus(bool status)
{
    m_Selectedstatus = status;
    update();
}

bool Chessman::getSelectedStatus() { return m_Selectedstatus; }

ChessType Chessman::getChessType() { return m_type; }

void Chessman::Move(int x, int y)
{
    m_x = x;
    m_y = y;

    this->setPos(g_top - g_chess_man_width / 2 + x * g_cell_width,
                 g_left - g_chess_man_width / 2 + y * g_cell_width);
}

int Chessman::getX() { return m_x; }

int Chessman::getY() { return m_y; }

QRectF Chessman::boundingRect() const { return QRectF(0, 0, m_width, m_width); }

void Chessman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    // 如果棋子的生命结束了，那么久不绘制他了。
    if (!m_isLive) {
        return;
    }
    switch (m_type) {
        case Che_R:  // 车 - 红色
            paintCheR(painter);
            break;
        case Ma_R:  // 马 - 红色
            paintMaR(painter);
            break;
        case Xiang_R:  // 象 - 红色
            paintXiangR(painter);
            break;
        case Shi_R:  // 士 - 红色
            paintShiR(painter);
            break;
        case Jiang_R:  // 将 - 红色
            paintJiangR(painter);
            break;
        case Pao_R:  // 炮 - 红色
            paintPaoR(painter);
            break;
        case Bing_R:  // 兵 - 红色
            paintBingR(painter);
            break;
        case Che_B:  // 车 - 黑色
            paintCheB(painter);
            break;
        case Ma_B:  // 马 - 黑色
            paintMaB(painter);
            break;
        case Xiang_B:  // 象 - 黑色
            paintXiangB(painter);
            break;
        case Shi_B:  // 士 - 黑色
            paintShiB(painter);
            break;
        case Jiang_B:  // 将 - 黑色
            paintJiangB(painter);
            break;
        case Pao_B:  // 炮 - 黑色
            paintPaoB(painter);
            break;
        case Bing_B:  // 兵 - 黑色
            paintBingB(painter);
            break;
        default:
            break;
    }
}

void Chessman::paintCheB(QPainter *painter) { paintBlackChess(painter, "车"); }

void Chessman::paintMaB(QPainter *painter) { paintBlackChess(painter, "马"); }

void Chessman::paintXiangB(QPainter *painter)
{
    paintBlackChess(painter, "象");
}

void Chessman::paintShiB(QPainter *painter) { paintBlackChess(painter, "士"); }

void Chessman::paintJiangB(QPainter *painter)
{
    paintBlackChess(painter, "将");
}

void Chessman::paintPaoB(QPainter *painter) { paintBlackChess(painter, "炮"); }

void Chessman::paintBingB(QPainter *painter) { paintBlackChess(painter, "兵"); }

void Chessman::paintCheR(QPainter *painter) { paintRedChess(painter, "车"); }

void Chessman::paintMaR(QPainter *painter) { paintRedChess(painter, "马"); }

void Chessman::paintXiangR(QPainter *painter) { paintRedChess(painter, "相"); }

void Chessman::paintShiR(QPainter *painter) { paintRedChess(painter, "士"); }

void Chessman::paintJiangR(QPainter *painter) { paintRedChess(painter, "帅"); }

void Chessman::paintPaoR(QPainter *painter) { paintRedChess(painter, "炮"); }

void Chessman::paintBingR(QPainter *painter) { paintRedChess(painter, "卒"); }

void Chessman::paintBlackChess(QPainter *painter, QString str)
{
    QBrush b = painter->brush();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::SmoothPixmapTransform |
                            QPainter::Qt4CompatiblePainting);
    painter->setBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));
    painter->drawEllipse(0, 0, m_width, m_width);
    painter->setBrush(b);

    if (m_Selectedstatus) {
        painter->setPen(QPen(Qt::blue, 3, Qt::SolidLine));
    } else {
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
    }
    painter->drawEllipse(0, 0, m_width, m_width);
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
    painter->drawEllipse(6, 6, m_width - 12, m_width - 12);

    QFont font;  //设置字体，下面设置字体属性
    font.setFamily("CESI楷体-GB13000");  //字体样式
    font.setPointSize(m_width * 0.35);   //字体点大小
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
    painter->drawText(0, 0, m_width, m_width, Qt::AlignCenter, str);
}

void Chessman::paintRedChess(QPainter *painter, QString str)
{
    QBrush b = painter->brush();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::SmoothPixmapTransform |
                            QPainter::Qt4CompatiblePainting);
    painter->setBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));
    painter->drawEllipse(0, 0, m_width, m_width);
    painter->setBrush(b);
    if (m_Selectedstatus) {
        painter->setPen(QPen(Qt::blue, 3, Qt::SolidLine));
    } else {
        painter->setPen(QPen(QColor(163, 0, 0), 3, Qt::SolidLine));
    }
    painter->drawEllipse(0, 0, m_width, m_width);
    painter->setPen(QPen(QColor(163, 0, 0), 3, Qt::SolidLine));
    painter->drawEllipse(6, 6, m_width - 12, m_width - 12);

    QFont font;  //设置字体，下面设置字体属性
    font.setFamily("CESI楷体-GB13000");  //字体样式
    font.setPointSize(m_width * 0.35);   //字体点大小
    painter->setFont(font);
    painter->setPen(QPen(QColor(163, 0, 0), 3, Qt::SolidLine));
    painter->drawText(0, 0, m_width, m_width, Qt::AlignCenter, str);
}
