#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // Socket lib
#include <netinet/in.h> // Network address lib (sockaddr_in)
#include <unistd.h>     // Universal lib (htons)

int main(){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    for (int i = 1; i < 65535; i++){
        int fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
        if (fd < 0){
            perror("Could not open socket!\n");
            exit(1);
        }

        addr.sin_port = htons(i);
        if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == 0){
            printf("Connected to port %d\n", i);
            close(fd);
        } else {
            close(fd);
        }
    }
}
