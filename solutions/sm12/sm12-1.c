#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <inttypes.h>

int main(int argc, char* argv[]) {
    /*
    O_WRONLY -- Open for writing only.
    O_CREAT  -- If file does not exist, it will be created.
                This flag requires the presence of the third parameter (mode),
                which sets access permissions for newly created file.
    O_TRUNC  -- If the file exists and is a regular file, 
                and the file is successfully opened O_RDWR or O_WRONLY, 
                its length shall be truncated to 0, 
                and the mode and owner shall be unchanged.
    
    
    The new file mode is specified in mode, which is a bit mask created
    by ORing together zero or more of the following:
    S_IRUSR  (00400)  read by owner
    S_IWUSR  (00200)  write by owner
    */
    int f = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    uint16_t num;
    while (scanf("%" SCNu16, &num) != EOF) {
        unsigned char buffer[2];
        // convert little-endian to big-endian
        buffer[0] = (num >> 8) & 0xff;
        buffer[1] = num & 0xff;
        
        // write call is guaranteed to be successful
        write(f, buffer, 2);
    }
    close(f);
}
