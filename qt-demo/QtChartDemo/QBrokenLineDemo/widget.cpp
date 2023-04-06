#include "widget.h"
#include <QValueAxis>
#include <QTime>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_ptrChart(new QChart)
    , m_ptrChartView(new QChartView())
    , mLineSeries(new QLineSeries)
{
   // setChart();
    initUI();
}

Widget::~Widget()
{

}

void Widget::initUI()
{
  //  (500,500);
     setWindowTitle("折线图样例");
     QValueAxis * mAxY = new QValueAxis();
     QValueAxis * mAxX = new QValueAxis();

      //y轴范围
      mAxY->setRange(0, 10);
      // Y轴分等份
      mAxY->setTickCount(11);
      mAxX->setRange(1,12);
      mAxX->setTickCount(12);
      // 分辨设置X轴和Y轴的标题
      mAxX->setTitleText(QString(tr("月份")));
      mAxY->setTitleText(QString(tr("销售额(万)")));
      // 将系列添加到图表
      m_ptrChart->addSeries(mLineSeries);
      m_ptrChart->setTheme(QtCharts::QChart::ChartThemeBrownSand);


      m_ptrChart->addAxis(mAxY, Qt::AlignLeft);
      m_ptrChart->addAxis(mAxX, Qt::AlignBottom);
      mLineSeries->attachAxis(mAxX);

      mLineSeries->attachAxis(mAxY);

      //突出曲线上的点
      mLineSeries->setPointsVisible(true);

      mLineSeries->setName("年销售额");
      // 设置颜色
      mLineSeries->setColor(QColor(255,0,255));


      //隐藏背景
      m_ptrChart->setBackgroundVisible(true);
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
      for(int i = 0 ;i <= 12;i++){
             mLineSeries->append(i+1, i);
     }

      m_ptrChartView->setParent(this);
      m_ptrChartView->setMinimumSize(600,600);

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mLineSeries->clear();
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    for(int i = 1 ;i <= 12;i++){
           mLineSeries->append(i, qrand()%11);
   }
}
