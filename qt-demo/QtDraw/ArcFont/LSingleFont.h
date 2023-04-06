#ifndef LSINGLEFONT_H
#define LSINGLEFONT_H

#include <QLabel>
class LSingleFont : public QLabel {
   public:
    LSingleFont(QChar c, int angle = 0, QWidget *parent = nullptr);
    QChar m_char;
    int m_iAngle;
    int m_iFontWidth;
    int m_iFontHeight;
    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *);
};

#endif  // LSINGLEFONT_H
