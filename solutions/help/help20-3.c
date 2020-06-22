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
    
    int t = strtol(argv[3], NULL, 10);
    t = htonl(t);
    write(sfd, &t, sizeof(t));
    
    freeaddrinfo(res);
    return 0;
}