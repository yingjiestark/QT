#ifndef DATAFACTORY_H
#define DATAFACTORY_H

#include <QObject>
#include "numitem.h"
#include "common.h"

class DataFactory : public QObject {
    Q_OBJECT
   public:
    explicit DataFactory(QObject *parent = nullptr);
    // 初始化所以需要绘制的数据。
    QList<QList<NumItem>> initALLNumList(Numrule rule);
    // 初始化某一行的数据。
    QList<NumItem> initLineNumList(Numrule rule);

    QString RandomOption(QList<NUMOPTION> list);
private:
   Numrule m_rule;
   signals:

   public slots:
};

#endif  // DATAFACTORY_H
