#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }
    
    int port = strtol(argv[1], NULL, 10);
    if (0 >= port || port > 65535) {
        exit(EXIT_FAILURE);
    }
    
    int lfd;
    if ((lfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        exit(EXIT_FAILURE);
    }
    
    int val = 1;
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        exit(EXIT_FAILURE);
    }
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val)) < 0) {
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in serv_addr = { 
        .sin_family = AF_INET, 
        .sin_addr.s_addr  = INADDR_ANY, 
        .sin_port = htons(port)
    };
    
    if (bind(lfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        exit(EXIT_FAILURE);
    }
    
    if (listen(lfd, 5) < 0) {
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in client_addr;
    int afd;
    socklen_t clen;
    
    int sum = 0;
    while (1) {
        clen = sizeof(client_addr);
        if ((afd = accept(lfd, (struct sockaddr *) &client_addr, &clen)) < 0) {
            exit(EXIT_FAILURE);
        }
        
        int num;
        if (read(afd, &num, sizeof(num)) < 0) {
            exit(EXIT_FAILURE);
        }
        close(afd);
        num = ntohl(num);
        sum += num;
        if (num == 0) {
            break;
        }
    }
    
    printf("%d\n", sum);
    fflush(stdout);
    close(lfd);
    return 0;
}
