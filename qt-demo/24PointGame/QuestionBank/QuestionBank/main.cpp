#include <QCoreApplication>
#include <QtDebug>
#define MAXNUM 10
/**
 * @brief jisuan 计算两个数的运算结果
 * @param num1
 * @param num2
 * @param x     操作符号，0:+，1:-,2:*,3:/
 * @return
 */
double jisuan(double num1,double num2,int x);
int jisuan24(int num1,int num2,int num3 ,int num4);
/**
 * @brief is24OK 是否可以计算24
 * @param num1
 * @param num2
 * @param num3
 * @param num4
 * @return
 */
bool is24OK(int num1 , int num2,int num3,int num4){

    int numList[4] = {num1,num2,num3,num4};
    int c =0;
    if(num1 == num2 && num2 == num3 && num3 == num4){
        int x=jisuan24(num1,num2,num3,num3);
        if(x == 0){
            return false;
        }
        else {
            return  true;
        }
    }
    bool result = false;
    for (int i1 = 0 ; i1 < 4; i1 ++) {
        for (int i2 = 0 ; i2 < 4; i2 ++){
            if(i1 == i2) continue;
            for (int i3 = 0 ; i3 < 4; i3 ++){
                if(i2 == i3 || i1 == i3) continue;
                for (int i4 = 0 ; i4 < 4; i4 ++){
                    if(i1 == i4 || i2 == i4 || i3 == i4) continue;
                    //  qInfo()<<numList[i1]<<" "<<numList[i2] <<" "<< numList[i3] <<" "<<" "<< numList[i4];
                      int x=jisuan24(numList[i1],numList[i2],numList[i3],numList[i4]);
                      if(x !=0){
                          qInfo()<<"x:"<<x;
                            result = true;
                      }
                }
            }
        }
    }
    return result;
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
}

int jisuan24(int num1,int num2,int num3 ,int num4){

    double sum = 0;
    int c= 0;
    for(int i1 = 0 ; i1 < 4; i1 ++){
        for(int i2 = 0 ; i2 < 4; i2 ++ ){
            for(int i3 = 0 ; i3 < 4; i3 ++){
                sum = jisuan(jisuan(jisuan (num1,num2,i1),num3,i2),num4,i3) ;
                if(24.0  == sum){
                      qInfo()<< "(( "<< num1 <<strOption(i1) << num2 <<")"<<strOption(i2)<< num3<<")" <<strOption(i3)<< num4;
                      c++;

                }
            }
        }
    }

    return c;
}

double jisuan(double num1,double num2,int x){
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
    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


//    int c = jisuan24(4,4,2,8);
//    qInfo()<<c;
//    return 0;
//    is24OK(4,5,6,7);

   // return 0;
    for (int i1 = 1;i1 <= MAXNUM; i1++) {
        for (int i2 = 1;i2 <= MAXNUM; i2++) {
            for (int i3 = 1;i3 <= MAXNUM; i3++) {
                for (int i4 = 1;i4 <= MAXNUM; i4++) {
                    if(is24OK(i1,i2,i3,i4)){
                            qInfo()<<i1<<" "<<" "<<i2 <<" "<< i3 <<" "<<" "<< i4;
                    }
                }
            }
        }
    }

    return a.exec();
}
