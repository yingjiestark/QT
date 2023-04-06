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

#include "select_dialog.h"

SelectDialog::SelectDialog(QWidget *parent)
    : QDialog(parent)
    , m_ptrBtnEasy(new QPushButton(this))
    , m_ptrBtnMedium(new QPushButton(this))
    , m_ptrBtnHard(new QPushButton(this))
    , m_ptrLayoutMain(new QVBoxLayout)
    , m_iLevel(0)
{
    initUI();
    initConnect();
}

void SelectDialog::initUI()
{
    m_ptrBtnEasy->setText(tr("简单 (9*9)"));
    m_ptrBtnEasy->setFocusPolicy(Qt::NoFocus);
    m_ptrBtnMedium->setText(tr("中等 (16*16)"));
    m_ptrBtnMedium->setFocusPolicy(Qt::NoFocus);
    m_ptrBtnHard->setText(tr("困难 (30*16)"));
    m_ptrBtnHard->setFocusPolicy(Qt::NoFocus);

    m_ptrLayoutMain->addWidget(m_ptrBtnEasy);
    m_ptrLayoutMain->addWidget(m_ptrBtnMedium);
    m_ptrLayoutMain->addWidget(m_ptrBtnHard);
    setLayout(m_ptrLayoutMain);
    setMinimumWidth(500);
    setMaximumWidth(500);
    setWindowTitle(tr("选择游戏难度"));
}

void SelectDialog::initConnect()
{
    connect(m_ptrBtnEasy, &QPushButton::clicked, this, &SelectDialog::slotEasy);

    connect(m_ptrBtnMedium, &QPushButton::clicked, this,
            &SelectDialog::slotMedium);
    connect(m_ptrBtnHard, &QPushButton::clicked, this,
            &SelectDialog::slotBtnHard);
}

int SelectDialog::getLevel() { return m_iLevel; }

void SelectDialog::slotEasy()
{
    m_iLevel = 0;
    QDialog::accept();
}

void SelectDialog::slotMedium()
{
    m_iLevel = 1;
    QDialog::accept();
}

void SelectDialog::slotBtnHard()
{
    m_iLevel = 2;
    QDialog::accept();
}
