#include "widget.h"
#include <QtDebug>
#include <QLegendMarker>
#include <QBarLegendMarker>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
    , m_ptrBoxPlotSeries(new QBoxPlotSeries)
    , m_ptrBoxPlotSeries2(new QBoxPlotSeries)
{
    initUI();
    initConnect();
}
void Widget::initUI()
{
    setWindowTitle(tr("盒须图样例"));
    m_ptrChart->setMinimumSize(500, 500);
    m_ptrChart->setTitle("盒须图样例");

    initData();

    m_ptrChart->createDefaultAxes();
    m_ptrChart->axes(Qt::Vertical).first()->setMin(15.0);
    m_ptrChart->axes(Qt::Vertical).first()->setMax(40.0);

    m_ptrChart->setAnimationOptions(QChart::AllAnimations);
    m_ptrChartview->setFixedSize(600, 600);
    m_ptrChartview->setRenderHint(QPainter::Antialiasing);
}

void Widget::initConnect()
{
    foreach (auto marker, m_ptrChart->legend()->markers()) {
        QObject::disconnect(marker, &QLegendMarker::clicked, this,
                            &Widget::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this,
                         &Widget::handleMarkerClicked);
    }
}
void Widget::handleMarkerClicked()
{
    QLegendMarker *marker = qobject_cast<QLegendMarker *>(sender());

    //断言
    Q_ASSERT(marker);
    switch (marker->type()) {
        case QLegendMarker::LegendMarkerTypeBoxPlot: {
            //控序列隐藏/显示
            // Toggle visibility of series
            marker->series()->setVisible(!marker->series()->isVisible());

            // Turn legend marker back to visible, since hiding series also
            // hides the marker and we don't want it to happen now.
            marker->setVisible(true);

            //修改图例
            // Dim the marker, if series is not visible
            qreal alpha = 1.0;

            if (!marker->series()->isVisible()) alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);

            break;
        }
        default: {
            qInfo() << "Unknown marker type";
            break;
        }
    }
}
void Widget::initData()
{
    QList<qreal> listData;
    listData << 25.74 << 25.28 << 25.86 << 26.05 << 26.64 << 28.47 << 28.30
             << 29.22 << 29.72 << 27.50 << 25.62 << 25.50 << 25.15 << 26.47
             << 27.41 << 25.78 << 24.82 << 24.89 << 24.88 << 24.60 << 23.85;
    qSort(listData.begin(), listData.end());
    QBoxSet *box = new QBoxSet("统信");
    int count = listData.count();
    box->setValue(QBoxSet::LowerExtreme, listData.first());
    box->setValue(QBoxSet::UpperExtreme, listData.last());
    box->setValue(QBoxSet::Median, findMedian(listData, 0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(listData, 0, count / 2));
    box->setValue(QBoxSet::UpperQuartile,
                  findMedian(listData, count / 2 + (count % 2), count));
    m_ptrBoxPlotSeries->append(box);

    listData.clear();
    qInfo() << listData;
    listData << 30.79 << 29.62 << 29.67 << 30.37 << 30.16 << 30.22 << 31.02
             << 33.70 << 32.60 << 32.24 << 31.98 << 31.79 << 31.10 << 30.79
             << 31.53 << 30.92 << 29.00 << 29.58 << 30.37 << 29.40 << 28.60;
    qSort(listData.begin(), listData.end());

    QBoxSet *box2 = new QBoxSet("麒麟");
    count = listData.count();
    qInfo() << findMedian(listData, 0, count);
    qInfo() << findMedian(listData, 0, count / 2);
    qInfo() << findMedian(listData, count / 2 + (count % 2), count);
    box2->setValue(QBoxSet::LowerExtreme, listData.first());
    box2->setValue(QBoxSet::UpperExtreme, listData.last());
    box2->setValue(QBoxSet::Median, findMedian(listData, 0, count));
    box2->setValue(QBoxSet::LowerQuartile, findMedian(listData, 0, count / 2));
    box2->setValue(QBoxSet::UpperQuartile,
                   findMedian(listData, count / 2 + (count % 2), count));
    m_ptrBoxPlotSeries2->append(box2);

    m_ptrBoxPlotSeries->setName("统信");
    m_ptrBoxPlotSeries2->setName("麒麟");
    m_ptrChart->addSeries(m_ptrBoxPlotSeries);
    m_ptrChart->addSeries(m_ptrBoxPlotSeries2);
}
qreal Widget::findMedian(QList<qreal> sortedList, int begin, int end)
{
    //! [5]
    int count = end - begin;
    if (count % 2) {
        return sortedList.at(count / 2 + begin);
    } else {
        qreal right = sortedList.at(count / 2 + begin);
        qreal left = sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
    //! [5]
}
Widget::~Widget() {}
