#ifndef COMMON_H
#define COMMON_H
struct PointEx {
    double x;
    double y;
    PointEx(double a, double b)
    {
        x = a;
        y = b;
    }
    PointEx() {}
};
struct LineSegment {
    PointEx startPoint;
    PointEx endPoint;
    LineSegment(PointEx a, PointEx b)
    {
        startPoint = a;
        endPoint = b;
    }
    LineSegment() {}
};
struct LineInfo {
    bool bDraw;  //是否绘制

    bool bSelLine;     //是否选中线
    bool bSelStartPt;  //是否选中线段起点
    bool bSelEndPt;    //是否选线段终点
    LineSegment* seg;
    LineInfo()
    {
        bDraw = false;
        bSelLine = false;
        bSelStartPt = false;
        bSelEndPt = false;
        seg = new LineSegment;
    }
    ~LineInfo() { delete seg; }
};

#endif  // COMMON_H
