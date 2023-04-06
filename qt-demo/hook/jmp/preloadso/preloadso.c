#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "common.h"
void showHook(){
    printf("this is  hook function!\n");
}


int hookFunction(){
	
	char strProcessPath[1024] = {0};
	if(readlink("/proc/self/exe", strProcessPath,1023) <=0){
			return -1;
	}
	char *strProcessName = strrchr(strProcessPath, '/');
	if(strcmp(strProcessName,"/main")){return 0;}
	unsigned long baseAddress = getBaseAddress("main");

	unsigned long offset =0x401132-0x400000;
	// 打开浏览器证书弹窗的地址为 基地址+偏移量。
	unsigned long ShowFunAddress = baseAddress + offset;
	printf(" baseAddress:%llu, ShowFunAddress:%llu \r\n",baseAddress,ShowFunAddress);
	// 获取将要注入的函数地址。
	unsigned long myfunctionaddr = (unsigned long)&showHook;
	printf(" baseAddress:%llu, ShowFunAddress:%llu ,myfunctionaddr:%llu \r\n",baseAddress,ShowFunAddress,myfunctionaddr);
	// 打开程序内存。
	char filename[32];
    snprintf(filename, sizeof(filename),"/proc/%d/mem",getpid());
	int fd = 0;
	if((fd = open(filename, O_RDWR|O_SYNC)) ==-1)
	{
		return -1;
	}
	// 打开指定函数偏移的位置。
 	lseek(fd,ShowFunAddress,SEEK_SET);
	// 开始注入代码
	// 伪造jmp指令
	unsigned char jmpcmd[14] = {0};               // JMP远跳只支持32位程序 64位程序地址占8个字节 寻址有问题
	    jmpcmd[0] = 0xFF;                         // 当JMP指令为 FF 25 00 00 00 00时，会取下面的8个字节作为跳转地址
	    jmpcmd[1] = 0x25;                         // 因此可以使用14个字节作为指令 (FF 25 00 00 00 00) + dstaddr
	    jmpcmd[2] = 0x00;                                                              
	    jmpcmd[3] = 0x00;
	    jmpcmd[4] = 0x00;
	    jmpcmd[5] = 0x00;
	    unsigned long dstaddr = (unsigned long)myfunctionaddr;
	memcpy(&jmpcmd[6], &dstaddr, sizeof(dstaddr));  
	// 注入代码
	write(fd,&jmpcmd, sizeof(jmpcmd));
	int res = -1;
	 if ((res = close(fd)) == -1){
			printf("close popenerror!\n");
			return 0;
	}
  	return 0;
}


int  a=hookFunction();