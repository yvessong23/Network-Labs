#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct iphdr {
    // These two share the first byte (8 bits total)
    unsigned int version:4;  // Must be 4 for IPv4
    unsigned int ihl:4;      // Internet Header Length (usually 5)

    uint8_t  tos;            // Type of Service, aka Differentiated Services Code Point 
    uint16_t tot_len;        // Total Length of the packet
    uint16_t id;             // Identification
    uint16_t frag_off;       // Fragment Offset & Flags
    uint8_t  ttl;            // Time to Live
    uint8_t  protocol;       // Protocol (e.g., 6 for TCP, 17 for UDP)
    uint16_t check;          // Header Checksum
    uint32_t saddr;          // Source IP Address (32-bit unsigned int)
    uint32_t daddr;          // Destination IP Address (32-bit unsigned int)
} iphdr;

void create_iphdr(int id_count){
    iphdr *h = malloc(sizeof(iphdr));
    h->version = 4;
    h->ihl = 5;
    h->tos = 0;
    h->tot_len = 40;
    h->id = id_count;
    h->frag_off = 0;
    h->ttl = ;
}


int main(){
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	for (int i = 1024; i < 2070; i++){
		int fd = socket(AF_INET, SOCK_RAW, 0);
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
