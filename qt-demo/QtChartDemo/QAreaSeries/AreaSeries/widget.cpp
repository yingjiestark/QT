#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
    , m_ptrSeries0(new QLineSeries)
    , m_ptrSeries1(new QLineSeries)
    , m_ptrAreaSeries(new QAreaSeries(m_ptrSeries0, m_ptrSeries1))

{
    initUI();
    initData();
}

Widget::~Widget() {}

void Widget::initUI()
{
    m_ptrAreaSeries->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(3);
    m_ptrAreaSeries->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_ptrAreaSeries->setBrush(gradient);
    m_ptrChart->addSeries(m_ptrAreaSeries);

    m_ptrChart->setTitle("Simple areachart example");
    m_ptrChart->createDefaultAxes();
    m_ptrChart->axisX()->setRange(0, 20);
    m_ptrChart->axisY()->setRange(0, 10);

    m_ptrChartview->setRenderHint(QPainter::Antialiasing);
    m_ptrChartview->setFixedSize(500, 500);
    this->setFixedSize(500, 500);
}

void Widget::initData()
{
    *m_ptrSeries0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6)
                  << QPointF(9, 7) << QPointF(12, 6) << QPointF(16, 7)
                  << QPointF(18, 5);
    *m_ptrSeries1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3)
                  << QPointF(8, 2) << QPointF(12, 3) << QPointF(16, 4)
                  << QPointF(18, 3);
}
