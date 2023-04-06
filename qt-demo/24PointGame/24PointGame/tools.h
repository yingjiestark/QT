#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include "lnum.h"
class Tools : public QObject {
    Q_OBJECT
   public:
    explicit Tools(QObject *parent = nullptr);
    static LNum jisuan(LNum num1, LNum num2, int x);

   signals:

   public slots:
};

#endif  // TOOLS_H
