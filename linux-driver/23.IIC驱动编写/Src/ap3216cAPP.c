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
 * ./ap3216cAPP <filename>
 * ./ap3216cAPP /dev/ap3216c
 * 
*/

int main(int argc,char *argv[])
{
    int fd,err;
    unsigned short data[3];
    unsigned short ir,ps,als;
    char *filename;


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
        err = read(fd,data,sizeof(data));/*数组不取指*/
        if (err == 0) {
            ir = data[0];
            als= data[1];
            ps = data[2];
        }
        printf("ap3216c ir = %d,als = %d,ps = %d\r\n",ir,als,ps);
        usleep(200000);/*200ms*/
    }
    


    close(fd);
    return 0;
}