#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
    , m_ptrHorizontalPercentBarSeries(new QHorizontalPercentBarSeries)
    , m_ptrAxisY(new QBarCategoryAxis)
    , m_ptrAxisX(new QValueAxis)
{
    initUI();
    initBarSet();
}

Widget::~Widget() {}
void Widget::initUI()
{
    setWindowTitle(tr("水平百分比柱状图样例"));
    m_ptrChart->setMinimumSize(500, 500);
    m_ptrChart->addSeries(m_ptrHorizontalPercentBarSeries);
    m_ptrChart->setTitle("水平百分比柱状图样例");
    m_ptrChart->setAnimationOptions(QChart::AllAnimations);
    m_ptrChartview->setFixedSize(600, 600);
    m_ptrAxisY->append(tr("一月"));
    m_ptrAxisY->append(tr("二月"));
    m_ptrAxisY->append(tr("三月"));
    m_ptrAxisY->append(tr("四月"));
    m_ptrAxisY->append(tr("五月"));
    m_ptrAxisY->append(tr("六月"));
    m_ptrAxisY->setLabelsColor(QColor(7, 28, 96));
    m_ptrChart->setAxisX(m_ptrAxisX, m_ptrHorizontalPercentBarSeries);

    m_ptrChart->setAxisY(m_ptrAxisY, m_ptrHorizontalPercentBarSeries);
}

void Widget::initBarSet()
{
    // 构建不同的 QAbstractBarSeries
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 2 << 3 << 4 << 4 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    m_ptrHorizontalPercentBarSeries->append(set0);
    m_ptrHorizontalPercentBarSeries->append(set1);
    m_ptrHorizontalPercentBarSeries->append(set2);
    m_ptrHorizontalPercentBarSeries->append(set3);
    m_ptrHorizontalPercentBarSeries->append(set4);
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    foreach (auto item, m_ptrHorizontalPercentBarSeries->barSets()) {
        for (int i = 0; i < item->count(); i++) {
            item->remove(i);
        }
    }
    foreach (auto item, m_ptrHorizontalPercentBarSeries->barSets()) {
        for (int i = 0; i < m_ptrAxisY->count(); i++) {
            item->append(qrand() % 15);
        }
    }
}
