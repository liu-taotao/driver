#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>

#define SERVER_PORT 8888 //服务器的端口号
#define SERVER_IP "192.168.1.25" //服务器的 IP 地址

typedef struct {
    int sockfd;
    bool connected;
} ClientState;

typedef struct {
    char data[512];
} Message;

ClientState clientState;
pthread_mutex_t lock;
pthread_cond_t cond;
Message messageQueue[10];
int queueHead = 0;
int queueTail = 0;
int queueCount = 0;

void* receiveThread(void* arg) {
    int sockfd = clientState.sockfd;
    char buf[512];
    while (clientState.connected) {
        int ret = recv(sockfd, buf, sizeof(buf), 0);
        if (ret <= 0) {
            break;
        }
        pthread_mutex_lock(&lock);
        if (queueCount < 10) {
            strcpy(messageQueue[queueTail].data, buf);
            queueTail = (queueTail + 1) % 10;
            queueCount++;
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&lock);
        memset(buf, 0x0, sizeof(buf));
    }
    clientState.connected = false;
    pthread_exit(NULL);
}

void processMessages() {
    pthread_mutex_lock(&lock);
    while (queueCount > 0) {
        printf("Server response: %s\n", messageQueue[queueHead].data);
        queueHead = (queueHead + 1) % 10;
        queueCount--;
    }
    pthread_mutex_unlock(&lock);
}

void connectToServer() {
    struct sockaddr_in server_addr = {0};
    int ans;
    char tem2[512];
    printf("请输入端口号：");
    scanf("%d", &ans);
    printf("请输入IP地址：");
    scanf("%s", tem2);
    getchar();
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ans);
    inet_pton(AF_INET, tem2, &server_addr.sin_addr);
    int ret = connect(clientState.sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (0 > ret) {
        perror("connect error");
        return;
    }
    clientState.connected = true;
    printf("服务器连接成功...\n");
    pthread_t thread;
    pthread_create(&thread, NULL, receiveThread, NULL);
}

void disconnectFromServer() {
    if (clientState.connected) {
        close(clientState.sockfd);
        clientState.connected = false;
        printf("服务器已断开连接...\n");
    }
}

void sendMessage(const char* message) {
    if (clientState.connected) {
        int ret = send(clientState.sockfd, message, strlen(message), 0);
        if (0 > ret) {
            perror("send error");
        }
    }
}

void menu() {
    int choice;
    while (1) {
        printf("1. 连接\n");
        printf("2. 断开\n");
        printf("-----------------\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                connectToServer();
                break;
            case 2:
                disconnectFromServer();
                exit(EXIT_SUCCESS);
            default:
                printf("无效的选择，请重试。\n");
        }
        break;
    }
    while (1) {
        printf("1. 连接\n");
        printf("2. 断开\n");
        printf("3. 获取时间\n");
        printf("4. 获取名字\n");
        printf("5. 获取客户端列表\n");
        printf("6. 发送消息\n");
        printf("7. 退出\n");
        printf("-----------------\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                connectToServer();
                break;
            case 2:
                disconnectFromServer();
                break;
            case 3:
                sendMessage("time");
                break;
            case 4:
                sendMessage("name");
                break;
            case 5:
                sendMessage("list");
                break;
            case 6:
                if (clientState.connected) {
                    int clientNumber;
                    char message[512];
                    printf("请输入客户端编号: ");
                    scanf("%d", &clientNumber);
                    getchar();
                    printf("请输入消息内容: ");
                    fgets(message, sizeof(message), stdin);
                    char request[512];
                    snprintf(request, sizeof(request), "message %d %s", clientNumber, message);
                    sendMessage(request);
                } else {
                    printf("未连接到服务器。\n");
                }
                break;
            case 7:
                disconnectFromServer();
                exit(EXIT_SUCCESS);
            default:
                printf("无效的选择，请重试。\n");
        }
        sleep(1);
        processMessages();
    }
}

int main(void) {
    clientState.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > clientState.sockfd) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    menu();
    close(clientState.sockfd);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    exit(EXIT_SUCCESS);
}