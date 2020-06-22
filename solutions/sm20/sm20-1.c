#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    char line[1001];
    while (fgets(line, sizeof(line), stdin)) {
        char host[sizeof(line)];
        char service[sizeof(line)];
        
        if (sscanf(line, "%s%s", host, service) != 2) {
            exit(EXIT_FAILURE);
        }
        
        struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
        struct addrinfo* res = NULL;
        
        int err = getaddrinfo(host, service, &hints, &res);
        if (err) {
            printf("%s\n", gai_strerror(err));
            continue;
        }
        
        struct sockaddr_in* ans = NULL;
        struct addrinfo* curr = res;
        
        while (curr) {
            struct sockaddr_in* ain = (struct sockaddr_in*)curr->ai_addr;
            if (!ans || ntohl(ain->sin_addr.s_addr) < ntohl(ans->sin_addr.s_addr)) {
                ans = ain;
            }
            curr = curr->ai_next;
        }
        
        if (ans) {
            printf("%s:%d\n", inet_ntoa(ans->sin_addr), ntohs(ans->sin_port));
        }
        freeaddrinfo(res);       
    }
    return 0;
}
