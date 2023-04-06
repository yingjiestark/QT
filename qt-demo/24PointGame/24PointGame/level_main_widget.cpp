#include "level_main_widget.h"
#include "db/dbmanager.h"
#include <QtDebug>
#define MAX_NUM 515
LevelMainWidget::LevelMainWidget(QWidget* parent)
    : QWidget(parent)

    , m_ptrStackWidget(new QStackedWidget(this))
    , m_ptrLayoutMain(new QHBoxLayout)
    , m_ptrBtnPre(new QPushButton("上一个", this))
    , m_ptrBtnNext(new QPushButton("下一个", this))
    , m_bDonghua(false)

{
    int max = DBManager::getInstance()->getMax();
    for (int i = 0; i < max; i += 25) {
        int start = i + 1;
        int end = i + 25;
        if (end > max) {
            end = max;
        }
        LevelWidget* lvlWidget = new LevelWidget(start, end);
        m_listLevelWidget.append(lvlWidget);
        m_ptrStackWidget->addWidget(lvlWidget);
        connect(lvlWidget, &LevelWidget::sigBtnClick, this,
                &LevelMainWidget::slotBtnLevel);
    }

    m_ptrLayoutMain->addWidget(m_ptrBtnPre);
    m_ptrLayoutMain->addWidget(m_ptrStackWidget);
    m_ptrLayoutMain->addWidget(m_ptrBtnNext);
    m_ptrBtnPre->setFocusPolicy(Qt::NoFocus);
    m_ptrBtnNext->setFocusPolicy(Qt::NoFocus);
    // 初始化显示的关卡页面
    int id = DBManager::getInstance()->getCurrentLevel();
    int currentIndex = int((id - 1) / 25);
    m_ptrStackWidget->setCurrentIndex(currentIndex);

    setFixedSize(500, 500);
    setLayout(m_ptrLayoutMain);
    initConnect();
}

void LevelMainWidget::unlockLevel(int level)
{
    int index_v = 0;
    if (level == 1) {
        index_v = 0;
    } else {
        index_v = int((level - 1) / 25);
    }
    if (m_listLevelWidget.at(index_v) == nullptr) {
        qInfo() << "m_listLevelWidget is null !! index_v :" << index_v;
        return;
    }
    m_ptrStackWidget->setCurrentIndex(index_v);
    m_listLevelWidget.at(index_v)->unLockLevel(level);
}
void LevelMainWidget::onAnimationFinished()
{
    QParallelAnimationGroup* group = (QParallelAnimationGroup*)sender();
    QWidget* widget = group->property("widget").value<QWidget*>();
    if (nullptr != widget) {
        widget->hide();
    }
    m_bDonghua = false;
}

void LevelMainWidget::slotBtnPre()
{
    int currentIndex = m_ptrStackWidget->currentIndex();
    if(0 == currentIndex){
        return;
    }
    if (m_bDonghua) {
        return;
    }
    m_bDonghua = true;
    int windowWidth = m_ptrStackWidget->widget(currentIndex)->width();
    int windowHieght = m_ptrStackWidget->widget(currentIndex)->height();
    int PreIndex = currentIndex - 1;
    m_ptrStackWidget->setCurrentIndex(PreIndex);
    m_ptrStackWidget->widget(currentIndex)->show();
    QPropertyAnimation* animation1;
    QPropertyAnimation* animation2;
    // 设置动画组
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    animation1 = new QPropertyAnimation(m_ptrStackWidget->widget(currentIndex),
                                        "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
    animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));

    animation2 =
        new QPropertyAnimation(m_ptrStackWidget->widget(PreIndex), "geometry");
    animation2->setDuration(500);
    animation2->setStartValue(
        QRect(-windowWidth, 0, windowWidth, windowHieght));
    animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));

    group->addAnimation(animation1);
    group->addAnimation(animation2);
    group->start();
    group->setProperty(
        "widget", QVariant::fromValue(m_ptrStackWidget->widget(currentIndex)));
    connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

void LevelMainWidget::slotBtnNext()
{
    int currentIndex = m_ptrStackWidget->currentIndex();
    int total_page = m_ptrStackWidget->count();
    if (currentIndex >= total_page - 1) {
        return;
    }
    if (m_bDonghua) {
        return;
    }
    m_bDonghua = true;

    int windowWidth = m_ptrStackWidget->widget(currentIndex)->width();
    int windowHieght = m_ptrStackWidget->widget(currentIndex)->height();
    int NextIndex = currentIndex + 1;

    m_ptrStackWidget->setCurrentIndex(NextIndex);
    m_ptrStackWidget->widget(currentIndex)->show();
    QPropertyAnimation* animation1;
    QPropertyAnimation* animation2;
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    animation1 = new QPropertyAnimation(m_ptrStackWidget->widget(currentIndex),
                                        "geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
    animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));

    animation2 =
        new QPropertyAnimation(m_ptrStackWidget->widget(NextIndex), "geometry");
    animation2->setDuration(500);
    animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
    animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));

    group->addAnimation(animation1);
    group->addAnimation(animation2);
    group->start();
    group->setProperty(
        "widget", QVariant::fromValue(m_ptrStackWidget->widget(currentIndex)));
    connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

void LevelMainWidget::slotBtnLevel(int level)
{
    qInfo() << "LevelMainWidget level:" << level;
    // 判断是否解锁
    emit sigBtnLevel(level);
}

LevelMainWidget::~LevelMainWidget() {}

void LevelMainWidget::initConnect()
{
    connect(m_ptrBtnPre, SIGNAL(clicked()), this, SLOT(slotBtnPre()));
    connect(m_ptrBtnNext, SIGNAL(clicked()), this, SLOT(slotBtnNext()));
}
