/* с семинара 182-1 */
#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    char* host = argv[1];
    char* service = argv[2];
    
    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    struct addrinfo* res = NULL;
    
    /* "if connection is lost, client should exit with exit status 0" */
    int err = getaddrinfo(host, service, &hints, &res);
    if (err) {
        exit(0);
    }
    
    int sfd;
    if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        freeaddrinfo(res);
        exit(0);
    }
    
    if (connect(sfd, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        exit(0);
    }
    
    int sfd2;
    if ((sfd2 = dup(sfd)) < 0) {
        freeaddrinfo(res);
        exit(0);
    }
    FILE* fout = fdopen(sfd2, "w");
    FILE* fin = fdopen(sfd, "r");
    
    /* check key */
    char received_key[30];
    fgets(received_key, sizeof(received_key), fin);
    printf("Received key is: %s\n", received_key);
    fflush(stdout);
    
    /* check serial */
    char received_serial[30];
    fgets(received_serial, sizeof(received_serial), fin);
    printf("Received serial is: %s\n", received_serial);
    fflush(stdout);
    
    /* send max and check it */
    char * max_c = argv[3];
    fprintf(fout, "%s\r\n", max_c);
    fflush(fout);
    
    if (ferror(fout)) {
        freeaddrinfo(res);
        exit(0);
    }
    
    char max_s[30];
    fgets(max_s, sizeof(max_s), fin);
    printf("Received max is: %s\n", max_s);
    fflush(stdout);
    
    int k = 4;
    while (1) {
        char str[12];
        sprintf(str, "%d", k);
        
        fprintf(fout, "%s\r\n", str);
        fflush(fout);
        printf("Sent: %s\n", str);
        fflush(stdout);
        sleep(1);
        char back[12];
        fgets(back, sizeof(back), fin);
        printf("Received: %s\n", back);
        fflush(stdout);
        ++k;
    }

    fclose(fin);
    fclose(fout);
    freeaddrinfo(res);
    return 0;
}