#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

void connect_to_server(int *sockfd, struct sockaddr_in *server_addr);
void get_current_time(int sockfd);
void get_machine_name(int sockfd);
void get_active_connections(int sockfd);
void send_message(int sockfd);
void disconnect(int sockfd);

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int choice;

    connect_to_server(&sockfd, &server_addr);

    while (1) {
        printf("\n1. 获取时间\n");
        printf("2. 获取机器名称\n");
        printf("3. 活动连接列表\n");
        printf("4. 发消息\n");
        printf("5. 退出\n");
        printf("选择功能: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: get_current_time(sockfd); break;
            case 2: get_machine_name(sockfd); break;
            case 3: get_active_connections(sockfd); break;
            case 4: send_message(sockfd); break;
            case 5: disconnect(sockfd); exit(0);
            default: printf("无效选择\n");
        }
    }

    return 0;
}

void connect_to_server(int *sockfd, struct sockaddr_in *server_addr) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr->sin_addr);
    connect(*sockfd, (struct sockaddr *)server_addr, sizeof(*server_addr));
}

void disconnect(int sockfd) {
    close(sockfd);
}

void get_current_time(int sockfd) {
    unsigned char request[2] = {0x03, 0}; // 0x03: 获取时间
    send(sockfd, request, sizeof(request), 0);
    
    char buffer[BUFFER_SIZE];
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("当前时间: %s\n", buffer);
}

void get_machine_name(int sockfd) {
    unsigned char request[2] = {0x04, 0}; // 0x04: 获取机器名称
    send(sockfd, request, sizeof(request), 0);

    char buffer[BUFFER_SIZE];
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("机器名称: %s\n", buffer);
}

void get_active_connections(int sockfd) {
    unsigned char request[2] = {0x05, 0}; // 0x05: 获取活动连接列表
    send(sockfd, request, sizeof(request), 0);

    char buffer[BUFFER_SIZE];
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("活动连接: %s\n", buffer);
}

void send_message(int sockfd) {
    int target_id;
    char message[BUFFER_SIZE];

    printf("输入目标客户端编号: ");
    scanf("%d", &target_id);
    printf("输入消息: ");
    getchar(); // consume newline
    fgets(message, sizeof(message), stdin);
    
    // 构建发送消息请求
    unsigned char request[BUFFER_SIZE];
    request[0] = 0x06; // 0x06: 发消息
    request[1] = target_id + '0'; // 目标编号
    strcpy((char *)(request + 2), message);
    
    send(sockfd, request, strlen(message) + 2, 0);
}