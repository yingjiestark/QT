#include "common.h"
#include <QtDebug>
#include <QFile>
#include <QDir>

int is24OK(LNum num1, LNum num2, LNum num3, LNum num4)
{
    int result = 0;
     QList<struRecordNum> list;
    LNum numList[4] = {num1,num2,num3,num4};
        // 交换4个数字的顺序。
        for (int i1 = 0 ; i1 < 4; i1 ++) {
            for (int i2 = 0 ; i2 < 4; i2 ++){
                if(i1 == i2) continue;
                for (int i3 = 0 ; i3 < 4; i3 ++){
                    if(i2 == i3 || i1 == i3) continue;
                    for (int i4 = 0 ; i4 < 4; i4 ++){
                        if(i1 == i4 || i2 == i4 || i3 == i4) continue;
                        //  qInfo()<<numList[i1]<<" "<<numList[i2] <<" "<< numList[i3] <<" "<<" "<< numList[i4];
                          int x=suanfatongji(numList[i1],numList[i2],numList[i3],numList[i4],&list);
                          if(x !=0){
                              qInfo()<<"x:"<<x;
                              result += x;
                          }
                    }
                }
            }
        }
        return result;
}

int suanfatongji(LNum num1, LNum num2, LNum num3, LNum num4, QList<struRecordNum> *list)
{
        LNum sum = 0;
        QString aFileName = QDir::homePath();
        aFileName += "/tmp.txt";
        QFile   aFile(aFileName);

        int c= 0;
        for(int i1 = 0 ; i1 < 4; i1 ++){
            for(int i2 = 0 ; i2 < 4; i2 ++ ){
                for(int i3 = 0 ; i3 < 4; i3 ++){
                    sum = jisuan(jisuan(jisuan (num1,num2,i1),num3,i2),num4,i3) ;
                    if(24.0  == sum.data()){
                        // 是否找到相同的算法，因为有重复数字可能导致算法想法和数字相同的情况。
                        bool result = false;
                        for(auto item : *list){
                            if(item.num1 == static_cast<int>(num1.data())
                            && item.num2 == static_cast<int>(num2.data())
                            && item.num3 == static_cast<int>(num3.data())
                            && item.num4 == static_cast<int>(num4.data())
                            && item.option1 == i1
                            && item.option2 == i2
                            && item.option3 == i3){
                                result = true;
                            }
                        }
                        if(!result){
                            struRecordNum tmpItem;
                            tmpItem.num1 =  static_cast<int>(num1.data());
                            tmpItem.num2 =  static_cast<int>(num2.data());
                            tmpItem.num3 =  static_cast<int>(num3.data());
                            tmpItem.num4 =  static_cast<int>(num4.data());
                            tmpItem.option1 =  i1;
                            tmpItem.option2 =  i2;
                            tmpItem.option3 =  i3;
                            list->append(tmpItem);
                             c++;

                             QString str  = "";
                             str +=  "((" ;
                             str +=  QString::number(num1.data());
                             str += strOption(i1);
                             str += QString::number(num2.data());
                             str += ")" ;
                             str += strOption(i2) ;
                             str +=  QString::number(num3.data()) ;
                             str += ")"  ;
                             str += strOption(i3) ;
                             str +=  QString::number(num4.data())+"\r\n";
                             if (!aFile.open(QIODevice::Append | QIODevice::Text))
                                    return false;
                              QTextStream stream(&aFile);
                              stream << str<<endl;
                             qInfo()<< str;
                              aFile.close();
                        }
                    }
                }
            }
        }

        return c;
}

LNum jisuan(LNum num1, LNum num2, int x)
{
        switch (x) {
        case 0:
            return num1+num2;
        case 1:
            return num1-num2 ;
        case 2:
            return num1*num2;
        case 3:
            return num1/num2 ;
        }
        return LNum(0);
}

QString strOption(int x){
    switch (x) {
        case 0:
        return "+";
    case 1:
        return "-";
    case 2:
        return "*";
    case 3:
        return "/";
    }
    return "";
}

QList<struNum> initList()
{
    QList<struNum> list;
    for (int i1 = 1;i1 <= MAXNUM; i1++) {
        for (int i2 = 1;i2 <= MAXNUM; i2++) {
            for (int i3 = 1;i3 <= MAXNUM; i3++) {
                for (int i4 = 1;i4 <= MAXNUM; i4++) {
                    struNum num(i1,i2,i3,i4);
                    if(!isInList(num,list)){
                        list.append(num);
                    }
                }
            }
        }
    }
    return list;
}

bool isInList(struNum num, QList<struNum> list)
{
    int numList[4] = {num.num1,num.num2,num.num3,num.num4};
    bool result = false;
    for (int i1 = 0 ; i1 < 4; i1 ++) {
        for (int i2 = 0 ; i2 < 4; i2 ++){
            if(i1 == i2) continue;
            for (int i3 = 0 ; i3 < 4; i3 ++){
                if(i2 == i3 || i1 == i3) continue;
                for (int i4 = 0 ; i4 < 4; i4 ++){
                    if(i1 == i4 || i2 == i4 || i3 == i4) continue;
                      foreach(auto item ,list){
                            if(item.num1 == numList[i1]
                                && item.num2 == numList[i2]
                                && item.num3 == numList[i3]
                                && item.num4 == numList[i4]){
                                result = true;
                            }

                      }
                }
            }
        }
    }
    return result;

}
