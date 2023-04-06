#ifndef _COMMON_H
#define _COMMON_H
#include <iostream>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
using namespace std;
#define HDD_MOUNT_DIR 		"yubo.wang"

// char转数字
int char_to_hex(char x);
// 16进制字符串转码
unsigned long  str_to_hex(string str);
// 获取程序基地址
unsigned long getBaseAddress(string name);

#endif