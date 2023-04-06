#ifndef LEVEL_BUTTON_H
#define LEVEL_BUTTON_H
#include <QPushButton>

class LevelButton : public QPushButton {
    Q_OBJECT
   public:
    LevelButton(int level);
    bool getSelectStatus();
    void setSelectStatus(bool status);
    void setSelected();

    void setUnlock();  // 设置解锁
    bool getLockStatus();
    void setLockStatus(bool bLockStatus);

   private:
    bool m_bSelectStatus;
    bool m_bLockStatus;
    int m_level;

    // QWidget interface
   protected:
    void paintEvent(QPaintEvent *event);
};

#endif  // LEVEL_BUTTON_H
