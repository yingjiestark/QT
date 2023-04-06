#include <stdio.h>
int getpid(void){
        printf("i hook the getpid function!\n");
        return 12306;
}