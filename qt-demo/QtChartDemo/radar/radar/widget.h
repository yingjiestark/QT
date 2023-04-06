#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPolarChart>
#include <QChartView>
#include <QScatterSeries>
#include <QList>
#include <QLineSeries>
#include <QTimer>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initConnect();
    void timeout();

   private:
    QPolarChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QTimer *m_ptrTime;
    qreal m_rangle;
};

#endif  // WIDGET_H
