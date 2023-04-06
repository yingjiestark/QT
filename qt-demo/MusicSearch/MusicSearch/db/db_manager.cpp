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
#include <QDateTime>
#include <QElapsedTimer>
DBManager *DBManager::m_pInstance = nullptr;  // 懒汉模式
DBManager::DBManager(QObject *parent)
    : QObject(parent)
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QElapsedTimer time;
    time.start();
    // 获取主目录
    QString strHomePath = QDir::homePath();
    strHomePath.append("/.config/sreachMusic/");
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
    qInfo() << time.elapsed() / 1000000 << "ms";
}

DBManager *DBManager::instance()
{
    if (m_pInstance == nullptr) {
        m_pInstance = new DBManager();
    }
    return m_pInstance;
}

DBManager::~DBManager() { db.close(); }

/**
 * @brief 插入数据
 * @param info
 */
void DBManager::insertData(AbsListLocal info)
{
    QSqlQuery query(db);
    QSqlError err;
    QString strSql = "insert into " + tableName +
                     " (name,path,img,url,rid,remark)values(:name,:"
                     "path,:img,:url,:rid,:remark); ";
    qInfo() << strSql;
    query.prepare(strSql);
    query.bindValue(":name", info.NAME);
    query.bindValue(":path", info.localPath);
    query.bindValue(":img", info.localImage);
    query.bindValue(":url", info.URL);
    query.bindValue(":remark", "f");
    query.bindValue(":rid", info.MUSICRID);
    // query.bindValue(":create_time", int(QDateTime::currentSecsSinceEpoch()));
    if (!query.exec()) {
        err = query.lastError();

        qInfo() << "insertData table error:" << err.text() << ","
                << err.databaseText() << "," << err.driverText() << ","
                << err.nativeErrorCode();

        return;
    }
}

/**
 * @brief 获取当前页的音乐列表
 * @param page 从0开始计算第一页
 * @return
 */
QList<AbsListLocal> DBManager::getList(int page)
{
    QSqlQuery query(db);
    QString strSql = "select name,path,img,url,rid from " + tableName + ";";
    QList<AbsListLocal> list;
    query.prepare(strSql);
    if (query.exec()) {
        QSqlRecord rec = query.record();
        for (int r = 0; query.next(); r++) {
            AbsListLocal info;
            info.NAME = query.value(0).toString();
            info.localPath = query.value(1).toString();
            info.localImage = query.value(2).toString();
            info.URL = query.value(3).toString();
            info.MUSICRID = query.value(4).toString();
            list.append(info);
        }
    }
    return list;
}

/**
 * @brief 获取某个音乐的信息，通过ID
 * @param id
 * @return
 */
AbsListLocal DBManager::getInfoFromId(QString id)
{
    AbsListLocal info;
    QString strSql = "select name,path,img,url,rid from " + tableName +
                     " where id='" + id + "';";
    QSqlQuery query(db);
    QSqlError err;
    query.prepare(strSql);
    if (query.exec()) {
        info.NAME = query.value(0).toString();
        info.localPath = query.value(1).toString();
        info.localImage = query.value(2).toString();
        info.URL = query.value(3).toString();
        info.MUSICRID = query.value(4).toString();
    }
    return info;
}

QList<AbsListLocal> DBManager::getInfoFromRId(QString rid)
{
    QList<AbsListLocal> list;

    QString strSql = "select name,path,img,url,rid from " + tableName +
                     " where rid='" + rid + "';";
    qInfo() << strSql;
    QSqlQuery query(db);
    QSqlError err;
    query.prepare(strSql);
    if (query.exec()) {
        QSqlRecord rec = query.record();
        for (int r = 0; query.next(); r++) {
            AbsListLocal info;
            info.NAME = query.value(0).toString();
            info.localPath = query.value(1).toString();
            info.localImage = query.value(2).toString();
            info.URL = query.value(3).toString();
            info.MUSICRID = query.value(4).toString();
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

bool DBManager::createTable()
{
    QString strSql = "create table if not exists " + tableName +
                     "(id integer primary key autoincrement"
                     ",name     char(50)    not null"
                     ",path     char(255)   not null"
                     ",img     char(255)  "
                     ",url      char(255)   not null"
                     ",rid      char(255)   not null"
                     ",remark   char(255)   not null"
                     ",careate_time int);";
    qInfo() << strSql;
    QSqlError err;
    QSqlQuery query(db);
    if (!query.exec(strSql)) {
        err = query.lastError();
        qInfo() << "create table error:" << err.text() << err.type() << "\n";
        return false;
    }
    return true;
}
