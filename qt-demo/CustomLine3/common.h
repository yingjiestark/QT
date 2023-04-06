#ifndef COMMON_H
#define COMMON_H
#include <QPointF>

enum SelStatus {
    outLine,       // 在线段外
    onStartPoint,  // 在起始点
    onEndPoint,    // 在结束点
    onLine         // 在线段上
};
struct LineSegment {
    QPointF startPoint;
    QPointF endPoint;
    LineSegment(QPointF a, QPointF b)
    {
        startPoint = a;
        endPoint = b;
    }
    LineSegment() {}
};
struct LineInfo {
    bool bDraw;  //是否绘制
    SelStatus selStatus;

    LineSegment* seg;
    LineInfo()
    {
        selStatus = outLine;
        seg = new LineSegment;
    }
    ~LineInfo() { delete seg; }
};

#endif  // COMMON_H
