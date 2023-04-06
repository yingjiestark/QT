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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game_widget.h"
#include <QtDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include "../db/db_manager.h"
#include <QTime>
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    QWidget *m_mainView;
    QHBoxLayout *m_mainlayout;
    QVBoxLayout *m_showInfoLayout;
    // 时间图片
    QLabel *m_imgTime;
    // 时间
    QLCDNumber *m_lcdNumber;
    QLabel *m_imgFlag;
    QLabel *m_labFlag;
    QPushButton *m_btn;
    // 修改游戏难度
    QPushButton *m_btnModify;
    // 显示排名
    QPushButton *m_btnRanking;
    // 显示关于
    QPushButton *m_btnAbout;
    QGameWidget *m_gameWidget;
    QTimer *m_timer;
    QTime m_gameTime;  // 记录游戏时间
    int m_nTime;
    int m_level;  // 记录游戏当前的难度
    DBManager db;

   private:
    void initUI();
    void initConnect();

   public slots:
    void onTimer();
    void slotGameStart();
    void slotGameWin();
    void slotGameOver();
    void slotModifyGameLeve();
    void slotShowRanking();
    void slotShowAbout();
    void slotFlag(int flags);
    void initGame();
};

#endif  // MAINWINDOW_H
