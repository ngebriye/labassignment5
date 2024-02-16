#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} node;

int length(node* head) {
    int len = 0;
    node* current = head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

char* toCString(node* head) {
    int len = length(head);
    char* str = (char*)malloc((len + 1) * sizeof(char)); // This is where we allocate memory for string
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    node* current = head;
    while (current != NULL) {
        str[i] = current->data;
        i++;
        current = current->next;
    }
    str[i] = '\0'; // this null will terminate the string
    return str;
}

void insertChar(node** pHead, char c) {
    node* newNode = (node*)malloc(sizeof(node)); // now we are allocating memory for the new node
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = c;
    newNode->next = *pHead;
    *pHead = newNode;
}

void deleteList(node** pHead) {
    node* current = *pHead;
    node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *pHead = NULL; // we need to update head to NULL
}

int main() {
    FILE *fp;
    int n, i, j, len;
    char c;
    node* head = NULL;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &len);
        for (j = 0; j < len; j++) {
            fscanf(fp, " %c", &c);
            insertChar(&head, c);
        }
        printf("%s\n", toCString(head));
        deleteList(&head);
    }

    fclose(fp);
    return 0;
}
