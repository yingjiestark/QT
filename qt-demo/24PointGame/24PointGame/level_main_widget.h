#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QBoxLayout>
#include "level_widget.h"
#include <QPushButton>
class LevelMainWidget : public QWidget {
    Q_OBJECT

   public:
    LevelMainWidget(QWidget *parent = nullptr);
    void unlockLevel(int level);  // 更新解锁按钮状态
    int m_preIndex = 0;

    QList<LevelWidget *> m_listLevelWidget;

    QStackedWidget *m_ptrStackWidget;
    QHBoxLayout *m_ptrLayoutMain;
    QPushButton *m_ptrBtnPre;
    QPushButton *m_ptrBtnNext;
    bool m_bDonghua;
    ~LevelMainWidget();

   private:
    void initConnect();
   signals:
    void sigBtnLevel(int level);
   protected slots:
    void onAnimationFinished();
    void slotBtnPre();
    void slotBtnNext();
    void slotBtnLevel(int level);
};

#endif  // WIDGET_H
