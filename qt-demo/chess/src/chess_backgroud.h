#ifndef CHESS_BACKGROUD_H
#define CHESS_BACKGROUD_H

#include <QObject>
#include <QGraphicsItem>

#define WIDTH 50
class ChessBackgroud : public QObject, public QGraphicsItem {
    Q_OBJECT
   public:
    explicit ChessBackgroud(int width, QObject *parent = nullptr);

   signals:

   public slots:

    // QGraphicsItem interface
   public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPixmap pix;
    int m_width;
    int m_h_width;
    int m_v_width;
};

#endif  // CHESS_BACKGROUD_H
