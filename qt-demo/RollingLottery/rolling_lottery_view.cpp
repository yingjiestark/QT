#include "rolling_lottery_view.h"
#include <QtDebug>
#include <QPainter>
RollingLotteryView::RollingLotteryView(int num, QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(new QHBoxLayout(this))
    , d_ptr(new RollingLotteryViewPrivate(this))

{
    Q_D(RollingLotteryView);
    for (int i = 0; i < num; i++) {
        NumItem *item = new NumItem(5);
        connect(item, &NumItem::sigStop, this, &RollingLotteryView::slotStop);
        item->setSpeed(4 + i);
        d->m_listNum.push_back(item);
        m_mainLayout->addWidget(item);
    }
}

bool RollingLotteryView::setItemBackground(QImage img)
{
    Q_D(RollingLotteryView);
    foreach (auto item, d->m_listNum) {
        item->setBackground(img);
    }
    return true;
}

bool RollingLotteryView::setBackground(QImage img)
{
    Q_D(RollingLotteryView);
    d->m_imgBackground = img;
    return true;
}

bool RollingLotteryView::setItemColor(QColor color)
{
    Q_D(RollingLotteryView);
    foreach (auto item, d->m_listNum) {
        item->setColor(color);
    }
    return true;
}

void RollingLotteryView::start()
{
    Q_D(RollingLotteryView);

    if (d->m_status) {
        qInfo() << "抽奖中，请不要重复点击！";
        return;
    }
    d->m_res = 0;
    // 记录当前需要停止的控件编号。
    d->m_statusNum = d->m_listNum.size() - 1;

    d->m_status = true;
    for (auto item : d->m_listNum) {
        item->startRun();
    }
}

void RollingLotteryView::stop(int num)
{
    Q_D(RollingLotteryView);
    if (!d->m_status) {
        qInfo() << "停止中，请不要重复点击！";
        return;
    }
    d->m_stopNum = num;

    if(num == -1){
        d->m_listNum.at(d->m_statusNum)->stopRun();
    }
    else {
        d->m_listNum.at(d->m_statusNum)->stopRun(num%10);

    }


}

void RollingLotteryView::paintEvent(QPaintEvent *)
{
    Q_D(RollingLotteryView);
    if (d->m_imgBackground.isNull()) return;
    QPainter painter(this);
    QRect target(0, 0, this->size().width(), this->size().height());
    painter.drawImage(target, d->m_imgBackground);
}

void RollingLotteryView::slotStop(int num)
{
    Q_D(RollingLotteryView);
    qInfo() << "slotStop num:" << num;
    for (int i = 0; i < d->m_listNum.size() - d->m_statusNum - 1; i++) {
        num *= 10;
    }
    d->m_res += num;
    if (d->m_statusNum == 0) {
        d->m_status = false;

        sigStop(d->m_res);
        qInfo() << "d->m_res:" << d->m_res;
        return;
    }
    d->m_statusNum--;
    if(d->m_stopNum == -1){
        d->m_listNum.at(d->m_statusNum)->stopRun();
    }
    else{
        int temp = 1;
        for (int i = 0; i < d->m_listNum.size() - d->m_statusNum - 1; i++) {
            temp *= 10;
        }
        int res = (d->m_stopNum / temp) % 10;
        d->m_listNum.at(d->m_statusNum)->stopRun(res);
    }

}
