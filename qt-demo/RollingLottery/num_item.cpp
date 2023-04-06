#include "num_item.h"
#include <QTimer>
#include <QPainter>
#include <QtDebug>
NumItem::NumItem(int num)
    : m_num(num)
    , m_resNum(-1)
    , m_timer(new QTimer())
    , m_speed(100)
    , m_height(0)
    , m_status(false)

{
    QFont qf;
    qf.setPointSize(2);
    qf.setPixelSize(100);
    QFontMetrics qfm(qf);
    int a = qfm.width("1");
    int b = qfm.height();
    setFixedSize(a, b);
    // resize(;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    m_timer->stop();
}

void NumItem::setSpeed(int speed) { m_speed = speed; }

void NumItem::startRun()
{
    m_timer->setInterval(m_speed);
    m_timer->start();
    m_status = true;
}

void NumItem::stopRun(int num)
{
    qInfo() << "stopRun";
    m_resNum = num;
    m_status = false;
}

int NumItem::getNum() { return m_num; }

void NumItem::setBackground(QImage img) { m_imgBackground = img; }

void NumItem::setColor(QColor color) { m_color = color; }

void NumItem::on_timer_timeout()
{
    m_height += 5;
    QFont qf;
    qf.setPointSize(2);
    qf.setPixelSize(100);
    QFontMetrics qfm(qf);
    int b = qfm.height();
    if (m_height > b) {
        m_height = m_height % b;

        if (m_num == 0) {
            m_num = 9;
        } else {
            m_num--;
        }
        if (!m_status) {
            if (m_resNum == -1) {
                sigStop(m_num);
                m_timer->stop();
            } else if (m_resNum == m_num) {
                sigStop(m_num);
                m_timer->stop();
            }
        }
    }
    update();
}

void NumItem::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont qf;
    QPen pen(m_color);
    p.setPen(pen);
    qf.setPointSize(2);
    qf.setPixelSize(100);
    QFontMetrics qfm(qf);
    int a = qfm.width("1");
    int b = qfm.height();
    p.setFont(qf);
    p.drawText(0, m_height, a, b, 1, QString::number(m_num));
    p.drawText(0, m_height - b, a, b, 1, QString::number(m_num - 1));
    if (m_imgBackground.isNull()) {
        return;
    }
    QPainter painter(this);
    QRect target(0, 0, this->size().width(), this->size().height());
    painter.drawImage(target, m_imgBackground);
}
