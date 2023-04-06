#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_drawingPaperView(new QDrawingPaperView(this))
{
    m_drawingPaperView->setMouseTracking(true);
    setCentralWidget(m_drawingPaperView);
    resize(700, 500);
}

MainWindow::~MainWindow() {}
