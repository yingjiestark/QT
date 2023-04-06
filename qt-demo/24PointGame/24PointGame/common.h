#ifndef COMMON_H
#define COMMON_H
#include "lnum.h"
#include "num_button.h"
typedef struct num_item_stu {
    LNum num = LNum(-1);
    int type = -1;  // 选中的按钮编号
    bool operator==(const num_item_stu &p)
    {
        return (this->num == p.num) && (this->type == p.type);
    }
    NumButton *btn;
} NumItem;

typedef struct option_item_stu {
    int option = -1;  // 操作符号 0:加，1：减，2：乘，3：除法
    int type = -1;    // 选中的按钮编号
} OptionItem;

typedef struct mode_item_stu {
    int id;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    int status;

} ModeItem;
#endif  // COMMON_H
