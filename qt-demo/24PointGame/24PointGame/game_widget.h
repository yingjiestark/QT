#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "num_button.h"
#include "lnum.h"
#include "common.h"
#include <QLabel>
class GameWidget : public QWidget {
    Q_OBJECT
   public:
    explicit GameWidget(QWidget *parent = nullptr);

   private:
    QVBoxLayout *m_ptrLayoutMain;
    QHBoxLayout *m_ptrLayoutBtn;
    QLabel *m_ptrLabTitle;
    QGridLayout *m_ptrLayoutGame;
    QPushButton *m_ptrBtnBack;
    QPushButton *m_ptrBtnInitGame;
    NumButton *m_ptrBtnNum1;
    NumButton *m_ptrBtnNum2;
    NumButton *m_ptrBtnNum3;
    NumButton *m_ptrBtnNum4;
    QPushButton *m_ptrBtnOption1;
    QPushButton *m_ptrBtnOption2;
    QPushButton *m_ptrBtnOption3;
    QPushButton *m_ptrBtnOption4;

    int m_iCurrentLevel;  // 当前的游戏关卡数

    QList<NumItem> m_listNumSelect;
    QList<OptionItem> m_listOptionSelect;

   public:
    void initUI();
    void intiConnect();
    void initGame();
    void setCurrentLevel(int level);
    void jisuan();

   signals:
    void sigBtnBack();
    void sigUnlockLevel(int level);
   public slots:
    void slotBtnBack();
    void slotBtnClickNum();     // 点击数字
    void slotBtnClickOption();  // 点击计算符号
    void slotBtnClickInitGame();
};

#endif  // GAME_WIDGET_H
