#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
 
 
#define JMP_OFFSET_LEN  5   //JMP指令的长度
void showDialog(){
 	printf("leiyuanxiang i hook the getpid f\n");
}

int getpid1(){
	

	unsigned long startFun = 0x4011b2;
//mprotect
	unsigned long myfunctionaddr = (unsigned long)&showDialog;
 	char filename[32];
    snprintf(filename, sizeof(filename),"/proc/%d/mem",getpid());
	 int fd = open(filename, O_RDWR|O_SYNC);
 	lseek(fd,startFun,SEEK_SET);

	unsigned char jmpcmd[14] = {0};                                                // JMP远跳只支持32位程序 64位程序地址占8个字节 寻址有问题
	    jmpcmd[0] = 0xFF;                                                              // 当JMP指令为 FF 25 00 00 00 00时，会取下面的8个字节作为跳转地址
	    jmpcmd[1] = 0x25;                                                              // 因此可以使用14个字节作为指令 (FF 25 00 00 00 00) + dstaddr
	    jmpcmd[2] = 0x00;                                                              
	    jmpcmd[3] = 0x00;
	    jmpcmd[4] = 0x00;
	    jmpcmd[5] = 0x00;
	    unsigned long dstaddr = (unsigned long)myfunctionaddr;
	memcpy(&jmpcmd[6], &dstaddr, sizeof(dstaddr));  
   write(fd,&jmpcmd, sizeof(jmpcmd));
  	return 0;
};
int a =  getpid1();
