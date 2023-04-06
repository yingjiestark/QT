#include "LSingleFont.h"
#include <QPainter>

LSingleFont::LSingleFont(QChar c, int angle, QWidget *parent)
    : m_char(c)
    , m_iAngle(angle)
    , QLabel(parent)
{
    int ifontWidth = QFontMetrics(this->font()).width(c);  // 计算一个数字的长度
    int ifontHeight = QFontMetrics(this->font()).height();  // 一个字的高度
    setFixedSize(ifontWidth, ifontHeight);
}

void LSingleFont::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.translate(m_iFontWidth / 2, m_iFontHeight / 2);
    p.drawText(0, 0, m_char);
    p.rotate(m_iAngle);
    p.resetMatrix();
}
