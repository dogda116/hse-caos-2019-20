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
    
    fprintf(fout, "%s\n", argv[3]);
    fflush(fout);
    
    if (ferror(fout)) {
        freeaddrinfo(res);
        exit(0);
    }
    
    int k = -1;
    if (fscanf(fin, "%d", &k) != 1) {
        freeaddrinfo(res);
        exit(0);
    }
    
    for (int i = 0; i <= k; ++i) {
        fprintf(fout, "%d\n", i);
        fflush(fout);
        
        if (ferror(fout)) {
            freeaddrinfo(res);
            exit(0);
        }
    }
    
    unsigned long long reply = 0;
    if (fscanf(fin, "%llu", &reply) != 1) {
        freeaddrinfo(res);
        exit(0);
    }
    
    printf("%llu\n", reply);
    fflush(stdout);
    fclose(fin);
    fclose(fout);
    freeaddrinfo(res);
    return 0;
}
