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

   private:
    QVector<LineInfo *> m_listLineInfos;  // 保存所有线条的数据信息。
    bool m_bLBtnDown;                     // 鼠标按下状态
    QPointF m_startPoint;                 // 临时记录起点
    QPointF m_endPoint;                   // 临时记录终点
    LineInfo *m_currectSelectedLine;      // 当前选中的下

    LineInfo *m_tempLine;
    LineInfo *getSeleledLine();  // 当前选中的线段
   signals:

   public slots:

    // QWidget interface
   protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif  // DRAWING_PAPER_VIEW_H
