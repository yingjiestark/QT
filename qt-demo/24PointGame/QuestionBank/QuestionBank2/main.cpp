#include <QCoreApplication>
#include <QtDebug>
#include <QFile>

#include "lnum.h"
#include "common.h"
#include <dbmanager.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 遍历数

    QList<struNum > list = initList();
    qInfo()<<list.size();
    DBManager dbm;
    foreach(auto item ,list){
       int c = is24OK(item.num1,item.num2,item.num3,item.num4);
       dbm.insertData(item.num1,item.num2,item.num3,item.num4,c);
    }
    return 0;

    return a.exec();
}
