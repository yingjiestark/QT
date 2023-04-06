#ifndef LEVEL_WIDGET_H
#define LEVEL_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
/**
 * @brief 关卡展示类
 */
class LevelWidget : public QWidget {
    Q_OBJECT
   public:
    explicit LevelWidget(QWidget *parent = nullptr);
    explicit LevelWidget(int start, int end);
    void unLockLevel(int level);
    QGridLayout *m_layoutMain;
   signals:
    void sigBtnClick(int level);
   public slots:
    void slotBtnClick();
};

#endif  // LEVEL_WIDGET_H
