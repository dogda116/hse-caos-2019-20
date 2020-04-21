#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>


struct FileContent read_file(int fd) {
    struct FileContent fc;
    fc.data = NULL;
    fc.size = 0;
    
    ssize_t r;
    char buffer[4096];
    
    /* 
            ssize_t read(int filedes, void *buf, size_t nbytes);
    returns the number of successfully read bytes 
    or 0 if reached the end of file 
    or -1 if an error occured
    */
    while ((r = read(fd, buffer, 4096))) {
        // buffer to data
        
        if (r == -1) {
            free(fc.data);
            fc.size = -1;
            fc.data = NULL;
            return fc;
        }
        
        /*
                void *realloc( void *ptr, size_t new_size );
        Reallocates the given area of memory.
        The reallocation is done by either:
        
        a) expanding or contracting the existing area pointed to by ptr, if possible. 
        The contents of the area remain unchanged up to the lesser of the new and old sizes. 
        If the area is expanded, the contents of the new part of the array are undefined.
        
        b) allocating a new memory block of size new_size bytes, 
        copying memory area with size equal the lesser of the new and the old sizes,
        and freeing the old block.
        
        If there is not enough memory, the old memory block is not freed and null pointer is returned.
        */
        char* read_bytes = realloc(fc.data, fc.size + r);
        
        if (read_bytes == NULL) {
            // failed to allocate memory
            free(fc.data);
            fc.size = -1;
            fc.data = NULL;
            return fc;
        } else {
            fc.data = read_bytes;
            
            /*
                    void* memcpy( void *dest, const void *src, size_t count );
            Copies 'count' characters from the object pointed to by 'src' to the object pointed to by 'dest'. 
            Both objects are interpreted as arrays of 'unsigned char'.
            */
            memcpy(fc.data + fc.size, buffer, r);
            
            fc.size += r;
        }
    }
    
    char* spc = realloc(fc.data, fc.size + 1);
    if (spc == NULL) {
        // failed to allocate memory
        free(fc.data);
        fc.size = -1;
        fc.data = NULL;
    } else {
        fc.data = spc;
        fc.data[fc.size] = '\0';
    }
    return fc;
}
