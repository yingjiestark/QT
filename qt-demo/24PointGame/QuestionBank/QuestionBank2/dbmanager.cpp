#include "dbmanager.h"
#include <QDir>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtDebug>
DBManager::DBManager(QObject *parent) : QObject(parent), db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString strHomePath = QDir::homePath();
    QString strSqlFile = strHomePath + "/db.sql";
        db.setDatabaseName(strSqlFile);
    if (!db.open()) {
          return;
     }

    createTable();
    deleteTable();
}

void DBManager::createTable()
{
    QString strSql =
           "create table if not exists record(id integer primary key "
           "autoincrement,num1 int not null,num2 int not null,num3 int not null,num4 int not null,c int not null);";
       QSqlError err;
       QSqlQuery query(db);
       if (!query.exec(strSql)) {
           err = query.lastError();
           qInfo() << "create table error:" << err.text() << err.type() << "\n";
           return ;
       }

    return ;
}

void DBManager::deleteTable()
{
   QString strSql  = "delete * from record;";
    QSqlError err;
    QSqlQuery query(db);
    if (!query.exec(strSql)) {
        err = query.lastError();
        qInfo() << "create table error:" << err.text() << err.type() << "\n";
        return ;
    }
}

void DBManager::insertData(int num1, int num2, int num3, int num4, int c)
{
    QSqlQuery query(db);
        QSqlError err;
        QString strSql =
            "insert into record (num1,num2,num3,num4,c) values (:num1,:num2,:num3,:num4,:c);";
        query.prepare(strSql);
        query.bindValue(":num1", num1);
        query.bindValue(":num2", num2);
        query.bindValue(":num3", num3);
        query.bindValue(":num4", num4);
        query.bindValue(":c", c);
        if (!query.exec()) {
            err = query.lastError();

            qInfo() << "insertData table error:" << err.text() << err.databaseText()
                    << "\n";
            return;
        }
        return;

}
