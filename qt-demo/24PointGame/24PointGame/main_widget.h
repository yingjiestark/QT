#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include "level_main_widget.h"
#include "game_widget.h"
class MainWidget : public QWidget {
    Q_OBJECT
   public:
    explicit MainWidget(QWidget *parent = nullptr);

   private:
    QHBoxLayout *m_ptrLayoutMain;
    QStackedWidget *m_ptrStackWidget;
    LevelMainWidget *m_ptrLevelMainWidget;
    GameWidget *m_ptrGameWidget;

   private:
    void initUI();
    void initConnect();

   signals:

   public slots:
    void slotUnlockLevel(int level);
    void slotBtnClick(int level);
    void slotBtnBack();
};

#endif  // MAIN_WIDGET_H
