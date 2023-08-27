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
 * ./gpioledAPP <filename> <0:1>
 * ./gpioledAPP /dev/led 0
 * ./gpioledAPP /dev/led 1
 * 
*/

int main(int argc,char *argv[])
{
        int fd,ret;
        char *filename;
        unsigned int databuf[1];

        if(argc != 3) {
                printf("error usage!\r\n");
        }

        filename = argv[1];
        fd = open(filename,O_RDWR);
        if (fd < 0) {
                printf("file %s open failed\r\n",filename);
                return -1;
        }

        databuf[0] = atoi(argv[2]); /*由字符串转为数字*/
        ret = write(fd,databuf,sizeof(databuf));
        if (ret < 0) {
                printf("LED control failed\r\n");
                close(fd);
                return -1;
        }

        close(fd);
        return 0;

}