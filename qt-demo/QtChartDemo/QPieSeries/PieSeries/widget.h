#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
QT_CHARTS_USE_NAMESPACE
class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUI();
    void initData();
    void initConnect();

   public slots:
    void clickedItem(QPieSlice *slice);

   private:
    QList<QBrush> m_listColor;
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QPieSeries *m_ptrPieSeries;
};

#endif  // WIDGET_H
