#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

/*
    struct Node a[size];
*/

void reverse_in_order_traversal(int f, int32_t array_index) {
    struct Node tree_node;
    
    /*
    off_t lseek(int fd, off_t offset, int whence);
       lseek() repositions the file offset of the open file description
       associated with the file descriptor fd to the argument offset
       according to the directive whence as follows:

       SEEK_SET
              The file offset is set to offset bytes.

       SEEK_CUR
              The file offset is set to its current location plus offset
              bytes.

       SEEK_END
              The file offset is set to the size of the file plus offset
              bytes.
    
    Here we repostion the file offset to the place where current node is located,
    so we can straight read sizeof(tree_node) bytes into &tree_node
    Rough interpretation below:
    struct Node tree_node = a[array_index] = *(a + array_index * sizeof(tree_node))
    */
    if (lseek(f, array_index * sizeof(tree_node), SEEK_SET) < 0) {
        // failed to change the postion
        exit(EXIT_FAILURE);
    }
    
    
    /*
    we shall consider the case when 'read' call returned -1 or 
    could have read lesser amount of bytes than sizeof(tree_node),
    which means that some values of struct Node tree_node are incorrect
    and we cannot proceed the traversal
    */
    if (read(f, &tree_node, sizeof(tree_node)) < sizeof(tree_node)) {
        exit(EXIT_FAILURE);
    }
    
    /*
    Perform reverse in-order traversal (right-node-left [RNL]):
    In a binary search tree, reverse in-order traversal retrieves the keys in descending sorted order.
    Zero index means an absence of the respective subtree
    */
    
    if (tree_node.right_idx != 0) {
        reverse_in_order_traversal(f, tree_node.right_idx);
    }
    
    printf("%d\n", tree_node.key);
    
    if (tree_node.left_idx != 0) {
        reverse_in_order_traversal(f, tree_node.left_idx);
    }
}

int main(int argc, char* argv[]) {
    /* O_RDONLY Open for reading only. */
    int f = open(argv[1], O_RDONLY);
    if (f < 1) {
        // failed to open the file
        exit(EXIT_FAILURE);
    }
    
    // start traversing from root which has an index 0
    reverse_in_order_traversal(f, 0);
    
    close(f);
    return 0;
}
