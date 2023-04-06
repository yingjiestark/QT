#include "common.h"
int char_to_hex(char x){
    switch (x)
    {
    case '0':
        return 0;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
       return 12;
    case 'd':
    case 'D':
       return 13;
    case 'e':
    case 'E':
       return 14;
    case 'f':
    case 'F':
       return 15;
    default:
        return 0;
        break;
    }
    return 0;
}

unsigned long  str_to_hex(string str){
    unsigned long   result = 0;
    for(int i = str.length()-1   ; i>= 0 ;i--){
        unsigned long base = 1;
        if(str.at(i) == '0') continue;
        for(int j = 0 ; j < str.length()- 1 - i ; j++){
            base *= 16;
        }
        result += char_to_hex(str.at(i))*base;
    }
    return result;
 }
 // 获取程序基地址
unsigned long getBaseAddress(string name){
    
    string cmd = "cat /proc/" +  to_string(getpid()) + "/maps | grep " + name +" | head -n 1 | awk -F '-' '{print $1}'";
   // cout <<cmd<<endl;
    int res = -1;
    int ret = -1;
    FILE * fp;
    if ((fp = popen(cmd.c_str(), "r") ) == NULL)
	{
		printf("Popen Error!\n");
		return 0;
	}
    char pRetMsg[512] ={0};
    while(fgets(pRetMsg, 512, fp) != NULL){
       // printf("safdad:%p ,%s,%d \r\n",&pRetMsg,pRetMsg,getpid()); //print all info
       if(NULL != strstr(pRetMsg, HDD_MOUNT_DIR)){
            printf("got df info:\n");
            ret = 0;
            break;
        }
    }
    if ((res = pclose(fp)) == -1){
			printf("close popenerror!\n");
			return 0;
	}
    pRetMsg[strlen(pRetMsg)-1] = '\0';
  //  cout <<getpid()<<" : pRetMsg:"<< string(pRetMsg)<<endl;
    return str_to_hex(string(pRetMsg));
}