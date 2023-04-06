#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
class QPushButton;
class QHBoxLayout;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QHBoxLayout *m_mainLayout;
    QWidget *m_main;
    QPushButton *m_btn;
   public slots:
    void clickPrinter();
    void slotPrintReviewPaint(QPrinter *printer);
};

#endif  // MAINWINDOW_H
