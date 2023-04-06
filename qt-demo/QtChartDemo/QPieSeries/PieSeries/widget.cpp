#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
    , m_ptrPieSeries(new QPieSeries)
{
    initUI();
    initData();
    initConnect();
}

Widget::~Widget() {}

void Widget::initUI()
{
    m_ptrChart->addSeries(m_ptrPieSeries);
    m_ptrChart->setTitle("Simple piechart example");
    m_ptrChart->legend()->hide();

    m_ptrChartview->setRenderHint(QPainter::Antialiasing);
    m_ptrChartview->setFixedSize(500, 500);
    setFixedSize(500, 500);
}

void Widget::initData()
{
    QPieSlice *slice1 = new QPieSlice("jane", 1);
    QPieSlice *slice2 = new QPieSlice("Joe", 2);
    QPieSlice *slice3 = new QPieSlice("Andy", 3);
    QPieSlice *slice4 = new QPieSlice("Barbara", 4);
    QPieSlice *slice5 = new QPieSlice("Axel", 5);

    m_listColor.append(QBrush(QColor("#f15b6c")));
    m_listColor.append(QBrush(QColor("#faa755")));
    m_listColor.append(QBrush(QColor("#bed742")));
    m_listColor.append(QBrush(QColor("#afb4db")));
    m_listColor.append(QBrush(QColor("#4e72b8")));
    m_ptrPieSeries->append(slice1);
    m_ptrPieSeries->append(slice2);
    m_ptrPieSeries->append(slice3);
    m_ptrPieSeries->append(slice4);
    m_ptrPieSeries->append(slice5);
    for (int i = 0; i < m_ptrPieSeries->slices().count(); i++) {
        m_ptrPieSeries->slices()[i]->setBrush(m_listColor.at(i));
    }
}

void Widget::initConnect()
{
    connect(m_ptrPieSeries, SIGNAL(clicked(QPieSlice *)), this,
            SLOT(clickedItem(QPieSlice *)));
}

void Widget::clickedItem(QPieSlice *slice)
{
    int i = m_ptrPieSeries->slices().lastIndexOf(slice);

    if (!slice->isExploded()) {
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setBrush(Qt::green);
    } else {
        slice->setLabelVisible(false);
        slice->setExploded(false);
        slice->setPen(QPen(Qt::white, 1));
        slice->setBrush(m_listColor.at(i));
    }
}
