#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    int sockfd;
    struct sockaddr_in addr;
} client_info;

client_info clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg);
void send_current_time(int client_sock);
void send_machine_name(int client_sock);
void send_active_connections(int client_sock);
void forward_message(int sender_sock, const char *message, int target_id);

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t thread_id;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, MAX_CLIENTS);

    printf("Server is listening on port %d\n", PORT);

    while ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len))) {
        pthread_mutex_lock(&clients_mutex);
        if (client_count < MAX_CLIENTS) {
            clients[client_count].sockfd = client_sock;
            clients[client_count].addr = client_addr;
            client_count++;
            pthread_create(&thread_id, NULL, handle_client, (void *)&clients[client_count - 1]);
        } else {
            printf("Max clients connected. Rejecting connection.\n");
            close(client_sock);
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    close(server_sock);
    return 0;
}

void *handle_client(void *arg) {
    client_info *client = (client_info *)arg;
    int client_sock = client->sockfd;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the string

        if (strcmp(buffer, "TIME") == 0) {
            send_current_time(client_sock);
        } else if (strcmp(buffer, "NAME") == 0) {
            send_machine_name(client_sock);
        } else if (strcmp(buffer, "ACTIVE") == 0) {
            send_active_connections(client_sock);
        } else if (strncmp(buffer, "MSG ", 4) == 0) {
            int target_id = buffer[4] - '0'; // Extract the target ID
            forward_message(client_sock, buffer + 6, target_id); // Forward message
        }
    }

    close(client_sock);
    pthread_mutex_lock(&clients_mutex);
    client_count--;
    pthread_mutex_unlock(&clients_mutex);
    return NULL;
}

void send_current_time(int client_sock) {
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    send(client_sock, time_str, strlen(time_str), 0);
}

void send_machine_name(int client_sock) {
    char hostname[BUFFER_SIZE];
    gethostname(hostname, sizeof(hostname));
    send(client_sock, hostname, strlen(hostname), 0);
}

void send_active_connections(int client_sock) {
    char buffer[BUFFER_SIZE];
    int len = snprintf(buffer, sizeof(buffer), "Active clients: %d\n", client_count);
    send(client_sock, buffer, len, 0);
}

void forward_message(int sender_sock, const char *message, int target_id) {
    pthread_mutex_lock(&clients_mutex);
    if (target_id >= 0 && target_id < client_count) {
        send(clients[target_id].sockfd, message, strlen(message), 0);
    }
    pthread_mutex_unlock(&clients_mutex);
}