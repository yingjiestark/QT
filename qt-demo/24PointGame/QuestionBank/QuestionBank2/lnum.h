#ifndef LNUM_H
#define LNUM_H

class LNum
{

public:
    LNum(int Molecule);
    LNum(int Molecule,int Denominator);
    int getMolecule();                   // 获取分子
    int getDenominator();                // 获取分母
    void setMolecule(int molecule);      // 设置分子
    void setDenominator(int denominator);// 设置分母
    double data();
    LNum operator + ( LNum p1);
    LNum operator - ( LNum p1);
    LNum operator * ( LNum p1);
    LNum operator / ( LNum p1);
    bool operator ==( LNum p1) ;
private:
    // 分子
    int m_iMolecule = 1;
    // 分母
    int m_iDenominator = 1;
    void Equivalency();         // 约分

};

#endif // LNUM_H
