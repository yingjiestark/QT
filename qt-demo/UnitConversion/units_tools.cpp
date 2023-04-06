#include "units_tools.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QtDebug>
UnitsTools::UnitsTools(QObject *parent)
    : QObject(parent)
{
    QDesktopWidget *mydesk = QApplication::desktop();

    qInfo() << " mydesk->widthMM :" << mydesk->widthMM();
    qInfo() << " mydesk->heightMM :" << mydesk->heightMM();
    qInfo() << " mydesk->width :" << mydesk->width();
    qInfo() << " mydesk->height :" << mydesk->height();
}

PhysicsDistance UnitsTools::PxToMM(double px)
{
    PhysicsDistance res;
    if (px <= 0) {
        return res;
    }
    // PhysicsDistance res;
    QDesktopWidget *mydesk = QApplication::desktop();

    res.x = double(double(px * mydesk->widthMM()) / double(mydesk->width()));
    res.y = double(double(px * mydesk->heightMM()) / double(mydesk->height()));
    return res;
}

PhysicsDistance UnitsTools::PxToPt(double px)
{
    PhysicsDistance res;
    if (px <= 0) {
        return res;
    }
    // PhysicsDistance res;
    QDesktopWidget *mydesk = QApplication::desktop();
    res.x = double((px * double(mydesk->widthMM()) * 1000000) /
                   double(mydesk->width() * 352777));
    res.y = double((px * double(mydesk->heightMM()) * 1000000) /
                   double(mydesk->height() * 352777));
    qInfo() << "resx" << res.x;
    qInfo() << "resy" << res.y;
    return res;
}

PhysicsDistance UnitsTools::x_MMToPx(double mm)
{
    QDesktopWidget *mydesk = QApplication::desktop();
    PhysicsDistance res;
    if (mm <= 0) {
        return res;
    }
    res.x = double(mydesk->width() * mm) / double(mydesk->widthMM());
    //    res.y = double(mydesk->height() * mm) / double(mydesk->heightMM());
    return res;
}

PhysicsDistance UnitsTools::y_MMToPx(double mm)
{
    QDesktopWidget *mydesk = QApplication::desktop();
    PhysicsDistance res;
    if (mm <= 0) {
        return res;
    }
    //   res.x = double(mydesk->width() * mm) / double(mydesk->widthMM());
    res.y = double(mydesk->height() * mm) / double(mydesk->heightMM());
    return res;
}
/**
 * @brief UnitsTools::InchtoMM 1英寸等于25.4毫米
 * @param inch
 * @return
 */
double UnitsTools::InchToMM(double inch)
{
    double res;
    res = inch * 25.4;
    return res;
}
/**
 * @brief UnitsTools::InchToPT 1英寸等于72pt
 * @param inch
 * @return
 */
double UnitsTools::InchToPT(double inch)
{
    double res;
    res = inch * 72;
    return res;
}
/**
 * @brief UnitsTools::MMToPT( 1inch = 25.4mm = 72pt )  ===> (1mm = (72/25.4)pt)
 * @param inch
 * @return
 */
double UnitsTools::MMToPT(double mm)
{
    double res;
    res = (mm * 72) / 25.4;
    return res;
}
/**
 * @brief UnitsTools::PTToMM ( 1inch = 25.4mm = 72pt )  ===> (1pt = (25.4/72)mm)
 * @param pt
 * @return
 */
double UnitsTools::PTToMM(double pt)
{
    double res;
    res = (pt * 25.4) / 72;
    return res;
}
