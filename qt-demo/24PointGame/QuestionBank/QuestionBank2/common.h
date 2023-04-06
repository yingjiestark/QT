#ifndef COMMON_H
#define COMMON_H

#include "lnum.h"

#include <QString>
#define MAXNUM 10
typedef  struct SNUM{
    SNUM(int num1,int num2,int num3,int num4){
        this->num1 = num1;
        this->num2 = num2;
        this->num3 = num3;
        this->num4 = num4;
    }
    int num1 =0;
    int num2 =0;
    int num3 =0;
    int num4 =0;
    int c = 0;  // 四个数能够计算24算法。
}struNum;


typedef  struct RNUM{

    int num1 = -1;
    int num2= -1;
    int num3= -1;
    int num4= -1;
    int option1= -1;
    int option2= -1;
    int option3= -1;
}struRecordNum;

/**
 * @brief is24OK 该数字是否可以计算24
 * @param num1
 * @param num2
 * @param num3
 * @param num4
 * @return 返回4个数计算24的算法种类
 */
int is24OK(LNum num1, LNum num2,LNum num3,LNum num4);
/**
 * @brief suanfatongji 统计4个数能够计算出24点的算法
 * @param num1
 * @param num2
 * @param num3
 * @param num4
 * @return 0:不能计算，N>0：N种，
 */
int suanfatongji(LNum num1, LNum num2,LNum num3,LNum num4 ,QList<struRecordNum> *list);

/**
 * @brief jisuan 根据 操作计算两个数的结果
 * @param num1
 * @param num2
 * @param x 标识运算符。
 * @return
 */
LNum jisuan(LNum num1,LNum num2,int x);
/**
 * @brief strOption
 * @param x 标识运算符。0:加法，1:减法，2:乘法，3除法
 * @return
 */
QString strOption(int x);



/**
 * @brief initList 初始化不重复的4个数字的组合类型
 * 可以转化为：一个袋子里面有1-10号求，从袋子去除一个球放回，拿到组合有多少种。
 * 分析：
 * 一、四个数都相等情况
 * 10
 * 二、三个数相等情况
 * 10*9 = 90
 * 三、两个数相等另外两个数不相等情况
 * 10*9*8/2 = 360
 * 四、两个数相等另外两个数也相等情况
 * 10 * 9 /2 = 45
 * 五、四个数都不想等的情况C(10,4)
 * 10*9* 8* 7 / (4*3*2*1) = 210
 * 总数
 * 
 * @return
 */
QList<struNum>  initList();
/**
 * @brief isInList
 * @param num
 * @param list
 * @return
 */
bool isInList(struNum num,QList<struNum> list);

#endif // COMMON_H
