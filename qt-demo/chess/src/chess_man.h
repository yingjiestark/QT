#ifndef CHESS_MAN_H
#define CHESS_MAN_H

#include <QObject>
#include <QGraphicsItem>
#include "common.h"
/**
 * @brief 棋子
 */
class Chessman : public QObject, public QGraphicsItem {
    Q_OBJECT
   public:
    explicit Chessman(int width, ChessType type, QObject *parent = nullptr);

   private:
    int x;             // 在棋盘上的X坐标
    int y;             // 在棋盘上的Y坐标
    ChessType m_type;  // 棋子类型
    int m_width;
    int m_x;
    int m_y;
    bool m_Selectedstatus;  // 状态是否被选中
    bool m_isLive;          // 是否存活

   signals:
    void sigClick();
   public slots:

    // QGraphicsItem interface
   public:
    bool getLive();
    void setLive(bool live);
    void setSelectedStatus(bool status);
    bool getSelectedStatus();
    ChessType getChessType();
    void initPos();
    void Move(int x, int y);
    int getX();
    int getY();
    // 为图元限定区域范围，必须实现
    QRectF boundingRect() const;
    // 绘制
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void paintCheB(QPainter *painter);
    void paintMaB(QPainter *painter);
    void paintXiangB(QPainter *painter);
    void paintShiB(QPainter *painter);
    void paintJiangB(QPainter *painter);
    void paintPaoB(QPainter *painter);
    void paintBingB(QPainter *painter);

    void paintCheR(QPainter *painter);
    void paintMaR(QPainter *painter);
    void paintXiangR(QPainter *painter);
    void paintShiR(QPainter *painter);
    void paintJiangR(QPainter *painter);
    void paintPaoR(QPainter *painter);
    void paintBingR(QPainter *painter);

    void paintBlackChess(QPainter *painter, QString str);
    void paintRedChess(QPainter *painter, QString str);
};

#endif  // CHESS_MAN_H
