#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fcntl.h>

/*
 *argc:
 *argv[]:
 * ./asyncnotiAPP <filename>
 * ./asyncnotiAPP /dev/imx6uirq
 * 
*/

int fd;

static void sigio_signal_func(int num)
{
    int err;
    unsigned int keyvalue = 0;

    err = read(fd,&keyvalue,sizeof(keyvalue));

    if (err < 0) {

    } else {
        /*不加\r\n不会打印到终端，会在缓存区打印，但是这里我并没有发生不打印的情况，
        所以为了记录。要知道如果应用程序不打印，记得刷新缓存区*/
        printf("sigio signal! key value = %d",keyvalue);
        fflush(stdout);
    }
}


int main(int argc,char *argv[])
{
    int ret;
    char *filename;
    unsigned char data;
    int flags = 0;


    if(argc != 2) {
        printf("error usage\r\n");
    }

    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0) {
        printf("file %s open failed\r\n",filename);
        return -1;
    }

    /*设置信号处理函数*/
    signal(SIGIO,sigio_signal_func);

    fcntl(fd,F_SETOWN,getpid());   /*设置当前进程接收 SIGIO信号*/
    flags = fcntl(fd,F_GETFL);  /*获取当前文件标志*/
    fcntl(fd,F_SETFL,flags | FASYNC); /*设置文件标志 异步通知   */

    while(1) {
        sleep(2);
        printf("sleep\r\n");
    }

    close(fd);
    return 0;
}