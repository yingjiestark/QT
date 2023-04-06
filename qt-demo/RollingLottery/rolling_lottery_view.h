#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H
#include "rollinh_lottery_view_private.h"
#include "num_item.h"

class RollingLotteryView : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(RollingLotteryView)
   public:
    /**
     * @brief RollingLotteryView
     * @param num 抽奖号码个数
     * @param parent
     */
    explicit RollingLotteryView(int num = 1, QWidget *parent = nullptr);
    /**
     * @brief 设置每一个数字的背景
     * @param 背景图片
     * @return
     */
    bool setItemBackground(QImage img);
    /**
     * @brief setBackground
     * @param img
     * @return
     */
    bool setBackground(QImage img);

    bool setItemColor(QColor color);
    /**
     * @brief 开始抽奖
     */
    void start();
    /**
     * @brief 结束抽奖
     */
    void stop(int res = -1);
    // QWidget interface
   private:
    QHBoxLayout *m_mainLayout;
    QScopedPointer<RollingLotteryViewPrivate> d_ptr;

    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);
   signals:
    void sigStop(int num);
   public slots:
    void slotStop(int num);
};

#endif  // MAIN_VIEW_H
