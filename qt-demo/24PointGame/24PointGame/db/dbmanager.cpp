#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QDir>
#include <QFile>
#include <QtDebug>
DBManager *DBManager::m_ptrInstance = nullptr;

DBManager *DBManager::getInstance()
{
    if (m_ptrInstance == nullptr) {
        m_ptrInstance = new DBManager();
    }
    return m_ptrInstance;
}

int DBManager::getMax()
{
    QSqlQuery query(db);
    query.exec(QString("select count(*) from %1").arg("record"));
    if (query.next()) {
        return query.value(0).toInt();
    }
}

QList<ModeItem> DBManager::getAllData()
{
    QList<ModeItem> list;
    QSqlQuery query(db);
    QString sql =
        QString("select id,num1,num2,num3,num4,status from %1").arg("record");
    query.prepare(sql);
    QSqlRecord rec = query.record();
    if (query.exec()) {
        for (int row = 0; query.next(); row++) {
            ModeItem item;
            item.id = query.value(0).toInt();
            item.num1 = query.value(1).toInt();
            item.num2 = query.value(2).toInt();
            item.num3 = query.value(3).toInt();
            item.num4 = query.value(4).toInt();
            item.status = query.value(5).toInt();
            list.append(item);
        }
    }
    return list;
}

ModeItem DBManager::getLevelData(int level)
{
    QSqlQuery query(db);
    ModeItem item;
    QString sql =
        QString(
            "select id,num1,num2,num3,num4,status from record where id = '%1';")
            .arg(QString::number(level));
    query.exec(sql);
    if (query.next()) {
        item.id = query.value(0).toInt();
        item.num1 = query.value(1).toInt();
        item.num2 = query.value(2).toInt();
        item.num3 = query.value(3).toInt();
        item.num4 = query.value(4).toInt();
        item.status = query.value(5).toInt();
        qInfo() << item.id << ":" << query.value(5).toString();
        return item;
    } else {
        qInfo() << query.lastError();
    }
    return item;
}

void DBManager::unlockLevel(int level)
{
    QSqlQuery query(db);
    QString sql = QString("update record set status = 1 where id= '%1';")
                      .arg(QString::number(level));
    query.prepare(sql);
    if (!query.exec()) {
        qInfo() << query.lastError();
    }
}

int DBManager::getCurrentLevel()
{
    QSqlQuery query(db);
    QString sql = QString(
        "select id from record where status = '1' order by id desc limit 0,1;");
    int id = 1;
    query.exec(sql);
    if (query.next()) {
        int id = query.value(0).toInt();

        return id;
    } else {
        qInfo() << query.lastError();
    }
    return id;
}

DBManager::DBManager(QObject *parent)
    : QObject(parent)
    , db(QSqlDatabase::addDatabase("QSQLITE"))

{
    QString strHomePath = QDir::homePath();
    strHomePath.append("/.config/24PointGame/");
    QDir dir;
    // 目录是否存在不存在则创建目录。
    if (!isDirExist(strHomePath)) {
        dir.mkpath(strHomePath);
    }
    QString strSqlFile = strHomePath + "game.db";
    QFile file(strSqlFile);
    if (!file.exists()) {
        createTable();
    }
    db.setDatabaseName(strSqlFile);
    // 打开数据库
    if (!db.open()) {
        return;
    }
}

bool DBManager::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if (dir.exists()) {
        return true;
    }
    return false;
}

void DBManager::createTable()
{
    QString strHomePath = QDir::homePath();
    strHomePath.append("/.config/24PointGame/");
    QDir dir;
    // 目录是否存在不存在则创建目录。
    if (!isDirExist(strHomePath)) {
        dir.mkpath(strHomePath);
    }
    QString strSqlFile = strHomePath + "game.db";

    QFile file(":/db/game.db");
    file.open(QIODevice::ReadOnly | QIODevice::Unbuffered);
    QFile file2(strSqlFile);
    file2.open(QIODevice::WriteOnly);
    file2.write(file.readAll());
    file2.close();
    file.close();
}

bool DBManager::isTableExist(QString strTableName)
{
    QSqlQuery query(db);
    query.exec(QString("select count(*) from sqlite_master where type='table' "
                       "and name='%1'")
                   .arg(strTableName));
    if (query.next()) {
        if (query.value(0).toInt() == 0) {
            return false;
        } else {
            return true;
        }
    }
}

DBManager::~DBManager() {}
