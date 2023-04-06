#include "TestClass.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdbool.h>
using namespace std;


void testPrint(){
	int a= 0;
	a++;
	 printf("the test:%d \n",a);
	
}
void testPrint2(){
	int b= 0;
	b--;
	 printf("the test:%d \n",b);
	
}
int (*f)(int ,int);
int main(){
    
    f = (int(*)(int,int))dlsym(RTLD_NEXT,"_ZN9TestClassC1Ev");
    if(f ==nullptr){
        printf("f is null\r\n");
    }
 //   int a = (*f)(5,6);
    
    printf("%p\r\n",*&f);
    TestClass t;
    printf("the pid is %d\n",getpid());
    while (true)
    {
 	 testPrint();
        int ac = t.add(1,2);
        cout <<"ac:" <<ac<<endl;
        sleep(1);               
    }
    

    return 0;  
}