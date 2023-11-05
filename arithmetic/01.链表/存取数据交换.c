#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

int main() {
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = array[0];
    head->next = NULL;
    for (int i = 1; i < 10; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = array[i];
        new_node->next = NULL;
        Node* current = head;
        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    return 0;
}