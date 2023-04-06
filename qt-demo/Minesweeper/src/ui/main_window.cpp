/*
 * Copyright (C) 2019 ~ 2021 arv000
 *
 * Author:     arv000 <arv003@163.com>
 *
 * Maintainer: arv000 <arv003@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main_window.h"
#include "select_dialog.h"
#include "ranking_dialog.h"
#include "register_dialog.h"
#include "about_dialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mainView(new QWidget(this))
    , m_mainlayout(new QHBoxLayout())
    , m_showInfoLayout(new QVBoxLayout())
    , m_imgTime(new QLabel(this))
    , m_lcdNumber(new QLCDNumber(this))
    , m_imgFlag(new QLabel(this))
    , m_labFlag(new QLabel(this))
    , m_btn(new QPushButton(this))
    , m_btnModify(new QPushButton(this))
    , m_btnRanking(new QPushButton(this))
    , m_btnAbout(new QPushButton(this))
    , m_gameWidget(new QGameWidget(9, 9, 10, m_mainView))
    , m_timer(new QTimer(this))
    , m_nTime(0)
    , m_level(0)
{
    initUI();
    initConnect();
    setCentralWidget(m_mainView);
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    setWindowTitle(tr("扫雷"));

    // 初始化按钮
    m_btn->setText(tr("重新开始"));
    m_btn->setFocusPolicy(Qt::NoFocus);

    m_btnModify->setText(tr("修改难度"));
    m_btnModify->setFocusPolicy(Qt::NoFocus);

    m_btnRanking->setText(tr("显示排名"));
    m_btnRanking->setFocusPolicy(Qt::NoFocus);

    m_btnAbout->setText(tr("关于"));
    m_btnAbout->setFocusPolicy(Qt::NoFocus);

    // 初始化时间
    QPixmap pixmapTime(":/time.png");
    m_imgTime->setMaximumSize(50, 50);
    m_imgTime->setMinimumSize(50, 50);
    pixmapTime.scaled(m_imgTime->size(), Qt::KeepAspectRatioByExpanding,
                      Qt::SmoothTransformation);
    m_imgTime->setAlignment(Qt::AlignCenter);
    m_imgTime->setPixmap(pixmapTime);
    m_imgTime->setScaledContents(true);

    // 初始化时间控件。
    m_lcdNumber->setDigitCount(5);
    m_lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdpat = m_lcdNumber->palette();
    lcdpat.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    m_lcdNumber->setPalette(lcdpat);

    // 初始化小旗内容
    m_imgFlag->setMaximumSize(50, 50);
    m_imgFlag->setMinimumSize(50, 50);
    QPixmap pixMapFlag(":/flag.png");
    pixMapFlag.scaled(50, 50, Qt::KeepAspectRatioByExpanding,
                      Qt::SmoothTransformation);
    m_imgFlag->setPixmap(pixMapFlag);
    m_imgFlag->setScaledContents(true);

    // 初始化小旗控件
    m_labFlag->setText("0/10");

    // 初始化布局
    m_showInfoLayout->addWidget(m_imgTime, 0, Qt::AlignCenter);
    m_showInfoLayout->addWidget(m_lcdNumber, 0, Qt::AlignCenter);
    m_showInfoLayout->addWidget(m_imgFlag, 0, Qt::AlignCenter);
    m_showInfoLayout->addWidget(m_labFlag, 0, Qt::AlignCenter);
    m_showInfoLayout->addWidget(m_btnAbout);
    m_showInfoLayout->addWidget(m_btnRanking);
    m_showInfoLayout->addWidget(m_btnModify);
    m_showInfoLayout->addWidget(m_btn);

    m_mainlayout->addWidget(m_gameWidget);
    m_mainlayout->addLayout(m_showInfoLayout);

    // 设置mainwindow布局
    m_mainView->setLayout(m_mainlayout);
    setFixedSize(467, 378);
}

void MainWindow::initConnect()
{
    connect(m_btn, &QPushButton::clicked, this, &MainWindow::initGame);
    connect(m_btnModify, &QPushButton::clicked, this,
            &MainWindow::slotModifyGameLeve);

    connect(m_btnRanking, &QPushButton::clicked, this,
            &MainWindow::slotShowRanking);

    connect(m_btnAbout, &QPushButton::clicked, this,
            &MainWindow::slotShowAbout);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    connect(m_gameWidget, &QGameWidget::sigGameWin, this,
            &MainWindow::slotGameWin);
    connect(m_gameWidget, &QGameWidget::sigGameStart, this,
            &MainWindow::slotGameStart);

    connect(m_gameWidget, &QGameWidget::sigGameOver, this,
            &MainWindow::slotGameOver);
    connect(m_gameWidget, &QGameWidget::sigFlags, this, &MainWindow::slotFlag);
}

void MainWindow::slotGameStart()
{
    m_timer->start(1000);
    m_btnModify->setEnabled(false);
    m_gameTime.start();
    qInfo() << "slotStartGame!";
}

void MainWindow::slotGameWin()
{
    qInfo() << "slotWinGame!";
    m_btnModify->setEnabled(true);
    m_timer->stop();
    double gameTime = m_gameTime.elapsed() / 1000;
    qInfo() << "gameTime" << gameTime;
    double max = db.getMax();
    qInfo() << "max" << max;
    if (gameTime < db.getMax()) {
        RegisterDialog dlg;
        dlg.exec();
        QString name = dlg.getName();
        if (name.isNull()) {
            name = "匿名";
        }
        db.insertData(name, gameTime, int(gameTime));
        RankingDialog rdlg;
        rdlg.initData(db.getList());
        rdlg.exec();
    }
}

void MainWindow::slotGameOver()
{
    qInfo() << "game over!";
    m_btnModify->setEnabled(true);
    m_timer->stop();
}

void MainWindow::slotModifyGameLeve()
{
    SelectDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) {
        qInfo() << "level:" << dlg.getLevel();
        switch (dlg.getLevel()) {
            case GAME_LEVEL_easy:
                m_gameWidget->initGame(9, 9, 10);
                m_level = GAME_LEVEL_easy;
                setFixedSize(467, 378);
                break;
            case GAME_LEVEL_medium:
                m_gameWidget->initGame(16, 16, 40);
                m_labFlag->setText("0/40");
                m_level = GAME_LEVEL_medium;
                setFixedSize(747, 658);
                break;
            case GAME_LEVEL_hard:
                m_gameWidget->initGame(30, 16, 99);
                m_labFlag->setText("0/99");
                m_level = GAME_LEVEL_hard;
                setFixedSize(1307, 658);
                break;
        }
    }
    m_gameWidget->initGame();

    QSizePolicy sizePolicy = this->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(sizePolicy);
    m_timer->stop();
}

void MainWindow::slotShowRanking()
{
    RankingDialog dlg;
    dlg.initData(db.getList());
    dlg.exec();
}

void MainWindow::slotShowAbout()
{
    AboutDialog dlg;
    dlg.exec();
}
void MainWindow::slotFlag(int flags)
{
    QString strFlags = "";
    switch (m_level) {
        case GAME_LEVEL_easy:
            strFlags = QString::number(flags) + "/10";
            break;
        case GAME_LEVEL_medium:
            strFlags = QString::number(flags) + "/40";
            break;
        case GAME_LEVEL_hard:
            strFlags = QString::number(flags) + "/99";
            break;
    }
    m_labFlag->setText(strFlags);
}

void MainWindow::initGame()
{
    m_gameWidget->initGame();
    m_nTime = 0;
    m_btnModify->setEnabled(true);
    m_lcdNumber->display(m_nTime);
    m_timer->stop();
}

void MainWindow::onTimer()
{
    m_nTime++;

    m_lcdNumber->display(m_nTime);
}
