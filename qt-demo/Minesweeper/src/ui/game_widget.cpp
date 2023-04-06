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

#include "game_widget.h"
#include "../common.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

QGameWidget::QGameWidget(int max_block_x, int max_block_y, int sum_lei,
                         QWidget *parent)
    : QWidget(parent)
    , m_max_block_x(max_block_x)
    , m_max_block_y(max_block_y)
    , m_sum_lei(sum_lei)
    , m_flags(0)
    , m_isClickLeftButton(false)
    , m_currentSelectCell(nullptr)
    , m_gameStatus(gameInit)
{
    setFixedSize(max_block_x * BLOCK + 2, max_block_y * BLOCK + 2);
    initLei();
}

void QGameWidget::paintBackground(QPaintEvent *)
{
    QPainter painter(this);
    QColor color("#0000000");
    painter.setPen(color);
    painter.drawRect(0, 0, this->width() - 2, this->height() - 2);
}

void QGameWidget::paintBlock(QPaintEvent *)
{
    QPainter painter(this);
    QFont font;
    QColor color;
    QFontMetrics fm(font);
    for (int i = 0; i < m_max_block_x; i++) {
        for (int j = 0; j < m_max_block_y; j++) {
            Cell *lei = getCell(i, j);

            if (lei->showStatus == showNum) {
                // 绘画数字
                paintBlockNum(&painter, lei);
            } else if (lei->showStatus == isOk) {
                paintBlockIsOK(&painter, lei);
            } else if (lei->showStatus == hideNum) {
                painter.setBrush(QColor(COLOR_CELL_HIDE_STATUS_BACKGROUD));
                color.setNamedColor(COLOR_CELL_BORDER);
                painter.setPen(color);
                painter.drawRect(i * BLOCK + 2, j * BLOCK + 2, BLOCK - 4,
                                 BLOCK - 4);
                if (m_gameStatus == gameOver && lei->leiStatus == isLei) {
                    painter.drawImage(QRectF(i * BLOCK + 4, j * BLOCK + 4,
                                             BLOCK - 8, BLOCK - 8),
                                      QImage(":/lei.png"));
                }
            } else if (lei->showStatus == isAsk) {
                paintBlockIsAsk(&painter, lei);
            }
        }
    }
}

void QGameWidget::paintBlockIsOK(QPainter *painter, Cell *lei)
{
    int x = lei->x;
    int y = lei->y;
    QColor color;
    painter->setBrush(Qt::white);
    color.setNamedColor(COLOR_CELL_BORDER);
    painter->setPen(color);
    painter->drawRect(x * BLOCK + 2, y * BLOCK + 2, BLOCK - 4, BLOCK - 4);
    painter->drawImage(QRectF(x * BLOCK, y * BLOCK, BLOCK, BLOCK),
                       QImage(":/flag.png"));
}

void QGameWidget::paintBlockIsAsk(QPainter *painter, Cell *lei)
{
    int x = lei->x;
    int y = lei->y;
    int padding = 8;
    QColor color;
    painter->setBrush(QColor(COLOR_CELL_HIDE_STATUS_BACKGROUD));
    color.setNamedColor(COLOR_CELL_BORDER);
    painter->setPen(color);
    painter->drawRect(x * BLOCK + 2, y * BLOCK + 2, BLOCK - 4, BLOCK - 4);
    painter->drawImage(QRectF(x * BLOCK + padding, y * BLOCK + padding,
                              BLOCK - padding * 2, BLOCK - padding * 2),
                       QImage(":/ask.png"));
}

void QGameWidget::paintBlockNum(QPainter *painter, Cell *lei)
{
    QFont font;
    QFontMetrics fm(font);
    QColor color;
    int x = lei->x;
    int y = lei->y;

    font.setBold(true);
    painter->setBrush(Qt::white);
    color.setNamedColor(COLOR_CELL_BORDER);
    painter->setPen(color);
    painter->drawRect(x * BLOCK + 2, y * BLOCK + 2, BLOCK - 4, BLOCK - 4);

    painter->setFont(font);
    if (lei->num == 0) {
        return;
    }
    if (lei->leiStatus == isNum) {
        switch (lei->num) {
            case 1:
                color.setNamedColor(COLOR_NUM_1);
                break;
            case 2:
                color.setNamedColor(COLOR_NUM_2);
                break;
            case 3:
                color.setNamedColor(COLOR_NUM_3);
                break;
            case 4:
                color.setNamedColor(COLOR_NUM_4);
                break;
            case 5:
                color.setNamedColor(COLOR_NUM_5);
                break;
            case 6:
                color.setNamedColor(COLOR_NUM_6);
                break;
            case 7:
                color.setNamedColor(COLOR_NUM_7);
                break;
            case 8:
                color.setNamedColor(COLOR_NUM_8);
                break;
        }
        painter->setPen(color);
        painter->drawText(
            x * BLOCK + 1 + BLOCK / 2 - fm.width(QString::number(lei->num)) / 2,
            y * BLOCK + 1 + BLOCK / 2 - fm.height() / 2 - 1, fm.width("1"),
            fm.height(), 1, QString::number(lei->num));
    }
}

void QGameWidget::paintTip()
{
     QColor color;
    QPainter painter(this);
    if (m_isClickLeftButton) {
        if (m_currentSelectCell != nullptr) {
            int b_x = m_currentSelectCell->x;
            int b_y = m_currentSelectCell->y;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (0 == i && 0 == j) continue;
                    int index = getIndex(b_x + i, b_y + j);
                    if (index < 0) continue;
                    if (m_cells.at(index).showStatus == hideNum ||
                        isAsk == m_cells.at(index).showStatus) {
                        color.setNamedColor(COLOR_CELL_BORDER);
                        painter.setPen(color);
                        painter.setBrush(QBrush(QColor(193, 210, 240)));
                        painter.drawRect((b_x + i) * BLOCK + 2,
                                         (b_y + j) * BLOCK + 2, BLOCK - 4,
                                         BLOCK - 4);
                    }
                }
            }
        }
    }
}

bool QGameWidget::getBlockPoint(int mouse_x, int mouse_y, Block *block)
{
    for (int i = 0; i < m_max_block_x; i++) {
        for (int j = 0; j < m_max_block_y; j++) {
            if (mouse_x >= i * BLOCK + 1 && mouse_x <= (i + 1) * BLOCK - 2 &&
                mouse_y >= j * BLOCK + 1 && mouse_y <= (j + 1) * BLOCK - 2) {
                block->x = i;
                block->y = j;
                return true;
            }
        }
    }
    return false;
}

int QGameWidget::getRandom(int max)
{
    int res = qrand();
    res = res % max;
    return res;
}

Cell *QGameWidget::getCell(int block_x, int block_y)
{
    if (block_x >= m_max_block_x || block_y >= m_max_block_y || block_x < 0 ||
        block_y < 0) {
        return nullptr;
    }
    return &m_cells[getIndex(block_x, block_y)];
}

void QGameWidget::initLei()
{
    // 清空所有的格子
    m_cells.clear();
    // 初始化小旗的数量。
    m_flags = 0;
    for (int i = 0; i < m_max_block_x; i++) {
        for (int j = 0; j < m_max_block_y; j++) {
            Cell lei;
            lei.x = i;
            lei.y = j;
            m_cells.push_back(lei);
        }
    }

    // 初始化雷的位置
    int sum = 0;
    int size = m_cells.size();
    do {
        int ran = getRandom(size);
        if (m_cells.at(ran).leiStatus != isLei) {
            sum++;
            m_cells[ran].leiStatus = isLei;
        }
    } while (sum < m_sum_lei);
    // 初始化个个数据
    for (int i = 0; i < m_cells.size(); i++) {
        // 如果这个位置是雷就不需要统计了
        if (m_cells[i].leiStatus == isLei) continue;
        int sum = sumLeiStatus(m_cells[i].x, m_cells[i].y, isLei);
        m_cells[i].num = sum;
    }
}

int QGameWidget::sumLeiStatus(int block_x, int block_y, LeiStatus leiStatus)
{
    int sum = 0;
    int b_x = block_x;
    int b_y = block_y;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int index = getIndex(b_x - i, b_y - j);
            if (index < 0) {
                continue;
            }
            if (m_cells.at(index).leiStatus == leiStatus) {
                sum++;
            }
        }
    }
    return sum;
}

int QGameWidget::sumShowStatus(int block_x, int block_y, ShowStatus showStatus)
{
    int sum = 0;
    int b_x = block_x;
    int b_y = block_y;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (0 == i && 0 == j) continue;
            int index = getIndex(b_x - i, b_y - j);
            if (index < 0) continue;
            if (m_cells.at(index).showStatus == showStatus) {
                sum++;
            }
        }
    }
    return sum;
}

void QGameWidget::clickCell(int block_x, int block_y)
{
    Cell *cell = getCell(block_x, block_y);
    if (nullptr == cell) return;
    if (cell->leiStatus == isLei) {
        // game over;
        m_gameStatus = gameOver;
        m_isClickLeftButton = false;
        update();
        emit sigGameOver();
        return;
    }

    if (cell->num == 0) {
        updateLei(block_x, block_y);
    } else {
        cell->showStatus = showNum;
    }
    isWin();
}

void QGameWidget::updateLei(int block_x, int block_y)
{
    // 判断坐标的合法性.
    if (getIndex(block_x, block_y) < 0 ||
        getIndex(block_x, block_y) >= m_max_block_x * m_max_block_y) {
        return;
    }

    if (m_cells[getIndex(block_x, block_y)].showStatus == hideNum ||
        m_cells[getIndex(block_x, block_y)].showStatus == isAsk) {
        m_cells[getIndex(block_x, block_y)].showStatus = showNum;
        if (m_cells[getIndex(block_x, block_y)].num == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (!(i == 0 && j == 0))
                        updateLei(block_x + i, block_y + j);
                }
            }
        }
    }
    return;
}

int QGameWidget::getIndex(int block_x, int block_y)
{
    if (block_x < 0 || block_y < 0) return -1;
    if (block_x >= m_max_block_x || block_y >= m_max_block_y) return -2;
    return block_x * m_max_block_y + block_y;
}

bool QGameWidget::isWin()
{
    int sum = 0;
    // 遍历所有的方格,判断其展示的数据以及标识的数据的和是否等于
    for (int i = 0; i < m_cells.size(); i++) {
        if (m_cells.at(i).showStatus == showNum) {
            sum++;
        } else if (m_cells.at(i).leiStatus == isLei &&
                   m_cells.at(i).showStatus == isOk) {
            sum++;
        }
    }
    // 数据总和是否等于初始化方格列表,如果不等于,那么直接返回游戏没有结束.
    if (sum != m_cells.size()) {
        return false;
    }
    if (m_gameStatus != gameWin) {
        emit sigGameWin();
        m_gameStatus = gameWin;
    }
    return true;
}

void QGameWidget::initGame()
{
    m_gameStatus = gameInit;
    initLei();
    update();
}
/**
 * @brief QGameWidget::initGame
 * @param x
 * @param y
 * @param sum_lei
 */
void QGameWidget::initGame(int x, int y, int sum_lei)
{
    m_max_block_x = x;
    m_max_block_y = y;
    m_sum_lei = sum_lei;
    setFixedSize(x * BLOCK + 2, y * BLOCK + 2);
    initLei();
}

void QGameWidget::paintEvent(QPaintEvent *event)
{
    paintBackground(event);
    paintBlock(event);
    paintTip();
}

void QGameWidget::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标的坐标点。
    int mouse_x = event->x();
    int mouse_y = event->y();
    if (m_gameStatus == gameInit) {
        emit sigGameStart();
        m_gameStatus = gameStar;
    }
    if (m_gameStatus == gameOver) {
        return;
    }
    Block block;
    // 通过鼠标的坐标点获取方格的坐标点
    if (!getBlockPoint(mouse_x, mouse_y, &block)) {
        return;
    }
    // 获取根据坐标点获取方格的信息
    Cell *cell = getCell(block.x, block.y);
    if (event->button() == Qt::LeftButton) {
        Block block;
        getBlockPoint(mouse_x, mouse_y, &block);
        // 记录当前选中的方格
        m_currentSelectCell = getCell(block.x, block.y);
        // 记录鼠标的点击状态
        m_isClickLeftButton = true;
        if (!(hideNum == cell->showStatus || isAsk == cell->showStatus)) {
            update();
            return;
        }
        clickCell(block.x, block.y);
    } else if (event->button() == Qt::RightButton) {
        if (cell->showStatus == hideNum) {
            if (m_flags < m_sum_lei) {
                cell->showStatus = isOk;
                m_flags++;
                emit sigFlags(m_flags);
            }

        } else if (cell->showStatus == isOk) {
            qInfo() << "ok";
            cell->showStatus = isAsk;
            m_flags--;
            emit sigFlags(m_flags);
        } else if (cell->showStatus == isAsk) {
            cell->showStatus = hideNum;
        }
        isWin();
    }
    update();
}

void QGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isClickLeftButton = false;
        update();
    }
}

void QGameWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (m_gameStatus == gameOver) {
        return;
    }
    // 获取当前的内容
    int mouse_x = event->x();
    int mouse_y = event->y();
    Block block;
    bool ret = getBlockPoint(mouse_x, mouse_y, &block);

    if (ret) {
        // 统计当前的标识类的数量
        Cell *cell = getCell(block.x, block.y);
        if (nullptr == cell) return;
        // 统计被标记为小旗的数量。
        int sum = sumShowStatus(cell->x, cell->y, isOk);
        if (sum != cell->num || cell->showStatus != showNum) {
            return;
        }
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (0 == i && 0 == j) continue;
                if (getCell(cell->x + i, cell->y + j) != nullptr &&
                    getCell(cell->x + i, cell->y + j)->showStatus != isOk)
                    clickCell(cell->x + i, cell->y + j);  // 右上
            }
        }
    }
}

void QGameWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 如果当前有见按钮
    if (m_isClickLeftButton) {
        int mouse_x = event->x();
        int mouse_y = event->y();
        Block block;
        if (!getBlockPoint(mouse_x, mouse_y, &block)) return;
        // 获取当前鼠标所在位置的方格。
        m_currentSelectCell = getCell(block.x, block.y);
        update();
    }
}
