#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel *m_ptrLabHost;
    QLineEdit *m_ptrLineEditHostName;
    QPushButton *m_ptrBtnDetail;
    QWidget *m_ptrWdgMain;
    QGridLayout *m_ptrLayoutMain;

   private:
    void initUI();
    void initConnect();
   public slots:
    void slotGetNetWorkDetail();
};

#endif  // MAINWINDOW_H
