#include "widget.h"

#include <QSplineSeries>
#include <QtDebug>
Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , m_ptrChart(new QPolarChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
    , m_ptrTime(new QTimer)
    , m_rangle(22.5)
{
    QSplineSeries* s = new QSplineSeries();
    s->append(m_rangle, 190);
    s->append(0, 100);
    QScatterSeries* series = new QScatterSeries();
    // 创建一个散点绘图数据集对象
    const qreal angularMax = 100;  // 最大角度
    series->setName("散点");
    for (int i = 0; i < angularMax; i += 10) {
        series->append(i,
                       i + 100);  // 向series中添加数据，X：角度 Y：到圆心距离
    }
    m_ptrChart->legend()->setVisible(true);  // 隐藏图例
                                             // m_ptrChart->addSeries(s);
    m_ptrChart->addSeries(series);  // 将创建的series添加进图表中
    m_ptrChart->addSeries(s);
    m_ptrChart->createDefaultAxes();
    m_ptrChartview->setFixedSize(500, 500);
    m_ptrTime->start(100);
    initConnect();
}
void Widget::initConnect()
{
    connect(m_ptrTime, &QTimer::timeout, this, &Widget::timeout);
}

void Widget::timeout()
{
    qInfo() << "start timeout";
    foreach (auto* item, m_ptrChart->series()) {
        ///   qInfo() << "item->type()" << item->type();
        if (item->type() == QSplineSeries::SeriesTypeSpline) {
            dynamic_cast<QSplineSeries*>(item)->clear();
            m_rangle += 0.2;
            m_rangle = ((int)m_rangle % 90) + 1;
            dynamic_cast<QSplineSeries*>(item)->append(m_rangle, 190);
            dynamic_cast<QSplineSeries*>(item)->append(0, 100);
        }
    }
}
Widget::~Widget() {}
