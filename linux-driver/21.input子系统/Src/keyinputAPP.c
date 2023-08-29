#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <linux/input.h>
/*
 *argc:
 *argv[]:
 * ./keyinputAPP <filename>
 * ./keyinputAPP /dev/input/event1
 * 
*/

/*input_event结构体变量*/
static struct input_event inputevent;


int main(int argc,char *argv[])
{
    int fd,err;
    char *filename;
    unsigned char data;

    if(argc != 2) {
        printf("error usage\r\n");
    }

    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0) {
        printf("file %s open failed\r\n",filename);
        return -1;
    }

    /*循环读取*/
    while(1) {
        err = read(fd,&inputevent,sizeof(inputevent));
        if (err > 0) {/*数据读取成功*/
            switch(inputevent.type) {/*type也就是刚刚在开发板上 hexdump 出现的type类型*/
                case EV_KEY:
                    printf("EV_KEY事件\r\n");
                    if (inputevent.code < BTN_MISC) {   /*KEY*/
                        printf("key %d %s\r\n",inputevent.code,inputevent.value?"press":"release");
                    } else {    /*BIN*/
                        printf("button %d %s\r\n",inputevent.code,inputevent.value?"press":"release");
                    }
                    break;
                case EV_SYN:
                    printf("EV_SYN事件\r\n");
                    break;
                case EV_REL:
                    printf("EV_REL事件\r\n");
                    break;
                case EV_ABS:
                    printf("EV_ABS事件\r\n");
                    break;
                default:
                    break;

            }
        } else {
            printf("读取数据失败\r\n");
        }
    }

    close(fd);
    return 0;
}