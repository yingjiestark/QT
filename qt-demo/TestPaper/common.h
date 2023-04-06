#ifndef COMMON_H
#define COMMON_H
#include <QList>

enum NUMOPTION{
    ADDOPTION,  // 加法运算符
    SUBOPTION,  // 减法运算符
    MULOPTION,
    DIVOPTION

};

typedef struct NUMRULE {
    int IntegerChance;   // 整数和分数概率0全为分数 100:全为整数
    int PositiveChance;  // 0:全为负数，100：全为正数
    int MoleculeRange;   // 分子范围 1 - X
    int DenominatorRange;  // 分母范围 1 - X
    int page;              // 生成的页码范围
    int Num;               // 每个等式等数字个数。
    QList<NUMOPTION> option;      // 随机的运算符，size不能等于0
    NUMRULE()
    {
        IntegerChance = 50;
        PositiveChance = 50;
        MoleculeRange = 10;
        DenominatorRange = 10;
        page = 1;
        Num = 2;
    }
} Numrule;

#endif  // COMMON_H
