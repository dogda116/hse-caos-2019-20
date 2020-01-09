#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

struct LinkedList
{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList *node;

node addNode(node head, int value) {
    node new_node;
    new_node = (node)malloc(sizeof(struct LinkedList));
    new_node->next = head;
    new_node->data = value;
    return new_node;
}

int main(void) {
    int input_number;
    node head = NULL;
    while (scanf("%d", &input_number) != EOF) {
        head = addNode(head, input_number);
    }
    while (head != NULL) {
        printf("%d\n", head->data);
        node tmp_node = head->next;
        free(head);
        head = tmp_node;
    }
    return 0;
}
