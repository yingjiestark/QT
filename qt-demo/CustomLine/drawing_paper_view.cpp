#include "drawing_paper_view.h"
#include <QMouseEvent>
#include <QPainter>
QDrawingPaperView::QDrawingPaperView(QWidget *parent)
    : QWidget(parent)
    , m_bLBtnDown(false)
    , m_currectSelectedLine(nullptr)
{
}

LineInfo *QDrawingPaperView::getSeleledLine() { return nullptr; }

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
                m_tempLine->seg->startPoint.x = event->x();
                m_tempLine->seg->startPoint.y = event->y();
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
                m_tempLine->seg->endPoint.x = event->pos().x();
                m_tempLine->seg->endPoint.y = event->pos().y();
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
    if (m_bLBtnDown) {
        m_endPoint = movePt;
    }
    update();
}

void QDrawingPaperView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    // 设置画笔的样式
    p.setPen(QPen(Qt::red, 2));
    // 绘制临时图像
    if (m_bLBtnDown == true) {
        p.drawLine(m_startPoint, m_endPoint);
    }
    // 绘制最终的数据列表
    foreach (auto item, m_listLineInfos) {
        if (true == item->bDraw) {
            p.drawLine(item->seg->startPoint.x, item->seg->startPoint.y,
                       item->seg->endPoint.x, item->seg->endPoint.y);
        }
    }
}
