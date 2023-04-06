#include "widget.h"
#include <QTime>
#include <QLegendMarker>
#include <QtDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartview(new QChartView(m_ptrChart, this))
{
    initData();
    initUI();
    initConnect();
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

void Widget::initData()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec() + randtime.second() * 1000);
    for (int i = 0; i < 3; i++) {
        QScatterSeries *mptrScatterSeries = new QScatterSeries();
        mptrScatterSeries->setName("test" + QString::number(i));
        for (int j = 0; j < 20; j++) {
            int x = qrand() % 100;
            int y = qrand() % 100;
            mptrScatterSeries->append(x, y);
        }
        QScatterSeries::MarkerShape markerShape;
        markerShape = i % 2 == 0 ? QScatterSeries::MarkerShapeCircle
                                 : QScatterSeries::MarkerShapeRectangle;
        mptrScatterSeries->setMarkerShape(markerShape);
        m_ptrChart->addSeries(mptrScatterSeries);
    }
}

void Widget::initUI()
{
    m_ptrChart->createDefaultAxes();
    m_ptrChartview->setRenderHint(QPainter::Antialiasing);
    m_ptrChartview->setFixedSize(500, 500);
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
Widget::~Widget() {}
