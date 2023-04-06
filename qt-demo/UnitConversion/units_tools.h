#ifndef UNITS_TOOLS_H
#define UNITS_TOOLS_H

#include <QObject>
#include <QtDebug>
struct PhysicsDistance {
    PhysicsDistance()
    {
        x = 0;
        y = 0;
    }
    double x;
    double y;

   public:
    void log() { qInfo() << "res.x:" << x << ",res.y:" << y; }
};
class UnitsTools : public QObject {
    Q_OBJECT
   public:
    explicit UnitsTools(QObject *parent = nullptr);
    PhysicsDistance PxToMM(double px);  // 由px转成毫米
    PhysicsDistance PxToPt(double px);
    PhysicsDistance x_MMToPx(double mm);  // 由毫米专为px
    PhysicsDistance y_MMToPx(double mm);  // 由毫米专为px
    double InchToMM(double inch);         // 由英寸(inch)转为毫米（mm）
    double InchToPT(double inch);         // 由英寸(inch)转为磅 (pt)
    double MMToPT(double inch);           // 由毫米(mm)转为磅 (pt)
    double PTToMM(double inch);           // 由磅(pt)转为毫米(mm)
};

#endif  // UNITS_TOOLS_H
