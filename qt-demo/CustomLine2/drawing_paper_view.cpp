#include "drawing_paper_view.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtCore/qmath.h>
#include <QDebug>
QDrawingPaperView::QDrawingPaperView(QWidget *parent)
    : QWidget(parent)
    , m_bLBtnDown(false)
    , m_currectSelectedLine(nullptr)
{
    LineSegment seg;
    seg.startPoint.setX(0);
    seg.startPoint.setY(0);
    seg.endPoint.setX(6);
    seg.endPoint.setY(6);

    QPointF pt;
    QPointF np;
    pt.setX(0);
    pt.setY(6);
    //  double p = pointToLineDis(pt, seg, np);
    //  qInfo() << p;
    qInfo() << np;
}

LineInfo *QDrawingPaperView::getSeleledLine() { return nullptr; }

double QDrawingPaperView::pointToSegmentDis(QPointF pt, LineSegment seg)
{
    // 1. 获取垂点
    QPointF Verticalpoint;
    Verticalpoint = getPointToLineVerticalpoint(pt, seg);
    // 2. 判断垂点是否在线段上

    bool isOnSeg = verticalPointIsOnLine(Verticalpoint, seg);
    if (isOnSeg) {
        // 如果在线段上那么垂点到点的距离最短
        qInfo() << "在垂涎上";
        return distance(pt, Verticalpoint);
    } else {
        qInfo() << "不在垂线上";
        // 如果不在点段上那么到两点的距离最短。
        double startDistance = distance(pt, seg.startPoint);
        double endDistance = distance(pt, seg.endPoint);
        return startDistance < endDistance ? startDistance : endDistance;
    }
}

QPointF QDrawingPaperView::getPointToLineVerticalpoint(QPointF pt,
                                                       LineSegment seg)
{
    QPointF np;
    double x_se = seg.startPoint.x() - seg.endPoint.x();
    double y_se = seg.startPoint.y() - seg.endPoint.y();
    double x_se_2 = x_se * x_se;
    double y_se_2 = y_se * y_se;
    double x = (x_se_2 * pt.x() + (pt.y() - seg.startPoint.y()) * y_se * x_se +
                seg.startPoint.x() * y_se_2) /
               (x_se_2 + y_se_2);
    double y = pt.y() + x_se * (pt.x() - x) / y_se;
    np.setX(x);
    np.setY(y);
    return np;
}

bool QDrawingPaperView::verticalPointIsOnLine(QPointF np, LineSegment seg)
{
    bool isOnX = false;  // 垂点的x坐标是否在线段上
    bool isOnY = false;  // 垂点的y坐标是否在线段上
    if (seg.startPoint.x() > seg.endPoint.x()) {
        if (np.x() < seg.startPoint.x() && np.x() > seg.endPoint.x()) {
            isOnX = true;
        }
    } else {
        if (np.x() < seg.endPoint.x() && np.x() > seg.startPoint.x()) {
            isOnX = true;
        }
    }

    if (seg.startPoint.y() > seg.endPoint.y()) {
        if (np.y() < seg.startPoint.y() && np.y() > seg.endPoint.y()) {
            isOnY = true;
        }
    } else {
        if (np.y() < seg.endPoint.y() && np.y() > seg.startPoint.y()) {
            isOnY = true;
        }
    }

    if (isOnX && isOnY) {
        return true;
    }
    return false;
}

double QDrawingPaperView::distance(QPointF startPoint, QPointF endPoint)
{
    double dis = 0;
    double width = startPoint.x() - endPoint.x();
    double height = startPoint.y() - endPoint.y();
    dis = qSqrt(width * width + height * height);
    return dis;
}

void QDrawingPaperView::selSeg(QPointF pt)
{
    int num = m_listLineInfos.size();
    for (int i = 0; i < num; i++) {
        LineInfo *line = m_listLineInfos.at(i);
        LineSegment *seg = line->seg;
        QPointF np;
        double dis = pointToSegmentDis(pt, *seg);
        if (dis < 10) {
            line->bSelLine = true;
        } else {
            line->bSelLine = false;
        }
    }
}

void QDrawingPaperView::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::LeftButton:
            m_bLBtnDown = true;  // 记录左键鼠标按下
            m_currectSelectedLine = nullptr;
            m_currectSelectedLine = getSeleledLine();
            if (nullptr == m_currectSelectedLine) {  // 未选中

                m_startPoint = event->pos();
                m_endPoint = m_startPoint;
                // 记录绘画起始点
                m_tempLine = new LineInfo;
                m_tempLine->seg->startPoint.setX(event->x());
                m_tempLine->seg->startPoint.setY(event->y());
            } else {
            }
            break;
        default:
            break;
    }
}

void QDrawingPaperView::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
        case Qt::LeftButton:
            m_bLBtnDown = false;  // 记录左键鼠标按下
            if (nullptr == m_currectSelectedLine) {
                // 记录绘画结束点
                m_tempLine->seg->endPoint.setX(event->pos().x());
                m_tempLine->seg->endPoint.setY(event->pos().y());
                m_tempLine->bDraw = true;
                // 将线段信息保存在列表中
                m_listLineInfos.push_back(m_tempLine);
            }
            break;
        default:
            break;
    }
}

void QDrawingPaperView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF movePt = event->pos();
    m_currectSelectedLine = getSeleledLine();
    if (m_bLBtnDown) {
        m_endPoint = movePt;
    } else {
        selSeg(movePt);
    }
    update();
}

void QDrawingPaperView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    // 设置画笔的样式

    // 绘制临时图像
    if (m_bLBtnDown == true) {
        p.drawLine(m_startPoint, m_endPoint);
    }
    // 绘制最终的数据列表
    foreach (auto item, m_listLineInfos) {
        if (true == item->bDraw) {
            if (item->bSelLine) {
                p.setPen(QPen(Qt::red, 4));
            } else {
                p.setPen(QPen(Qt::green, 2));
            }

            p.drawLine(item->seg->startPoint, item->seg->endPoint);
        }
    }
}
