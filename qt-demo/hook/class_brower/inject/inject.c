
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
 
 
#define JMP_OFFSET_LEN  5   //JMP指令的长度

void install_stub2(unsigned long src_func,unsigned long dst_func)
{
    int pagesize = sysconf(_SC_PAGESIZE);                                          // 系统页大小
    unsigned long srcpage = (unsigned long)((unsigned long)src_func & 0xFFFFF000); // 计算原函数地址所在的页 的首地址
    mprotect((void*)srcpage, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);        // 使用mprotect函数使该页的内存可读可写可执行
    unsigned char jmpcmd[14] = {0};                                                // JMP远跳只支持32位程序 64位程序地址占8个字节 寻址有问题
    jmpcmd[0] = 0xFF;                                                              // 当JMP指令为 FF 25 00 00 00 00时，会取下面的8个字节作为跳转地址
    jmpcmd[1] = 0x25;                                                              // 因此可以使用14个字节作为指令 (FF 25 00 00 00 00) + dstaddr
    jmpcmd[2] = 0x00;                                                              
    jmpcmd[3] = 0x00;
    jmpcmd[4] = 0x00;
    jmpcmd[5] = 0x00;
    unsigned long dstaddr = (unsigned long)dst_func;
    memcpy(&jmpcmd[6], &dstaddr, sizeof(dstaddr));                                 
    memcpy(src_func, jmpcmd, sizeof(jmpcmd));   
}

int main(int argc,char* argv[]) {
    int pid = atoi(argv[1]);
    unsigned long offset = 0x4011b2;
    unsigned long myfunctionaddr = 0x4011dc;
	//install_stub2(offset,myfunctionaddr);
    char filename[32];
    snprintf(filename, sizeof(filename),"/proc/%d/mem",pid);
    int fd = open(filename, O_RDWR|O_SYNC);
    lseek(fd,offset,SEEK_SET);

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
}