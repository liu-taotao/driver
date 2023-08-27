#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 *argc:
 *argv[]:
 * ./keyledAPP <filename> <0:1>
 * ./keyledAPP /dev/key
 * 
*/
/*按键的状态 有效 无效*/
#define KEY0VALUE       0xf0
#define INVAKEY         0X00

int main(int argc,char *argv[])
{
        int value;
        int fd,ret;
        char *filename;
        unsigned int databuf[1];

        if(argc != 2) {
                printf("error usage!\r\n");
        }

        filename = argv[1];
        fd = open(filename,O_RDWR);
        if (fd < 0) {
                printf("file %s open failed\r\n",filename);
                return -1;
        }

        /*循环读取*/
        while(1) {
                read(fd,&value,sizeof(value));
                if (value == KEY0VALUE) {
                        printf("KEY0 Press, value = %d\r\n",value);
                }
        }

        close(fd);
        return 0;

}