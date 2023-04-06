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
#include "about_dialog.h"
#include <QDesktopServices>
#include <QUrl>
#include <QEvent>
#include <QMouseEvent>
AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , m_ptrLabMail(new QLabel(this))
    , m_ptrLabIcon(new QLabel(this))
    , m_ptrLabWeb(new QLabel(this))
    , m_ptrLayoutMain(new QVBoxLayout(this))

{
    m_ptrLabWeb->installEventFilter(this);
    // QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    initUI();
}

bool AboutDialog::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_ptrLabWeb) {
        QMouseEvent *even = (QMouseEvent *)(e);
        if (even->button() == Qt::LeftButton) {
            QDesktopServices::openUrl(QUrl("https://arv000.blog.csdn.net/"));
        }
    }
    return QWidget::eventFilter(o, e);
}

void AboutDialog::initUI()
{
    QPixmap img(":/lei.png");

    m_ptrLabMail->setText("邮箱:arv003@163.com");
    m_ptrLabWeb->setText("博客:https://arv000.blog.csdn.net/");
    m_ptrLabIcon->setPixmap(img);
    m_ptrLayoutMain->addWidget(m_ptrLabIcon);
    m_ptrLayoutMain->addWidget(m_ptrLabMail);
    m_ptrLayoutMain->addWidget(m_ptrLabWeb);
    setLayout(m_ptrLayoutMain);
}

void AboutDialog::initConnect() {}
