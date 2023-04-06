#ifndef ROLLINH_LOTTERY_VIEW_P_H
#define ROLLINH_LOTTERY_VIEW_P_H
#include <QHBoxLayout>
#include <QList>
#include "num_item.h"
class RollingLotteryView;
class RollingLotteryViewPrivate {
    Q_DECLARE_PUBLIC(RollingLotteryView)
   public:
    RollingLotteryViewPrivate(RollingLotteryView *ptr);
    ~RollingLotteryViewPrivate();
    QList<NumItem *> m_listNum;
    QImage m_imgBackground;  // 抽奖背景图
    bool m_status;           // 抽奖状态
    int m_res;               // 最终的展示结果
    int m_statusNum;  // 由于抽奖停止按照循序停止，因此需要记录当前停止的控件位置。
    int m_stopNum;    // 指定数据停止

   private:
    RollingLotteryView *q_ptr;
};

#endif  // ROLLINH_LOTTERY_VIEW_P_H
