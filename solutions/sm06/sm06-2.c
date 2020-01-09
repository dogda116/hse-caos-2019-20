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
    unsigned long long counter;
    struct LinkedList *next;
    struct LinkedList *prev;
};

typedef struct LinkedList *node;

node tail = NULL;
node head = NULL;

void addNode(int value) {
    if (head == NULL) {
        head = malloc(sizeof(struct LinkedList));
        head->counter = 1;
        head->data = value;
        head->prev = NULL;
        head->next = NULL;
        tail = head;
        return;
    }
    node p = head;
    while (p != NULL) {
        if (p->data != value) {
            p = p->next;
        } else if (p == head) {
            p->counter += 1;
            return;
        } else {
            node p_prev = p->prev;
            node p_next = p->next;
            if (p_prev != NULL) {
                p_prev->next = p_next;
            }
            if (p_next != NULL) {
                p_next->prev = p_prev;
            } else {
                tail = p_prev;
            }
            p->next = head;
            p->prev = NULL;
            p->counter += 1;
            head->prev = p;
            head = p;
            return;
        }
    }
    node new_node;
    new_node = (node)malloc(sizeof(struct LinkedList));
    new_node->next = head;
    new_node->prev = NULL;
    new_node->counter = 1;
    new_node->data = value;
    head->prev = new_node;
    head = new_node;
}

int main(void) {
    int input_number;
    while (scanf("%d", &input_number) != EOF) {
        addNode(input_number);
    }
    while (tail != NULL) {
        printf("%d %llu\n", tail->data, tail->counter);
        node tmp_node = tail->prev;
        free(tail);
        tail = tmp_node;
    }
    return 0;
}
