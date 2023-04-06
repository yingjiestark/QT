#include "lnum.h"

LNum::LNum(int num)
    : m_iMolecule(num)
    , m_iDenominator(1)
{
}

LNum::LNum(int Molecule, int Denominator)
    : m_iMolecule(Molecule)
    , m_iDenominator(Denominator)
{
}

int LNum::getMolecule()
{
    Equivalency();
    return m_iMolecule;
}

int LNum::getDenominator()
{
    Equivalency();
    return m_iDenominator;
}

void LNum::setMolecule(int molecule) { m_iMolecule = molecule; }

void LNum::setDenominator(int denominator) { m_iDenominator = denominator; }

double LNum::data()
{
    Equivalency();
    if (m_iDenominator == 1) {
        return m_iMolecule;
    }
    return double(m_iMolecule) / double(m_iDenominator);
}

void LNum::Equivalency()
{
    int num = m_iMolecule > m_iDenominator ? m_iDenominator : m_iMolecule;

    for (int i = 2; i <= num; i++) {
        if (m_iDenominator % i == 0 && m_iMolecule % i == 0) {
            m_iDenominator = m_iDenominator / i;
            m_iMolecule = m_iMolecule / i;
            num = m_iMolecule > m_iDenominator ? m_iDenominator : m_iMolecule;
        }
    }
}

LNum LNum::operator+(LNum p1)
{
    LNum res(getMolecule(), getDenominator());
    res.setMolecule(getMolecule() * p1.getDenominator() +
                    getDenominator() * p1.getMolecule());
    res.setDenominator(getDenominator() * p1.getDenominator());
    res.Equivalency();
    return res;
}

LNum LNum::operator-(LNum p1)
{
    LNum res(getMolecule(), getDenominator());
    res.setMolecule(getMolecule() * p1.getDenominator() -
                    getDenominator() * p1.getMolecule());
    res.setDenominator(getDenominator() * p1.getDenominator());
    res.Equivalency();
    return res;
}

LNum LNum::operator*(LNum p1)
{
    LNum res(getMolecule(), getDenominator());
    res.setMolecule(getMolecule() * p1.getMolecule());
    res.setDenominator(getDenominator() * p1.getDenominator());
    res.Equivalency();
    return res;
}

LNum LNum::operator/(LNum p1)
{
    LNum res(getMolecule(), getDenominator());
    res.setMolecule(getMolecule() * p1.getDenominator());
    res.setDenominator(getDenominator() * p1.getMolecule());
    res.Equivalency();
    return res;
}

bool LNum::operator==(LNum p1)
{
    Equivalency();
    p1.Equivalency();
    if (getMolecule() == p1.getMolecule() &&
        getDenominator() == p1.getDenominator()) {
        return true;
    } else {
        return false;
    }
}
