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

#include "register_dialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , m_ptrLabInfo(new QLabel(this))
    , m_ptrEdtName(new QLineEdit(this))
    , m_ptrBtnSave(new QPushButton(this))
    , m_ptrLayoutMain(new QVBoxLayout)
{
    initUI();
    initConnect();
}

QString RegisterDialog::getName() { return m_strName; }

void RegisterDialog::initUI()
{
    m_ptrBtnSave->setText(tr("保存"));
    setWindowTitle(tr("排名记录"));
    m_ptrLayoutMain->addWidget(m_ptrLabInfo);
    m_ptrLayoutMain->addWidget(m_ptrEdtName);
    m_ptrLayoutMain->addWidget(m_ptrBtnSave);
    setLayout(m_ptrLayoutMain);
}

void RegisterDialog::initConnect()
{
    connect(m_ptrBtnSave, &QPushButton::clicked, this,
            &RegisterDialog::slotSaveName);
}

void RegisterDialog::slotSaveName()
{
    m_strName = m_ptrEdtName->text();
    QDialog::accept();
}
