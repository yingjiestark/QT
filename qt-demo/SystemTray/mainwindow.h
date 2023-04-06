#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSystemTrayIcon>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   public slots:
    void slotShowTray();
    void slotActionTray();
    void slotActionTrayTimeout();
    void slotActionSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

   private:
    QWidget *m_mainView;
    QTimer *m_timer;
    int m_num;
    QSystemTrayIcon *m_systemTray;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_btnShow;
    QPushButton *m_btnAction;
    QMenu *m_pPreMenu;

   protected:
    void changeEvent(QEvent *);
};

#endif  // MAINWINDOW_H
