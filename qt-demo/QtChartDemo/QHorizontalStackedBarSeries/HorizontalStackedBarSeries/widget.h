#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QHorizontalStackedBarSeries>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initUI();
    void initBarSet();
    void mousePressEvent(QMouseEvent *event);

   private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QHorizontalStackedBarSeries *m_ptrHorizontalPercentBarSeries;
    QBarCategoryAxis *m_ptrAxisY;
    QValueAxis *m_ptrAxisX;
};

#endif  // WIDGET_H
