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
 * ./imx6uirqlAPP <filename>
 * ./imx6uirqlAPP /dev/imx6uirq
 * 
*/

int main(int argc,char *argv[])
{
    int fd,ret;
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
        ret = read(fd,&data,sizeof(data)); /*读到data里面*/
        if (ret < 0) {

        } else {
            if (data) {
                printf("key value is %#x\r\n",data);
            }
        }
    }
    close(fd);
    return 0;
}