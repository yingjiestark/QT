#include "mainwindow.h"
#include "game_widget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainGameView(new GameWidget(this))
    , m_mainWidget(new QWidget(this))
    , m_btnStart(new QPushButton(this))
    , m_btnStop(new QPushButton(this))
    , m_btnPause(new QPushButton(this))
    , m_labScoreStr(new QLabel(this))
    , m_labScoreNum(new QLabel(this))
{
    m_btnStart->setText("开始");
    m_btnStop->setText("结束");
    m_btnPause->setText("暂停");
    setWindowTitle("贪吃蛇");
    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_btn = new QVBoxLayout;
    layout_main->addWidget(m_mainGameView);
    layout_main->addLayout(layout_btn);
    m_labScoreStr->setAlignment(Qt::AlignCenter);
    m_labScoreNum->setAlignment(Qt::AlignCenter);
    m_labScoreStr->setText("当前分数");
    m_labScoreNum->setText("0");
    QFont fontScoreNum;
    fontScoreNum.setPixelSize(20);
    m_labScoreNum->setFont(fontScoreNum);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    m_labScoreNum->setPalette(pa);
    layout_btn->setSpacing(10);
    layout_btn->addWidget(m_labScoreStr);
    layout_btn->addWidget(m_labScoreNum);
    layout_btn->addWidget(m_btnStart);
    layout_btn->addWidget(m_btnStop);
    layout_btn->addWidget(m_btnPause);
    layout_btn->addStretch();
    m_mainWidget->setLayout(layout_main);
    setCentralWidget(m_mainWidget);
    connect(m_btnStart, &QPushButton::clicked, m_mainGameView,
            &GameWidget::start);
    connect(m_btnStop, &QPushButton::clicked, m_mainGameView,
            &GameWidget::stop);
    connect(m_btnPause, &QPushButton::clicked, m_mainGameView,
            &GameWidget::pause);
    connect(m_mainGameView, &GameWidget::sigUpdateScore, this,
            &MainWindow::updateScore);
    m_mainGameView->setFocus();
}

MainWindow::~MainWindow() {}

void MainWindow::updateScore(int score)
{
    score *= 10;
    QString str = QString::number(score);
    m_labScoreNum->setText(str);
}
