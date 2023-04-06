#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "drawing_paper_view.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    QDrawingPaperView *m_drawingPaperView;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif  // MAINWINDOW_H
