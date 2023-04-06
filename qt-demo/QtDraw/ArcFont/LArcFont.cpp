#include "LArcFont.h"
#include <QPainter>
#include <QChar>
#include <math.h>  //用到了sqrt，所以添加头函数
#include <QtDebug>
#include <QMouseEvent>
using namespace std;
LArcFont::LArcFont(QWidget *parent)
    : QWidget(parent)
{
}

LArcFont::LArcFont(QString str, int width, int height)
    : m_Shaftx(width)
    , m_Shafty(height)
    , m_str(str)
    , m_time(new QTimer(this))
    , m_jiaodu(0)
{
    setFixedSize(300, 300);
    connect(m_time, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
    setMouseTracking(true);

//
    //  setPalette(QPalette(QPalette::Background, QColor(255, 0, 0)));
    // setAutoFillBackground(true);
}

LArcFont::LArcFont(QString str, int radius)
    : m_Shaftx(radius)
    , m_Shafty(radius)
    , m_str(str)
{
    setFixedSize(300, 300);

    // setPalette(QPalette(QPalette::Background, QColor(255, 0, 0)));
    //  setBackgroundRole();
    //    for (int i = 0; i < 360; i += 20) {
    //        LSingleFont *s = new LSingleFont(QChar('v'), i, this);
    //        m_listChar.append(s);
    //    }
}

void LArcFont::start() {  m_time->setInterval(100);
                          m_time->start();}

void LArcFont::stop() {
                         m_time->stop();}

void LArcFont::drawChar(int Shaftx, int Shafty, int jiaodu, QString c,
                        QPainter *p)
{
    jiaodu = jiaodu % 360;

    double xigema =
        static_cast<double>(static_cast<double>(jiaodu) / 180) * M_PI;
    qInfo() << xigema;
    int xb = 1, yb = 1;
    if (jiaodu == 90) {
        xb = 0;
        yb = 1;
    } else if (jiaodu == 270) {
        xb = 1;
        yb = -1;
    } else {
        if (jiaodu > 90 &&
            jiaodu < 270) {
            xb = -1;
            yb = -1;
        }
        else{
            xb = 1;
            yb = 1;
        }
    }

    double a = static_cast<double>(Shaftx / 2.0);
    double b = static_cast<double>(Shafty / 2.0);
    double tan = std::tan(xigema);
    double x = static_cast<double>(
        (a * b) / static_cast<double>(sqrt(b * b + a * a * tan * tan)));
    double y = (a * b) * tan / sqrt(b * b + a * a * tan * tan);
    int ifontWidth = QFontMetrics(this->font()).width(c);  // 计算一个数字的长度
    int ifontHeight = QFontMetrics(this->font()).height();  // 一个字的高度
    p->translate(a + xb * x + ifontWidth, b + yb * y+ifontHeight);
    qInfo() << "x:" << x;
    qInfo() << "y:" << y;
    // p->translate(ifontWidth / 2.0, ifontHeight / 2.0);
    p->rotate(90 + jiaodu);
    //    QPointF polint(ifontWidth / 2.0, ifontHeight / 2.0);
    p->drawText(-ifontWidth / 2.0, -ifontHeight / 2.0, ifontWidth, ifontHeight,
                1, c);

    qInfo() << "jiaodu:" << jiaodu;
    p->resetMatrix();
    p->resetTransform();
//    p->drawPoint(a + xb * x, b + yb * y);
}

void LArcFont::slotTimeOut()
{
    m_jiaodu -= 1;
    if (m_jiaodu > 360) {
        m_jiaodu = 0;
    }
    if (m_jiaodu < 0) {
        m_jiaodu = 360;
    }
    update();
}

void LArcFont::paintEvent(QPaintEvent *event)
{
    //QImage img(this->size(), QImage::Format_ARGB32);
    QPainter p(this);
    QPalette p2 ;
    p2.setColor(QPalette::Text,QColor(255,0,0));
    p.setPen(p2.color(QPalette::Text));
    p2.setColor(QPalette::Background,QColor(233,233,0));
    this->setAutoFillBackground(true);
    this->setPalette(p2);

//    img.fill(Qt::transparent);
//    p.fillRect(img.rect(), Qt::transparent);
    //    QChar c('A');
    //    int ifontWidth = QFontMetrics(this->font()).width(c);
    //    //计算一个数字的长度 int ifontHeight =
    //    QFontMetrics(this->font()).height();  // 一个字的高度 QMatrix matri;
    //    matri.translate(100, 100);
    //    matri.rotate(m_jiaodu);
    //    p.setMatrix(matri);
    //    p.drawText(-ifontWidth / 2, -ifontHeight / 2, ifontWidth, ifontHeight,
    //    1,
    //               "A");
    int startAngel = m_jiaodu;
    for (int i = 0; i < m_str.length(); i++) {
        startAngel = i * 20 + m_jiaodu;
        drawChar(m_Shaftx, m_Shafty, startAngel, m_str.at(i), &p);
    }

//    QPainter p2(this);
//    p2.fillRect(img.rect(), Qt::transparent);
//    p2.drawImage(0, 0, img);

//    p.drawText(
//        0, 0, 100, 100, 1,
//        "x:" + QString::number(m_mousex) + ",y:" + QString::number(m_mousey));
     p.end();
}

void LArcFont::mouseMoveEvent(QMouseEvent *event)
{
    m_mousex = event->x();
    m_mousey = event->y();
    update();
}
