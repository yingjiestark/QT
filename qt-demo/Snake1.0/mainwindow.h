#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class GameWidget;
class QPushButton;
class QLabel;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    GameWidget *m_mainGameView;
    QWidget *m_mainWidget;
    QPushButton *m_btnStart;
    QPushButton *m_btnStop;
    QPushButton *m_btnPause;
    QLabel *m_labScoreStr;
    QLabel *m_labScoreNum;
    ~MainWindow();
   public slots:
    void updateScore(int score);
    // QWidget interface
};

#endif  // MAINWINDOW_H
