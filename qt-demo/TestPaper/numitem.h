#ifndef NUMITEM_H
#define NUMITEM_H
#include "common.h"
class NumItem {
   public:
    enum NumType {
        INTEGER = 0,  // 整数
        FRACTION      // 分数
    };
    enum SymbolType {
        POSITIVENUMBER = 0,  // 正数
        NEGATIVENUMBER       // 负数
    };

   private:
    // 存储数字的符号
    SymbolType m_bSymbol;
    // 分子
    int m_iMolecule;
    // 分母。
    int m_iDenominator;
    // 数字类型整数还是分数
    NumType m_numType;

    // 根据规，则初始化数字类
    void init(Numrule rule);

    // 初始化正负符号
    SymbolType initSymbol(int random);
    // 初始化整数分数
    NumType initNumType(int change);
    // 初始化分母，最大值max
    int initMolecule(int max);
    // 初始化分母，最大值max
    int initDenominator(int max);

    void Equivalency();

   public:
    NumItem(Numrule rule);
    SymbolType getSymbol();
    NumType getNumType();
    // 获取分子数据
    int getMolecule();
    // 获取分母数据
    int getDenominator();
};

#endif  // NUMITEM_H
