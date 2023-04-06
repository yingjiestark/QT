#include "tools.h"

Tools::Tools(QObject *parent)
    : QObject(parent)
{
}

LNum Tools::jisuan(LNum num1, LNum num2, int x)
{
    switch (x) {
        case 0:
            return num1 + num2;
        case 1:
            return num1 - num2;
        case 2:
            return num1 * num2;
        case 3:
            return num1 / num2;
    }
    return LNum(0);
}
