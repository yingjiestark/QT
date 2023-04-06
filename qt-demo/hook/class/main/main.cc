#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>
#include "TestClass.h"
void showText(){
	
	printf("this is main function!\r\n");
}

int main(){
	MathManager m;
	 while(true){
		 
        int num =	m.add(5,6);
		printf("num:%d\r\n",num);
        sleep(1);
    }
	return 0;
}