#ifndef LARCFONT_H
#define LARCFONT_H

#include <QWidget>
#include "LSingleFont.h"
#include <QTimer>
class LArcFont : public QWidget {
    Q_OBJECT
   public:
    explicit LArcFont(QWidget *parent = nullptr);

    explicit LArcFont(QString str, int Shaftx, int Shafty);
    explicit LArcFont(QString str, int radius);
    void start();
    void stop();
    void drawChar(int Shaftx, int Shafty, int jiaodu, QString c, QPainter *p);

   public slots:
    void slotTimeOut();

   private:
    QTimer *m_time;
    int m_Shaftx;
    int m_Shafty;
    int m_jiaodu;
    int m_mousex;
    int m_mousey;
    QString m_str;
    QList<LSingleFont *> m_listChar;
   signals:

   public slots:

    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
   protected:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif  // LARCFONT_H
