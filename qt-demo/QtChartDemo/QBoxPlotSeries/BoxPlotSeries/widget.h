#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QBoxPlotSeries>
#include <QBoxSet>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initUI();
    void initConnect();
    void initData();
    qreal findMedian(QList<qreal> sortedList, int begin, int end);
   public slots:
    void handleMarkerClicked();

   private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QBoxPlotSeries *m_ptrBoxPlotSeries;
    QBoxPlotSeries *m_ptrBoxPlotSeries2;
};

#endif  // WIDGET_H
