#include "mainwindow.h"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "sreach_widget.h"
#include "player_widget.h"
#include "common.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ptrWdgMain(new QWidget(this))
    , m_buttonGrp(new QButtonGroup(this))
    , m_ptrBtnSreach(new QPushButton(tr("搜索页面"), this))
    , m_ptrBtnPlayer(new QPushButton(tr("播放页面"), this))
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_ptrLayoutBtn(new QHBoxLayout)
    , m_ptrLayoutContent(new QHBoxLayout)
    , m_ptrStackView(new QStackedWidget)
    , m_ptrWdgSreach(new SreachWidget(m_ptrWdgMain))
    , m_ptrWdgPlayer(new PlayerWidget(m_ptrWdgMain))

{
    initUI();
    initConnect();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    setWindowTitle("音乐搜索");
    setMinimumWidth(800);
    setMinimumHeight(600);
    m_ptrBtnSreach->setCheckable(true);
    m_buttonGrp->addButton(m_ptrBtnSreach, 0);
    m_ptrBtnPlayer->setCheckable(true);
    m_buttonGrp->addButton(m_ptrBtnPlayer, 1);

    m_buttonGrp->setExclusive(true);
    for (QWidget *w : m_buttonGrp->buttons()) {
        w->setMinimumSize(110, 10);
        m_ptrLayoutBtn->addWidget(w);
        w->installEventFilter(this);
    }
    m_ptrLayoutMain->addLayout(m_ptrLayoutBtn);

    m_ptrStackView->insertWidget(0, m_ptrWdgSreach);
    m_ptrStackView->insertWidget(1, m_ptrWdgPlayer);

    m_ptrLayoutContent->addWidget(m_ptrStackView);
    m_ptrLayoutMain->addLayout(m_ptrLayoutContent);
    m_ptrWdgMain->setLayout(m_ptrLayoutMain);
    setCentralWidget(m_ptrWdgMain);
}

void MainWindow::initConnect()
{
    connect(m_buttonGrp, SIGNAL(buttonClicked(int)), this,
            SLOT(slotClickShSLOTow(int)));

    connect(m_ptrWdgSreach, SIGNAL(sigDownLoadFinish(AbsListLocal)),
            m_ptrWdgPlayer, SLOT(slotInsertDownData(AbsListLocal)));
}


void MainWindow::slotClickShSLOTow(int index)
{
    m_ptrStackView->setCurrentIndex(index);
    m_buttonGrp->button(index)->setFocus();
}
