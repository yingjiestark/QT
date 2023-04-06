#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "numitem.h"
#include "pdf_manager.h"
class MainWindowPrivate;
// 考试试卷生成器
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    MainWindowPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(MainWindow)
    Q_DISABLE_COPY(MainWindow)
    PDFManager pdfManager;
   public slots:
    void slotDoWrite();
    void slotPickPath();
};

#endif  // MAINWINDOW_H
