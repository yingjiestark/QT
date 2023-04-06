#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QChart *m_ptrChart;
    QChartView *m_ptrChartView;
    QLineSeries * mLineSeries;
    ~Widget();

private:
    void initUI();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // WIDGET_H
