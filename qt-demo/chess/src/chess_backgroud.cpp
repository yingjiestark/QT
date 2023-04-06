#include "chess_backgroud.h"
#include <QPainter>
#include <QtDebug>
#include <QGraphicsSceneMouseEvent>
#include <QFontDatabase>
#include "common.h"
ChessBackgroud::ChessBackgroud(int width, QObject *parent)
    : QObject(parent)
    , m_width(width)
{
    pix.load(QString(":/1.jpg"));
    m_h_width = width / 10;
    m_v_width = width / 10;
}

QRectF ChessBackgroud::boundingRect() const
{
    return QRectF(0, 0, m_width, m_width);
}

void ChessBackgroud::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/bamboo.jpg");
    painter->drawPixmap(0, 0, pixmap);
    painter->setPen(QPen(QBrush(Qt::black), 1, Qt::SolidLine));
    int limit_i = 8;
    int limit_j = 9;
    int top = (m_width - limit_i * m_h_width) / 2;
    int left = (m_width - limit_j * m_h_width) / 2;
    for (int i = 0; i <= limit_i; i++) {
        if (i == 0 || i == limit_i) {
            painter->drawLine(top + m_h_width * i, left + m_v_width * 0,
                              top + m_h_width * i, left + m_v_width * 9);
        } else {
            painter->drawLine(top + m_h_width * i, left + m_v_width * 0,
                              top + m_h_width * i, left + m_v_width * 4);
            painter->drawLine(top + m_h_width * i, left + m_v_width * 5,
                              top + m_h_width * i, left + m_v_width * 9);
        }
    }
    for (int j = 0; j <= limit_j; j++) {
        painter->drawLine(top + m_h_width * 0, left + m_v_width * j,
                          top + m_h_width * 8, left + m_v_width * j);
    }

    // 绘制士的移动路径
    painter->drawLine(top + m_h_width * 3, left + m_v_width * 0,
                      top + m_h_width * 5, left + m_v_width * 2);
    painter->drawLine(top + m_h_width * 5, left + m_v_width * 0,
                      top + m_h_width * 3, left + m_v_width * 2);

    painter->drawLine(top + m_h_width * 3, left + m_v_width * 7,
                      top + m_h_width * 5, left + m_v_width * 9);
    painter->drawLine(top + m_h_width * 5, left + m_v_width * 7,
                      top + m_h_width * 3, left + m_v_width * 9);

    // 绘制棋盘最外的粗黑框
    int margin = 7;
    painter->setPen(QPen(QBrush(Qt::black), 4, Qt::SolidLine));
    painter->drawRect(top - margin, left - margin,
                      top + m_v_width * 7 + margin * 2,
                      top + m_h_width * 8 + margin * 2);
    // 绘制楚河汉界
    QFont font = painter->font();  //设置字体，下面设置字体属性
    qInfo() << font;
    font.setFamily("CESI楷体-GB13000");
    //    QFontDatabase database;
    //    for (QString family : database.families()) {
    //        qInfo() << "Family:" << family;
    //    }
    font.setPointSize(g_cell_width * 0.35);  //字体点大小
    painter->setFont(font);
    //  painter->setPen(QPen(QColor(163, 0, 0), 3, Qt::SolidLine));
    qInfo() << painter->font();
    painter->drawText(top + m_h_width * 1, left + m_v_width * 4, g_cell_width,
                      g_cell_width, Qt::AlignCenter, "楚");
    painter->drawText(top + m_h_width * 2, left + m_v_width * 4, g_cell_width,
                      g_cell_width, Qt::AlignCenter, "河");
    painter->drawText(top + m_h_width * 5, left + m_v_width * 4, g_cell_width,
                      g_cell_width, Qt::AlignCenter, "汉");
    painter->drawText(top + m_h_width * 6, left + m_v_width * 4, g_cell_width,
                      g_cell_width, Qt::AlignCenter, "界");
}
