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
 * ./ledAPP <filename> <0:1>
 * ./ledAPP /dev/led 0
 * ./ledAPP /dev/led 1
 * 
*/
#define LEDOFF 0
#define LED0N  1
int main(int argc,char *argv[])
{
    int fd,ret;
    char *filename;
    unsigned char databuf[1];

    if(argc != 3) {
        printf("error usage\r\n");
    }

    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0) {
        printf("file %s open failed\r\n",filename);
        return -1;
    }
    databuf[0] = atoi(argv[2]);/*become number*/
    ret = write(fd,databuf,sizeof(databuf));
    if(ret < 0) {
        printf("LED control failed\r\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}