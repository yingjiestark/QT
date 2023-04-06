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

#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QObject>
#include <QSqlDatabase>

typedef struct _RecordInfo {
    QString name;
    double score;
    int sec;
} recordInfo;

class DBManager : public QObject {
    Q_OBJECT
   public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    /**
     * @brief 获取数据库中前10的数据中耗时最长的数据。
     * @return
     */
    double getMax();
    /**
     * @brief insertData 插入数据
     * @param strName
     * @param data
     * @param sec
     */
    void insertData(QString strName, double data, int sec);
    /**
     * @brief 获取数据库中前10 的数据列表,用于展示数据使用.
     * @return
     */
    QList<recordInfo> getList();

   private:
    /**
     * @brief 数据库所在目录是否存在
     * @param fullPath
     * @return
     */
    bool isDirExist(QString fullPath);
    /**
     * @brief 数据表文件是否存在。
     * @param 表名称
     * @return
     */
    bool isTableExist(QString strTableName);
    /**
     * @brief createTable 创建数据表
     * @return
     */
    bool createTable();
    QSqlDatabase db;

   signals:

   public slots:
};

#endif  // DB_MANAGER_H
