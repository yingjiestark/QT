#include "numitem.h"
#include <qrandom.h>
#include <QTime>
#include <QRandomGenerator>
NumItem::NumItem(Numrule rule)
    : m_bSymbol(POSITIVENUMBER)
    , m_iMolecule(1)
    , m_iDenominator(1)
    , m_numType(INTEGER)
{
    init(rule);
}

void NumItem::init(Numrule rule)
{
    // 1. 随机符号
    m_bSymbol = initSymbol(rule.PositiveChance);
    // 2. 随机整数或者分数。
    m_numType = initNumType(rule.IntegerChance);
    // 3. 随机数值
    m_iMolecule = initMolecule(rule.MoleculeRange);

    m_iDenominator = initMolecule(rule.DenominatorRange);
    // 整理 1. 约分
    Equivalency();
    // 整理 2. 分母为1 那么为整数
    if (m_iDenominator == 1) {
        m_numType = INTEGER;
    }
}
void NumItem::Equivalency()
{
    int num = m_iMolecule > m_iDenominator ? m_iMolecule : m_iDenominator;
    for (int i = 2; i <= num; i++) {
        if (m_iDenominator % i == 0 && m_iMolecule % i == 0) {
            m_iDenominator = m_iDenominator / i;
            m_iMolecule = m_iMolecule / i;
            num = m_iMolecule > m_iDenominator ? m_iMolecule : m_iDenominator;
            i = 1;
        }
    }
}

NumItem::SymbolType NumItem::initSymbol(int rule)
{
    int random = QRandomGenerator::global()->bounded(100);
    // 概率为0表示全为负数
    if (0 == rule) {
        return NEGATIVENUMBER;
    } else if (100 == rule) {  // 概率为100表示全为正数。
        return POSITIVENUMBER;
    } else if (random < rule) {
        return POSITIVENUMBER;
    } else {
        return NEGATIVENUMBER;
    }
}

NumItem::NumType NumItem::initNumType(int change)
{
    int random = QRandomGenerator::global()->bounded(100);
    if (0 == random) {
        return INTEGER;
    } else if (100 == random) {
        return FRACTION;
    } else if (random < change) {
        return INTEGER;
    } else {
        return FRACTION;
    }
}

int NumItem::initMolecule(int rule)
{
    return QRandomGenerator::global()->bounded(100) % (rule - 1) + 1;
}

int NumItem::initDenominator(int rule)
{
    return QRandomGenerator::global()->bounded(100) % (rule - 1) + 1;
}

NumItem::SymbolType NumItem::getSymbol() { return m_bSymbol; }

NumItem::NumType NumItem::getNumType() { return m_numType; }

int NumItem::getMolecule() { return m_iMolecule; }

int NumItem::getDenominator() { return m_iDenominator; }
