#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char* argv[]) {
    int pid = atoi(argv[1]);
    unsigned long offset = 0x404028;
    unsigned long myfunctionaddr = 0x401142;
    char filename[32];
    snprintf(filename, sizeof(filename),"/proc/%d/mem",pid);
    int fd = open(filename, O_RDWR|O_SYNC);
    lseek(fd,offset,SEEK_SET);
    write(fd,&myfunctionaddr, sizeof(unsigned long));
    return 0;
}