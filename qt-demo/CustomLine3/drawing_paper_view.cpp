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
}

QDrawingPaperView::~QDrawingPaperView()
{
    foreach (auto item, m_listLineInfos) {
        delete item;
        item = nullptr;
    }
}

LineInfo *QDrawingPaperView::getSeleledLine()
{
    foreach (auto item, m_listLineInfos) {
        if (outLine != item->selStatus) {
            return item;
        }
    }
    return nullptr;
}

SelStatus QDrawingPaperView::pointToSegmentDis(QPointF pt, LineSegment seg,
                                               double minDistance)
{
    SelStatus res = outLine;
    // 1. 获取垂点
    QPointF Verticalpoint;
    Verticalpoint = getPointToLineVerticalpoint(pt, seg);
    // 2. 判断垂点是否在线段上

    //  bool isOnSeg = verticalPointIsOnLine(Verticalpoint, seg);
    double startDistance = distance(pt, seg.startPoint);
    double endDistance = distance(pt, seg.endPoint);
    double lineDistance = distance(pt, Verticalpoint);
    if (minDistance < startDistance && minDistance < startDistance &&
        minDistance < lineDistance) {
        res = outLine;
        return res;
    }
    if (startDistance < minDistance) {
        res = onStartPoint;
        return res;
    }
    if (endDistance < minDistance) {
        res = onEndPoint;
        return res;
    }

    if (lineDistance < minDistance) {
        res = onLine;
        return res;
    }
    return res;
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
        line->selStatus = outLine;

        SelStatus res = pointToSegmentDis(pt, *seg, 10);
        line->selStatus = res;
        //        if (line->selStatus != outLine) {
        //            return;
        //        }
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
                m_tmpPoint = event->pos();
                // 记录被选中的开始点和结束点，当鼠标移动时需要通过他们来计算移动的偏移量。
                m_startPoint = m_currectSelectedLine->seg->startPoint;
                m_endPoint = m_currectSelectedLine->seg->endPoint;
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
                // 将线段信息保存在列表中,开始位置不能与起始位置重复.
                if (m_tempLine->seg->startPoint != m_tempLine->seg->endPoint)
                    m_listLineInfos.push_back(m_tempLine);
            } else {
                m_currectSelectedLine = nullptr;
            }
            break;
        default:
            break;
    }
    update();
}

void QDrawingPaperView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF movePt = event->pos();

    if (!m_bLBtnDown) {
        selSeg(movePt);
    }
    m_currectSelectedLine = getSeleledLine();
    if (nullptr == m_currectSelectedLine) {
        if (m_bLBtnDown) {
            m_endPoint = movePt;
        }
    } else {
        if (m_bLBtnDown) {
            if (m_currectSelectedLine->selStatus == onLine) {
                qInfo() << (movePt);
                qInfo() << "m_tmpPoint" << m_tmpPoint;
                qInfo() << "偏移:" << movePt - m_tmpPoint;
                qInfo() << m_currectSelectedLine->seg->startPoint + movePt -
                               m_tmpPoint;
                m_currectSelectedLine->seg->startPoint =
                    m_startPoint + movePt - m_tmpPoint;

                m_currectSelectedLine->seg->endPoint =
                    m_endPoint + movePt - m_tmpPoint;
                qInfo() << "endPoint" << (m_currectSelectedLine->seg->endPoint);
            } else if (m_currectSelectedLine->selStatus == onStartPoint) {
                m_currectSelectedLine->seg->startPoint =
                    m_startPoint + movePt - m_tmpPoint;
            } else if (m_currectSelectedLine->selStatus == onEndPoint) {
                m_currectSelectedLine->seg->endPoint =
                    m_endPoint + movePt - m_tmpPoint;
            }
        }
    }
    update();
}

void QDrawingPaperView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    // 设置画笔的样式

    // 绘制临时图像
    if (m_bLBtnDown == true && nullptr == m_currectSelectedLine) {
        p.setPen(QPen(Qt::red, 1));
        p.drawLine(m_startPoint, m_endPoint);
    }
    // 绘制最终的数据列表
    foreach (auto item, m_listLineInfos) {
        if (true == item->bDraw) {
            if (item->selStatus != outLine) {
                p.setPen(QPen(Qt::red, 2));
                if (item->selStatus == onStartPoint) {
                    p.setPen(QPen(Qt::red, 2));
                    p.drawEllipse(item->seg->startPoint, 3, 3);
                } else if (item->selStatus == onEndPoint) {
                    p.setPen(QPen(Qt::red, 2));
                    p.drawEllipse(item->seg->endPoint, 3, 3);
                }
            } else {
                p.setPen(QPen(Qt::red, 1));
            }
            p.drawLine(item->seg->startPoint, item->seg->endPoint);
        }
    }
}
