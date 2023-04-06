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

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
class SelectDialog : public QDialog {
    Q_OBJECT
   public:
    SelectDialog(QWidget *parent);

   private:
    QPushButton *m_ptrBtnEasy;
    QPushButton *m_ptrBtnMedium;
    QPushButton *m_ptrBtnHard;
    QVBoxLayout *m_ptrLayoutMain;
    int m_iLevel;
    void initUI();
    void initConnect();

   public:
    int getLevel();

   public slots:
    void slotEasy();
    void slotMedium();
    void slotBtnHard();
};

#endif  // SELECTDIALOG_H
