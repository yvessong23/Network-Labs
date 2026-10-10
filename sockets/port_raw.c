#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // Socket lib
#include <netinet/in.h> // Network address lib (sockaddr_in)
#include <unistd.h>     // Universal lib (htons)

typedef struct iphdr {
	unsigned int ihl:4;
   	unsigned int version:4;	
	unsigned int tos;
	uint16_t frag_off;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t check;
	uint32_t saddr;
	uint32_t daddr;
} iphdr;

iphdr *create_header(){
	iphdr *ip = malloc(sizeof(iphdr));
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->frag_off = 0;
	ip->ttl = 65;
	ip->protocol



}

int main(){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    for (int i = 1; i < 65535; i++){
        int fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW); // Define raw socket
        if (fd < 0){
            perror("Could not open socket!\n");
            exit(1);
        }
        addr.sin_port = htons(i); // Define port number to visit
        
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == 0){
            printf("Connected to port %d\n", i);
            close(fd);
        } else {
            close(fd);
        }
    }
}
