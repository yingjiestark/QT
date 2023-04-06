#include "widget.h"
#include <QValueAxis>
#include <QTime>
#include <QLegendMarker>
#include <QtDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartView(new QChartView())
    , m_ptrAxY(new QValueAxis())
    , m_ptrAxX(new QValueAxis())

{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //  (500,500);
    setWindowTitle("曲线图样例");
    // y轴范围
    m_ptrAxY->setRange(0, 10);
    // Y轴分等份
    m_ptrAxY->setTickCount(11);
    m_ptrAxX->setRange(1, 12);
    m_ptrAxX->setTickCount(12);
    m_ptrAxX->setShadesVisible(true);
    m_ptrAxX->setShadesColor(QColor(255, 125, 125));
    m_ptrAxX->setLabelsAngle(45);
    //    QPen pen;
    //    pen.setColor(QColor(255, 0, 0));

    //    pen.setStyle(Qt::PenStyle::DashLine);
    //    pen.setWidth(5);
    //    m_ptrAxX->setShadesPen(pen);
    // 分辨设置X轴和Y轴的标题
    m_ptrAxX->setTitleText(QString(tr("月份")));
    m_ptrAxX->setTitleText(QString(tr("销售额(万)")));
    // 将系列添加到图表
    initSpline();
    m_ptrChart->setTheme(QtCharts::QChart::ChartThemeBrownSand);

    m_ptrChart->addAxis(m_ptrAxY, Qt::AlignLeft);
    m_ptrChart->addAxis(m_ptrAxX, Qt::AlignBottom);

    //隐藏背景
    m_ptrChart->setBackgroundVisible(false);
    //设置外边界全部为0
    m_ptrChart->setContentsMargins(0, 0, 0, 0);
    //设置内边界全部为0
    m_ptrChart->setMargins(QMargins(0, 0, 0, 0));
    //设置背景区域无圆角
    m_ptrChart->setBackgroundRoundness(0);

    //在底部显示图例
    QLegend *mlegend = m_ptrChart->legend();
    mlegend->setAlignment(Qt::AlignBottom);
    mlegend->show();

    m_ptrChartView->setChart(m_ptrChart);

    m_ptrChartView->setParent(this);
    m_ptrChartView->setMinimumSize(600, 600);
    initConnect();
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    foreach (auto item, m_listSplineSeries) {
        item->clear();

        for (int i = 1; i <= 12; i++) {
            item->append(i, qrand() % 11);
        }
    }
}

void Widget::handleMarkerClicked()
{
    QLegendMarker *marker = qobject_cast<QLegendMarker *>(sender());
    //断言
    Q_ASSERT(marker);
    switch (marker->type()) {
        case QLegendMarker::LegendMarkerTypeXY: {
            //控序列隐藏/显示
            // Toggle visibility of series
            marker->series()->setVisible(!marker->series()->isVisible());

            // Turn legend marker back to visible, since hiding series also
            // hides the marker and we don't want it to happen now.
            marker->setVisible(true);

            //修改图例
            // Dim the marker, if series is not visible
            qreal alpha = 2.0;

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
void Widget::initSpline()
{
    for (int i = 0; i < 3; i++) {
        QSplineSeries *mLineSeries = new QSplineSeries;
        mLineSeries->attachAxis(m_ptrAxX);

        mLineSeries->attachAxis(m_ptrAxY);
        mLineSeries->setUseOpenGL();

        //突出曲线上的点
        mLineSeries->setPointsVisible(true);

        mLineSeries->setName(QString::number(2015 + i) + QString("年"));
        // 设置颜色
        mLineSeries->setColor(
            QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        for (int i = 0; i <= 12; i++) {
            mLineSeries->append(i + 1, i);
        }
        m_listSplineSeries.append(mLineSeries);
        m_ptrChart->addSeries(mLineSeries);
    }
}

void Widget::initConnect()
{
    const auto markers = m_ptrChart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked, this,
                            &Widget::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this,
                         &Widget::handleMarkerClicked);
    }
}
Widget::~Widget() {}
