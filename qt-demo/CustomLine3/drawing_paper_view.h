#ifndef DRAWING_PAPER_VIEW_H
#define DRAWING_PAPER_VIEW_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include "common.h"

class QDrawingPaperView : public QWidget {
    Q_OBJECT
   public:
    explicit QDrawingPaperView(QWidget *parent = nullptr);
    ~QDrawingPaperView();

   private:
    QVector<LineInfo *> m_listLineInfos;  // 保存所有线条的数据信息。
    bool m_bLBtnDown;                     // 鼠标按下状态
    QPointF m_startPoint;                 // 临时记录起点
    QPointF m_endPoint;                   // 临时记录终点
    QPointF m_tmpPoint;                   // 临时记录鼠标点
    LineInfo *m_currectSelectedLine;      // 当前选中的下
    LineInfo *m_tempLine;
    LineInfo *getSeleledLine();  // 当前选中的线段
   signals:

   public slots:
   private:
    /**
     * @brief selSeg 当鼠标移动的时候判断坐标是否在选择范围内
     * @param pt
     */
    void selSeg(QPointF pt);
    /**
     * @brief  计算点到线段的距离并且返回最接近线段的点
     * @param pt  鼠标点的坐标
     * @param seg 线段，内部记录点的开始位置和结束位置
     * @param np  垂直的坐标点
     * @param minDistance  鼠标点到线段的距离视为选中。
     * @return    点到有两点的距离
     */
    SelStatus pointToSegmentDis(QPointF pt, LineSegment seg,
                                double minDistance);

    /**
     * @brief 获取点到在线段上的线的垂点
     * @param pt 点
     * @param seg 线段
     * @return
     */
    QPointF getPointToLineVerticalpoint(QPointF pt, LineSegment seg);

    /**
     * @brief pointIsOnLine 垂点是否在线段上
     * @param np 垂点
     * @param seg 线段
     * @return
     */
    bool verticalPointIsOnLine(QPointF np, LineSegment seg);
    /**
     * @brief distance  计算两点之间的距离
     * @param startPoint 开始点的位置
     * @param endPoint  结束点的位置
     * @return          两点之间的距离。
     */
    double distance(QPointF startPoint, QPointF endPoint);
    // QWidget interface
   protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif  // DRAWING_PAPER_VIEW_H
