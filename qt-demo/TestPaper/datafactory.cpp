#include "datafactory.h"
#include <QRandomGenerator>
DataFactory::DataFactory(QObject *parent)
    : QObject(parent)
{
}
QList<QList<NumItem>> DataFactory::initALLNumList(Numrule rule)
{
    m_rule = rule;
    QList<QList<NumItem>> list;
    for (int i = 0; i < 15; i++) {
        QList<NumItem> lineList = initLineNumList(rule);
        list.append(lineList);
    }
    return list;
}

QList<NumItem> DataFactory::initLineNumList(Numrule rule)
{

    QList<NumItem> list;
    int num = 2;
    if(rule.Num > 2){
        num  = QRandomGenerator::global()->bounded(rule.Num - 2) + 2;
    }

    for (int i = 0; i <= num; i++) {
        NumItem numItem(rule);
        list.append(numItem);
    }
    return list;
}

QString DataFactory::RandomOption(QList<NUMOPTION> list)
{
    int size = list.size();
   int idnex= QRandomGenerator::global()->bounded(size);
   NUMOPTION option = m_rule.option.at(idnex);
   switch(option){
       case ADDOPTION: return "+";
        case SUBOPTION: return "-";
        case MULOPTION: return "*";
        case DIVOPTION: return "÷";
       default:
           return "*";
   }
}
