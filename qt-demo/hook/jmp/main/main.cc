#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>

void showText(){
	
	printf("this is main function!\r\n");
}

int main(){
	 while(true){
        	showText();
        sleep(1);
    }
	return 0;
}