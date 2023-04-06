#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    QSqlDatabase db;
    void createTable();
    void deleteTable();
    void insertData(int num1,int num2,int num3,int num4,int c);


signals:

public slots:
};

#endif // DBMANAGER_H
