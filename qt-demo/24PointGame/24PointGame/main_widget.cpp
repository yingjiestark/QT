#include "main_widget.h"
#include <QtDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_ptrLayoutMain(new QHBoxLayout)
    , m_ptrStackWidget(new QStackedWidget)
    , m_ptrLevelMainWidget(new LevelMainWidget)
    , m_ptrGameWidget(new GameWidget)
{
    initUI();
    initConnect();
}

void MainWidget::initUI()
{
    setWindowTitle("24点游戏");
    m_ptrStackWidget->addWidget(m_ptrLevelMainWidget);
    m_ptrStackWidget->addWidget(m_ptrGameWidget);
    m_ptrLayoutMain->addWidget(m_ptrStackWidget);
    m_ptrStackWidget->setFixedSize(500, 550);
    setLayout(m_ptrLayoutMain);
}

void MainWidget::initConnect()
{
    connect(m_ptrLevelMainWidget, &LevelMainWidget::sigBtnLevel, this,
            &MainWidget::slotBtnClick);
    connect(m_ptrGameWidget, &GameWidget::sigBtnBack, this,
            &MainWidget::slotBtnBack);
    connect(m_ptrGameWidget, &GameWidget::sigUnlockLevel, this,
            &MainWidget::slotUnlockLevel);
}

void MainWidget::slotUnlockLevel(int level)
{
    qInfo() << "slotUnlockLevel level:" << level;
    m_ptrLevelMainWidget->unlockLevel(level);
}

void MainWidget::slotBtnClick(int level)
{
    m_ptrGameWidget->setCurrentLevel(level);
    m_ptrStackWidget->setCurrentWidget(m_ptrGameWidget);
}

void MainWidget::slotBtnBack()
{
    m_ptrStackWidget->setCurrentWidget(m_ptrLevelMainWidget);
}
