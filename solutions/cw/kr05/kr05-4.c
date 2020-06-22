#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>


int main(int argc, char* argv[]) {
    int f = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    uint32_t num;
    while (scanf("%" SCNu32, &num) != EOF) {
        unsigned char buffer[4];
        // convert little-endian to big-endian
        buffer[0] = (num >> 24) & 0xff;
        buffer[1] = (num >> 16) & 0xff;
        buffer[2] = (num >> 8) & 0xff;
        buffer[3] = num & 0xff;

        // write call is guaranteed to be successful
        write(f, buffer, 4);
    }
    close(f);
}
