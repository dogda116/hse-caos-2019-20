#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

struct Tree
{
    struct Tree *right;
    struct Tree *left;
    int number;
};

struct Tree *root = NULL;

void add_node(int new_number) {
    if (root == NULL) {
        root = malloc(sizeof(struct Tree));
        root->right = NULL;
        root->left = NULL;
        root->number = new_number;
        return;
    } else {
        struct Tree *p = root;
        while (true) {
            if (p->number == new_number) {
                return;
            } else if (p->number < new_number) {
                if (p->right != NULL) {
                    p = p->right;
                } else {
                    struct Tree *new_node;
                    new_node = malloc(sizeof(struct Tree));
                    new_node->number = new_number;
                    new_node->right = NULL;
                    new_node->left = NULL;
                    p->right = new_node;
                    return;
                }
            } else if (p->number > new_number) {
                if (p->left != NULL) {
                    p = p->left;
                } else {
                    struct Tree *new_node;
                    new_node = malloc(sizeof(struct Tree));
                    new_node->number = new_number;
                    new_node->right = NULL;
                    new_node->left = NULL;
                    p->left = new_node;
                    return;
                }
            }
        }
    }
}


void print_tree(struct Tree *node) {
    if (node == NULL) {
        return;
    } else {
        print_tree(node->right);
        printf("%d ", node->number);
        print_tree(node->left);
        free(node);
    }
}

int main(void) {
    bool last_seq_wo_zero = false;
    int input_number;
    while (scanf("%d", &input_number) != EOF) {
        if (input_number == 0) {
            print_tree(root);
            root = NULL;
            last_seq_wo_zero = false;
            printf("0 ");
            continue;
        }
        add_node(input_number);
        last_seq_wo_zero = true;
    }
    if (last_seq_wo_zero) {
        print_tree(root);
        printf("0\n");
    } else {
        printf("\n");
    }
    return 0;
}
