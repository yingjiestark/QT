#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QChart *m_ptrChart;
    QChartView *m_ptrChartView;
   QList< QSplineSeries *> m_listSplineSeries;
   QValueAxis * m_ptrAxY;
   QValueAxis * m_ptrAxX;
    ~Widget();
private:
    void initUI();
    void initSpline();
    void initConnect();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
public slots:
    void handleMarkerClicked();
};

#endif // WIDGET_H
