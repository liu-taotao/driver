#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
    int ret = 0;
    int fd;
    char *filename;

    char readbuf[100],writebuf[100];
    static char usrdata[] = {"usr data"};
    if(argc != 3) {
    printf("error usag!\r\n");
    return -1;
    }

    filename = argv[1];
    /*open*/
    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("can't open file %s\r\n",filename);
        return -1;
    }
    else {
        printf("open is ok\r\n");
    }

    /*read value is 1*/
    if (atoi(argv[2]) == 1){
        /*read*/
        ret = read(fd,readbuf,50);
        if(ret < 0){
            printf("read file %s failed\r\n",filename);
        
        } 
        else {
            printf("read is ok\r\n");
            printf("APP read data:%s\r\n",readbuf);
        }
    }

    /*write value is 2*/
    if(atoi(argv[2]) == 2) {
        memcpy(writebuf,usrdata,sizeof(usrdata));
        /*write*/
        ret = write(fd,writebuf,50);
        if(ret < 0) {
            printf("write file %s faild\r\n",filename);
        } 
        else {
            printf("write is ok\r\n");
        }
    }

    /*close*/
    ret = close(fd);
    if (ret < 0) {
        printf("close file %s faild\r\n",filename);
    }
    else {
        printf("close is ok\r\n");
    }

    return 0;
}