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

#include "db_manager.h"
#include <QDir>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QtDebug>
#include <QSqlRecord>
DBManager::DBManager(QObject *parent)
    : QObject(parent)
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    // 获取主目录
    QString strHomePath = QDir::homePath();
    strHomePath.append("/.config/minesweeper/");
    QDir dir;
    if (!isDirExist(strHomePath)) {
        dir.mkpath(strHomePath);
    }
    QString strSqlFile = strHomePath + "db.sql";
    db.setDatabaseName(strSqlFile);
    if (!db.open()) {
        return;
    }
    createTable();
}

DBManager::~DBManager() { db.close(); }

double DBManager::getMax()
{
    if (getList().size() < 10) return 999;
    QSqlError err;
    QSqlQuery query(db);

    // 查询按照时间排序，升序排序，前十总数字分数最大的值。
    QString strSql = "select max(score) from record asc score limit 0,10;";
    if (!query.exec(strSql)) {
        err = query.lastError();
        qDebug() << "create table error:" << err.text() << err.type() << "\n";
        return false;
    }
    if (query.next()) {
        return query.value(0).toDouble();
    }
    return 0;
}

void DBManager::insertData(QString strName, double data, int sec)
{
    QSqlQuery query(db);
    QSqlError err;
    QString strSql =
        "insert into record (name,score,sec) values (:name,:score,:sec);";
    query.prepare(strSql);
    query.bindValue(":name", strName);
    query.bindValue(":score", data);
    query.bindValue(":sec", sec);
    if (!query.exec()) {
        err = query.lastError();

        qInfo() << "create table error:" << err.text() << err.databaseText()
                << "\n";
        return;
    }
    return;
}

QList<recordInfo> DBManager::getList()
{
    QString strSql = "select name,score,sec from record limit 0,10;";
    QSqlQuery query(db);

    QList<recordInfo> list;

    query.prepare(strSql);
    if (query.exec()) {
        QSqlRecord rec = query.record();

        for (int r = 0; query.next(); r++) {
            recordInfo info;
            info.name = query.value(0).toString();
            info.score = query.value(1).toDouble();
            info.sec = query.value(2).toInt();
            list.append(info);
        }
    }

    return list;
}

bool DBManager::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if (dir.exists()) {
        return true;
    }
    return false;
}

bool DBManager::isTableExist(QString strTableName)
{
    QString strSql =
        QString(
            "select count(1) from sqlite_master where type='table' and name=%1")
            .arg(strTableName);
    QSqlQuery query(db);
    query.exec(strSql);
    if (query.next()) {
        if (query.value(0).toInt() == 0) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

bool DBManager::createTable()
{
    QString strSql =
        "create table if not exists record(id integer primary key "
        "autoincrement,name char(50) not null,score double,sec int);";

    QSqlError err;
    QSqlQuery query(db);
    if (!query.exec(strSql)) {
        err = query.lastError();
        qInfo() << "create table error:" << err.text() << err.type() << "\n";
        return false;
    }
    return true;
}
