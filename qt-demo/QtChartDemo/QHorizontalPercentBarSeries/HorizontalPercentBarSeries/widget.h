#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QHorizontalPercentBarSeries>
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
    QHorizontalPercentBarSeries *m_ptrHorizontalPercentBarSeries;
    QBarCategoryAxis *m_ptrAxisY;
    QValueAxis *m_ptrAxisX;

   protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif  // WIDGET_H
