#include "level_button.h"
#include <QPainter>
#include <QtDebug>
LevelButton::LevelButton(int level)
    : m_bSelectStatus(false)
    , m_bLockStatus(true)
    , m_level(level)
{
    this->setFixedSize(60, 60);
    setFocusPolicy(Qt::NoFocus);
}

bool LevelButton::getSelectStatus() { return m_bSelectStatus; }

void LevelButton::setSelectStatus(bool status) { m_bSelectStatus = status; }

void LevelButton::setSelected() { m_bSelectStatus = true; }

void LevelButton::setUnlock()
{
    m_bLockStatus = false;
    update();
}

bool LevelButton::getLockStatus() { return m_bLockStatus; }

void LevelButton::setLockStatus(bool bLockStatus)
{
    m_bLockStatus = bLockStatus;
    update();
}

void LevelButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    if (m_bLockStatus) {
        QPixmap img(":/resources/suo.png");
        painter.drawPixmap(12, 12, this->width() - 24, this->height() - 28,
                           img);
    } else {
        QFont f;
        if (m_level < 100) {
            f.setPointSize(20);
        } else {
            f.setPointSize(19);
        }
        QFontMetrics fm(f);
        int izw = fm.width(QString::number(m_level));
        int izh = fm.height();

        painter.setFont(f);
        painter.drawText((this->width() - izw) / 2, (this->width() - izh) / 2,
                         izw, izh, 1, QString::number(m_level));
    }
}
