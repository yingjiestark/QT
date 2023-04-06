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

#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
class RegisterDialog : public QDialog {
   public:
    RegisterDialog(QWidget *parent = nullptr);
    QString getName();

   private:
    void initUI();
    void initConnect();
    QLabel *m_ptrLabInfo;
    QLineEdit *m_ptrEdtName;
    QPushButton *m_ptrBtnSave;
    QVBoxLayout *m_ptrLayoutMain;
    QString m_strName;
   public slots:
    void slotSaveName();
};

#endif  // REGISTER_DIALOG_H
