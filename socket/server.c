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
#include <time.h>

#define PORT 8888 // 使用学号的后4位作为服务器的监听端口

typedef struct {
    int sockfd;
    struct sockaddr_in addr;
    bool connected;
} Client;

Client clients[10];
int clientCount = 0;
pthread_mutex_t lock;

void* handleClient(void* arg) {
    int clientSockfd = *(int*)arg;
    free(arg);
    char buffer[512];
    while (true) {
        int ret = recv(clientSockfd, buffer, sizeof(buffer), 0);
        if (ret <= 0) {
            break;
        }
        buffer[ret] = '\0';
        printf("Received request: %s\n", buffer);
        if (strcmp(buffer, "time") == 0) {
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            char response[512];
            snprintf(response, sizeof(response), "Current time: %s", asctime(timeinfo));
            send(clientSockfd, response, strlen(response), 0);
        } else if (strcmp(buffer, "name") == 0) {
            send(clientSockfd, "Server Name: MyServer", 19, 0);
        } else if (strcmp(buffer, "list") == 0) {
            char response[512] = "Client List:\n";
            pthread_mutex_lock(&lock);
            for (int i = 0; i < clientCount; i++) {
                if (clients[i].connected) {
                    char clientInfo[128];
                    snprintf(clientInfo, sizeof(clientInfo), "Client %d: %s:%d\n", i, inet_ntoa(clients[i].addr.sin_addr), ntohs(clients[i].addr.sin_port));
                    strcat(response, clientInfo);
                }
            }
            pthread_mutex_unlock(&lock);
            send(clientSockfd, response, strlen(response), 0);
        } else if (strncmp(buffer, "message ", 8) == 0) {
            int clientNumber;
            char message[512];
            sscanf(buffer, "message %d %[^\n]", &clientNumber, message);
            pthread_mutex_lock(&lock);
            if (clientNumber >= 0 && clientNumber < clientCount && clients[clientNumber].connected) {
                char response[512];
                snprintf(response, sizeof(response), "Message from client: %s", message);
                send(clients[clientNumber].sockfd, response, strlen(response), 0);
                snprintf(response, sizeof(response), "Message sent successfully");
                send(clientSockfd, response, strlen(response), 0);
            } else {
                send(clientSockfd, "Client not found", 16, 0);
            }
            pthread_mutex_unlock(&lock);
        } else {
            send(clientSockfd, "Unknown command", 17, 0);
        }
        memset(buffer, 0x0, sizeof(buffer));
    }
    close(clientSockfd);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].sockfd == clientSockfd) {
            clients[i].connected = false;
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main(void) {
    int serverSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > serverSockfd) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (0 > bind(serverSockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
        perror("bind error");
        close(serverSockfd);
        exit(EXIT_FAILURE);
    }
    if (0 > listen(serverSockfd, 10)) {
        perror("listen error");
        close(serverSockfd);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(&lock, NULL);
    printf("Server listening on port %d...\n", PORT);
    while (true) {
        struct sockaddr_in clientAddr = {0};
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSockfd = accept(serverSockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (0 > clientSockfd) {
            perror("accept error");
            continue;
        }
        pthread_mutex_lock(&lock);
        if (clientCount < 10) {
            clients[clientCount].sockfd = clientSockfd;
            clients[clientCount].addr = clientAddr;
            clients[clientCount].connected = true;
            clientCount++;
        } else {
            close(clientSockfd);
        }
        pthread_mutex_unlock(&lock);
        pthread_t thread;
        int* clientSockfdPtr = malloc(sizeof(int));
        *clientSockfdPtr = clientSockfd;
        pthread_create(&thread, NULL, handleClient, clientSockfdPtr);
    }
    close(serverSockfd);
    pthread_mutex_destroy(&lock);
    exit(EXIT_SUCCESS);
}