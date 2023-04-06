#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QAreaSeries>
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initUI();
    void initData();

   private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QLineSeries *m_ptrSeries0;
    QLineSeries *m_ptrSeries1;
    QAreaSeries *m_ptrAreaSeries;
};

#endif  // WIDGET_H
