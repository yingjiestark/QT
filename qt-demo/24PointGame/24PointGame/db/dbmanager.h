#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include "common.h"
class DBManager : public QObject {
    Q_OBJECT
   public:
    static DBManager *getInstance();
    int getMax();                  // 获取题库的总数
    QList<ModeItem> getAllData();  // 获取关卡所有的数据,为了初始化游戏的锁
    ModeItem getLevelData(int level);  // 获取某一关卡的数据
    void unlockLevel(int level);       // 解锁否一关卡
    int getCurrentLevel();             // 获取最后一次通关的关卡
   private:
    explicit DBManager(QObject *parent = nullptr);
    bool isDirExist(QString fullPath);
    // 创建数据库表内容
    void createTable();
    // 表是否存在
    bool isTableExist(QString strTableName);

    ~DBManager();
    static DBManager *m_ptrInstance;
    QSqlDatabase db;
};

#endif  // DBMANAGER_H
