#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QScatterSeries>
#include <QList>
QT_CHARTS_USE_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

   public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initConnect();
    void initData();
    void initUI();
   public slots:
    void handleMarkerClicked();

   private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QList<QScatterSeries *> m_listScatterSeries;
};

#endif  // WIDGET_H
