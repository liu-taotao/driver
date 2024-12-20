#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <sys/utsname.h>
#define SERVER_PORT 8888 //端口号不能发生冲突,不常用的端口号通常大于 5000
// 在 recv 之后立即调用此函数
char* trim_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    return str;
}
void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    int ans = 0;
    char buffer[1024] = {0};
    
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ans = recv(client_socket, buffer, sizeof(buffer), 0);
        // 将读取到的数据以字符串形式打印出来   
        printf("from client: %s\n", buffer);
        trim_newline(buffer); // 去除换行符
        if (strcmp(buffer, "time") == 0) {
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            char *time_str = asctime(timeinfo);
            printf("send client: %s\n", time_str);
            send(client_socket, time_str, strlen(time_str), 0);
        } 
        else if (strcmp(buffer, "hostname") == 0) {
            struct utsname info;
            uname(&info);
            send(client_socket, info.nodename, strlen(info.nodename), 0);
        }
        // 如果读取到"exit"则关闭套接字退出程序
        if (0 == strncmp("exit", buffer, 4)) {
            printf("server exit...\n");
            printf("Client disconnected: %d\n", client_socket);
            send(client_socket, buffer, strlen(buffer), 0);
            //close(client_socket);
            break;
        }
        if (ans <= 0 ) {
            printf("Client disconnected: %d\n", client_socket);
            break; // 退出循环，结束线程
        }
    }
    
    close(client_socket);
    pthread_exit(NULL);
}
int main(void)
{
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    char ip_str[20] = {0};
    int sockfd, connfd;
    int addrlen = sizeof(client_addr);
    char recvbuf[512];
    int ret;
    /* 打开套接字，得到套接字描述符 */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sockfd) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    /* 将套接字与指定端口号进行绑定 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (0 > ret) {
        perror("bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    /* 使服务器进入监听状态 */
    ret = listen(sockfd, 50);
    if (0 > ret) {
        perror("listen error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    pthread_t tid;
    
    while (1) {
        connfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        printf("有客户端接入...\n");
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_str, sizeof(ip_str));
        printf("客户端主机的 IP 地址: %s\n", ip_str);
        printf("客户端进程的端口号: %d\n", client_addr.sin_port);
        pthread_create(&tid, NULL, handle_client, (void *)&connfd);
        pthread_detach(tid);
    }
    /* 关闭套接字 */
    close(sockfd);
    exit(EXIT_SUCCESS);
}