#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>
// 替换getpid函数
int mygetpid(){
    return 520;
}

int main(){
    while(true){
        printf("the pid is %d\n",getpid());
        sleep(1);
    }
    return 0;
}