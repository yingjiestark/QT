#include "TestClass.h"
#include <stdio.h>
MathManager::MathManager(){


}

int MathManager::add(int num1,int num2){

    int numa = num1 ++;
    int numb = num2 ++;
    printf("num1:%d,num2:%d\r\n",num1,num2);
    return numa+numb;
}