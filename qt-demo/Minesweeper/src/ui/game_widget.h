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

#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>

#include "../common.h"

class QGameWidget : public QWidget {
    Q_OBJECT
   public:
    explicit QGameWidget(int max_block_x, int max_block_y, int sum_lei,
                         QWidget *parent = nullptr);
   signals:

   public slots:

    // QWidget interface
   private:
    // 绘制背景格子
    void paintBackground(QPaintEvent *event);
    /**
     * @brief paintBlock 绘画方格
     * @param event
     */
    void paintBlock(QPaintEvent *event);
    /**
     * @brief 绘画方格中的数字
     * @param painter 画笔
     * @param lei    方格内容
     */
    void paintBlockNum(QPainter *painter, Cell *lei);

    /**
     * @brief paintBlockIsOK 绘画方格中小标旗
     * @param painter        画笔
     * @param lei            方格内容
     */
    void paintBlockIsOK(QPainter *painter, Cell *lei);

    /**
     * @brief paintBlockIsAsk 绘画方格中问号
     * @param painter         画笔
     * @param lei             方格内容
     */
    void paintBlockIsAsk(QPainter *painter, Cell *lei);
    // 根据按钮位置绘画提示的格子。
    void paintTip();
    /**
     * @brief getBlockPoint 根据鼠标的px值，获取格子的坐标
     * @param mouse_x   鼠标x坐标点
     * @param mouse_y   鼠标y坐标点
     * @param block     返回对应的格子坐标
     * @return
     */
    bool getBlockPoint(int mouse_x, int mouse_y, Block *block);
    /**
     * @brief getRandom 获取指定大小的随机数
     * @param max   [0,max)
     * @return 返回 [0,max) 范围的随机数
     */
    int getRandom(int max);
    /**
     * @brief getCell 获取格子
     * @param block_x 通过格子的x坐标
     * @param block_y 通过格子的y坐标
     * @return
     */
    Cell *getCell(int block_x, int block_y);
    /**
     * @brief 初始化
     */
    void initLei();
    /**
     * @brief sumLeiStatus 统计当前坐标的周围数据是雷的总数
     * @param block_x   当前坐标的X值
     * @param block_y   当前坐标的Y值
     * @param leiStatus 需要统计的状态。
     * @return
     */
    int sumLeiStatus(int block_x, int block_y, LeiStatus leiStatus);
    /**
     * @brief sumShowStatus 统计指定坐标,指定展示状态的总数
     * @param block_x       当前坐标的X值
     * @param block_y       当前坐标的Y值
     * @param showStatus    展示状态
     * @return    总数
     */
    int sumShowStatus(int block_x, int block_y, ShowStatus showStatus);

    /**
     * @brief clickCell 鼠标做点击逻辑
     * @param block_x
     * @param block_y
     */
    void clickCell(int block_x, int block_y);
    void updateLei(int block_x, int block_y);
    /**
     * @brief getIndex
     * 获取格子的索引坐标，由于格子的存储使用列表的方式进行存储的，所以需要将二位坐标转化为列表索引
     * @param block_x
     * @param block_y
     * @return
     */
    int getIndex(int block_x, int block_y);

    int m_max_block_x;  // 游戏水平坐标的格子数
    int m_max_block_y;  // 游戏垂直坐标的格子数
    int m_sum_lei;      // 雷的总数。
    int m_flags;  // 小旗子的数量，该数量不能大于雷的总数。

    // 是否按下左键,用于记录鼠标按下状态，因为需要做数字提示
    bool m_isClickLeftButton;
    Cell *m_currentSelectCell;  // 当前选中状态的
    GameStatus m_gameStatus;    // 游戏状态
    QVector<Cell> m_cells;      // 格子的数据存储列表.
    // 是否获取胜利
    bool isWin();
   signals:
    void sigGameWin();    // 通知游戏获胜了。
    void sigGameOver();   // 通知游戏结束
    void sigGameStart();  // 通知界面游戏开始
    void sigFlags(int flags);

   public slots:
    void initGame();  // 初始化游戏
    void initGame(int x, int y, int sum_lei);

   protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif  // GAME_WIDGET_H
