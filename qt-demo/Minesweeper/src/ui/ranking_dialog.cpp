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

#include <QLabel>
#include "ranking_dialog.h"

RankingDialog::RankingDialog(QWidget *parent)
    : QDialog(parent)
    , m_ptrLayoutMain(new QGridLayout)
{
    initUI();
    setLayout(m_ptrLayoutMain);
}

void RankingDialog::initData(QList<recordInfo> list)
{
    int size = list.size();
    QLabel *labNumHead = new QLabel(this);
    QLabel *labNameHead = new QLabel(this);
    QLabel *labTimeHead = new QLabel(this);
    labNumHead->setText(tr("排名"));
    labNameHead->setText(tr("名字"));
    labTimeHead->setText(tr("时间"));
    m_ptrLayoutMain->addWidget(labNumHead, 0, 0, Qt::AlignCenter);
    m_ptrLayoutMain->addWidget(labNameHead, 0, 1, Qt::AlignCenter);
    m_ptrLayoutMain->addWidget(labTimeHead, 0, 2, Qt::AlignCenter);

    for (int i = 0; i < 10; i++) {
        QLabel *labNum = new QLabel(this);
        QLabel *labName = new QLabel(this);
        QLabel *labTime = new QLabel(this);
        labNum->setText(QString::number(i + 1));

        if (size > i) {
            auto item = list.at(i);
            labName->setText(item.name);
            labTime->setText(QString::number(item.score));
        }
        m_ptrLayoutMain->addWidget(labNum, i + 1, 0, Qt::AlignCenter);
        m_ptrLayoutMain->addWidget(labName, i + 1, 1, Qt::AlignCenter);
        m_ptrLayoutMain->addWidget(labTime, i + 1, 2, Qt::AlignCenter);
    }
}

void RankingDialog::initUI()
{
    setWindowTitle(tr("查看排名"));
    setFixedSize(300, 300);
}
