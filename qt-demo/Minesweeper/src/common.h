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

#ifndef COMMON_H
#define COMMON_H
#include <QString>

#define BLOCK 40  // 每一个格子的宽度

struct Block {
    int x;
    int y;
};

enum LeiStatus { isNum = 0, isLei };

enum ShowStatus {
    hideNum = 0,  // 最原始状态
    showNum,  // 点击展示其数字，如果点击的为雷那么游戏就直接结束了。
    isOk,     // 确认这个是雷,即给这个格子标上小旗
    isAsk     // 不确定这个是什么，给这个格子标上问号

};
enum GameStatus {
    gameInit = 0,  // 游戏初始状态
    gameStar,      // 游戏开始
    gameOver,  // 游戏结束，当游戏状态为结束时，需要将所有的地雷的位置标识出来。
    gameWin

};

/**
 * @brief The Cell 每一个格子的结构体
 */
struct Cell : Block {
    // 雷的状态，所有的格子有只有两种状态，雷或者是数字。
    LeiStatus leiStatus;
    // 显示状态，显示、隐藏、标记为小旗、标记为问号
    ShowStatus showStatus;
    int num;  // 表示每个位置的上下左右八个位置的雷的数据，如果雷的状态是
    Cell()
    {
        leiStatus = isNum;
        num = 0;
        showStatus = hideNum;
    }
};

#define COLOR_NUM_1 "#1B0F9B"
#define COLOR_NUM_2 "#75C481"
#define COLOR_NUM_3 "#CE5D62"
#define COLOR_NUM_4 "#150C60"
#define COLOR_NUM_5 "#800000"
#define COLOR_NUM_6 "#008080"
#define COLOR_NUM_7 "#000000"
#define COLOR_NUM_8 "#808080"

// 方格隐藏状态下的背景颜色
#define COLOR_CELL_HIDE_STATUS_BACKGROUD "#33a3dc"

// 方框边框颜色
#define COLOR_CELL_BORDER "#FFFFFF"


#define GAME_LEVEL_easy 0
#define GAME_LEVEL_medium 1
#define GAME_LEVEL_hard 2

#endif  // COMMON_H
