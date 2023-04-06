#include "num_button.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QBrush>
#include <QtMath>
NumButton::NumButton(int num, QPushButton *parent)
    : QPushButton(parent)
    , m_value(num)

{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    update();
}

NumButton::NumButton(int fenzi, int fenmu, QPushButton *parent)
    : QPushButton(parent)
    , m_value(fenzi, fenmu)
{
}

void NumButton::setSelectStatus(bool status)
{
    m_status = status;
    QPalette pal = this->palette();

    update();
}

bool NumButton::getSelectStatus() { return m_status; }

void NumButton::setType(int type) { m_iType = type; }

int NumButton::getType() { return m_iType; }

LNum NumButton::getValue() { return m_value; }

void NumButton::setVale(LNum num)
{
    m_value = num;
    update();
}

void NumButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    setText(QString::number(m_value.data()));
    if (!m_status) {
        painter.fillRect(rect(), QColor(255, 255, 255));
    } else {
        //实例阴影shadow
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.fillRect(10,10,this->width() -2*10 ,this->height() - 2 *10 ,QBrush(Qt::white));
        QColor color(255,0,0);
        for(int i = 0 ;i < 10 ; i ++){
            painter.setPen(color);
             painter.drawRoundedRect(10 -i,10-i,this->width() -2*(10 -i ) ,this->height() - 2 *(10 -i ) ,6,6);
        }

    }

    QPushButton::paintEvent(event);
}
