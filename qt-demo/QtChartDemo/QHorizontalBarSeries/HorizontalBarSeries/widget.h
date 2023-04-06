#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QBarCategoryAxis>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initUI();
    void initBarSet();

   private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QHorizontalBarSeries *m_ptrHorizontalBarSeries;
    QBarCategoryAxis *m_ptrAxisY;
    QValueAxis *m_ptrAxisX;

    // QWidget interface
   protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif  // WIDGET_H
