#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void* create_shared_memory(size_t size) {
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, -1, 0);
}


volatile sig_atomic_t * sig_termed;


void sig_handler(int sig) {
    *sig_termed = 1;
    while (waitpid(-1, NULL, 0) > 0);
    exit(0);
}

int check(int pw) {
    return (pw < 0 || *sig_termed);
}

void close_and_exit(FILE* fin, FILE* fout) {
    fclose(fin);
    fclose(fout);
    _exit(0);
}

void try_to(int c, FILE* fin, FILE* fout) {
    fflush(fout);
    if (check(c)) {
        close_and_exit(fin, fout);
    }
}

int main(int argc, char* argv[]) {
    sig_termed = create_shared_memory(sizeof(sig_atomic_t));
    *sig_termed = 0;
    
    if (argc < 3) {
        exit(EXIT_FAILURE);
    }
    
    /* set up handler for SIGTERM */
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &sa, NULL);
    
    int port = strtol(argv[1], NULL, 10);
    if (0 >= port || port > 65535) {
        // incorrect port
        exit(EXIT_FAILURE);
    }
    char* key = argv[2];
    
    
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
    int cfd;
    socklen_t clen;
    
    // pid_t server_pid = getpid();
    // printf("%d\n", server_pid);
    // fflush(stdout);
    
    int serial = 1;
    while (1) {
        /* bury "zombies" */
        while (waitpid(-1, NULL, WNOHANG) > 0);
        
        clen = sizeof(client_addr);
        if ((cfd = accept(lfd, (struct sockaddr *) &client_addr, &clen)) < 0) {
            exit(EXIT_FAILURE);
        }
        
        pid_t pid;
        if ((pid = fork()) == -1) {
            // failed to create a new process
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            int cfd2;
            if ((cfd2 = dup(cfd)) < 0) {
                exit(EXIT_FAILURE);
            }
            FILE* fout = fdopen(cfd2, "w");
            FILE* fin = fdopen(cfd, "r");
            
            try_to(fprintf(fout, "%s\r\n", key), fin, fout);
            try_to(fprintf(fout, "%d\r\n", serial), fin, fout);
            
            int max_c;
            try_to(fscanf(fin, "%d", &max_c), fin, fout);
            try_to(fprintf(fout, "%d\r\n", max_c), fin, fout);
            
            int num;
            int sum;
            int over_max = 0;
            while (!over_max && !(*sig_termed)) {
                try_to(fscanf(fin, "%d", &num), fin, fout);
                
                if (num > max_c || __builtin_add_overflow(serial, num, &sum)) {
                    over_max = 1;
                    try_to(fprintf(fout, "%d\r\n", -over_max), fin, fout);
                } else {
                    try_to(fprintf(fout, "%d\r\n", sum), fin, fout);
                }
            }
            
            fclose(fout);
            fclose(fin);
            _exit(0);
        } else {
            close(cfd);
        }
        ++serial;
    }
    
    close(lfd);
    return 0;
}
