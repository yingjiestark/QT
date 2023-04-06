#include "mainwindow.h"
#include "units_tools.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    UnitsTools tools;
    //  tools.PxToMM(1076);
    //   tools.PxToPt(1076);
    PhysicsDistance res;
    res = tools.x_MMToPx(210);
    res.log();
    res = tools.y_MMToPx(297);
    res.log();
}

MainWindow::~MainWindow() {}
