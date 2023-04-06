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

#ifndef RANKING_DIALOG_H
#define RANKING_DIALOG_H
#include <QDialog>
#include <QGridLayout>
#include "../db/db_manager.h"
class RankingDialog : public QDialog {
   public:
    RankingDialog(QWidget *parent = nullptr);
    void initData(QList<recordInfo> list);

   private:
    void initUI();
    QGridLayout *m_ptrLayoutMain;
};

#endif  // RANKING_DIALOG_H
