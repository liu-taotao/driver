#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
/*
 *argc:
 *argv[]:
 * ./timeioctlAPP <filename>
 * ./timeioctlAPP /dev/timer
 * 
*/
#define CLOSE_CMD       _IO(0xEF,1)             //关闭命令
#define OPEN_CMD        _IO(0xEF,2)             //打开命令
#define SETPERIOD_CMD   _IOW(0xEF,3,int)        //设置周期

int main(int argc,char *argv[])
{
    int fd,ret;
    char *filename;
    unsigned char databuf[1];
    unsigned int cmd;
    unsigned int arg;
    unsigned char str[100];
    if(argc != 2) {
        printf("error usage\r\n");
    }

    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0) {
        printf("file %s open failed\r\n",filename);
        return -1;
    }

    while(1) {
        printf("liut input CMD:");
        ret = scanf("%d",&cmd);
        if (ret != 1) {
            gets(str);  /*防止输入卡死*/
        }

        if (cmd == 1) {     /*关闭定时器*/
            ioctl(fd,CLOSE_CMD,&arg);
        } else if (cmd == 2) {  /*打开定时器*/
            ioctl(fd,OPEN_CMD,&arg);
        } else if (cmd == 3) {  /*设置周期*/
            printf("input timer period:");
            ret = scanf("%d",&arg);
            if (ret != 1) {
                gets(str);
            }
            ioctl(fd,SETPERIOD_CMD,&arg);
        } else {
            break;
        }
    }
    close(fd);
    return 0;
}