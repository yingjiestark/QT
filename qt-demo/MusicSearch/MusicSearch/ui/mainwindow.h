#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class SreachWidget;
class QPushButton;
class PlayerWidget;
class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    // 初始化界面
    void initUI();
    // 初始化信号曹函数。
    void initConnect();
    QWidget *m_ptrWdgMain;          // 主界面
    QButtonGroup *m_buttonGrp;      // 按钮组，用于切换界面使用的按钮
    QPushButton *m_ptrBtnSreach;    // 点击搜索按钮，界面切换到搜索功能界面
    QPushButton *m_ptrBtnPlayer;    // 点击播放按钮，界面切换到播放功能界面
    QVBoxLayout *m_ptrLayoutMain;   // 主界面中的布局，使用垂直布局方式。
    QHBoxLayout *m_ptrLayoutBtn;    // 按钮界面的界面布局，使用水平布局方式，并排放置
    QHBoxLayout *m_ptrLayoutContent;    // 内容界面布局。

    QStackedWidget *m_ptrStackView; //
    SreachWidget *m_ptrWdgSreach;   // 搜索功能界面
    PlayerWidget *m_ptrWdgPlayer;   // 播放功能界面
   public slots:
    void slotClickShSLOTow(int index);  // 点击按钮组
};

#endif  // MAINWINDOW_H
