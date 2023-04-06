#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
class RollingLotteryView;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    RollingLotteryView *m_mainview;
    QPushButton *m_btn;
    bool m_status;
    bool m_windowStatus; // 窗口状态用于记录窗口是否是全屏
    ~MainWindow();
   public slots:
    void slotClickBtn();
    void slotStop(int num);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif  // MAINWINDOW_H
