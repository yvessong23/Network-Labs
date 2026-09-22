#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


typedef struct iphdr {
    // These two share the first byte (8 bits total)
    unsigned int version:4;  // Must be 4 for IPv4, for Routers
    unsigned int ihl:4;      // Internet Header Length (usually 5)

    uint8_t  tos;            // Type of Service, aka Differentiated Services Code Point 
    uint16_t tot_len;        // Total Length of the packet
    uint16_t id;             // Identification
    uint16_t frag_off;       // Fragment Offset & Flags
    uint8_t  ttl;            // Time to Live
    uint8_t  protocol;       // Protocol (e.g., 6 for TCP, 17 for UDP) for OS
    uint16_t check;          // Header Checksum
    uint32_t saddr;          // Source IP Address (32-bit unsigned int)
    uint32_t daddr;          // Destination IP Address (32-bit unsigned int)
} iphdr;

 typedef struct tcphdr{
    uint16_t src_port;      /* source port */
    uint16_t dst_port;     /* destination port */
    uint32_t seq;           /* sequence number */
    uint32_t ack;           /* acknowledgement number */
    uint8_t th_x2:4;        /* (unused) */
    uint8_t th_off:4;       /* data offset */
    uint8_t flags;
    # define TH_FIN 0x01
    # define TH_SYN 0x02        
    # define TH_RST 0x04        
    # define TH_PUSH 0x08
    # define TH_ACK 0x10
    # define TH_URG 0x20
    uint16_t th_win;        /* window */
    uint16_t th_sum;        /* checksum */
    uint16_t th_urp;        /* urgent pointer */
} tcphdr;

typedef struct master_hdr{
    iphdr *iphdr;
    tcphdr *tcphdr;
} master_hdr;

typedef struct pseudo_tcphdr{
    uint32_t saddr;          // Source IP Address (32-bit unsigned int)
    uint32_t daddr;
    uint8_t reserved;        // For padding
    uint8_t protocol;
    uint16_t tcphdr_len;
} pseudo_tcphdr;

tcphdr *create_tcphdr(){
    // src port, dst port from where? Can do a for loop
    tcphdr *t = malloc(sizeof(tcphdr));
    t->src_port = htons(1024 + (rand() % 64000));
    t->dst_port = htons(1024 + (rand() % 64000));
    t->seq = htonl(1024 + (rand() % 64000));
    t->ack = 0;
    t->th_x2 = 0;
    t->flags = TH_SYN;
    t->th_win = htons(64000);
    t->th_sum = 0;
    t->th_urp = 0;
    return t;
}

iphdr *create_iphdr(int id_count){ 
    iphdr *h = malloc(sizeof(iphdr));
    h->version = 4;
    h->ihl = 5;
    h->tos = 0;
    h->tot_len = 40;
    h->id = id_count;
    h->frag_off = 0;
    h->ttl = 64;
    h->protocol = 6;
    h->check = 0;
    
    if(inet_pton(AF_INET, "10.0.0.2", &h->saddr) != 1){
         perror("Wrong SRC address assignment!\n");
         exit(1);
    };
    
    if(inet_pton(AF_INET, "192.168.4.33", &h->daddr) != 1){
         perror("Wrong DEST address assignment!\n");
         exit(1);
    }
    return h;
}

uint16_t checksum(void *ptr, int size){ // One compliment's algorithm
    uint32_t total = 0;         
    uint16_t *t_bytes = (uint16_t*)ptr; // 20 or 12.. or 250 byte struct needs to be read by short
   
    for (int i = 0; i < size; i++){
        total+=t_bytes[i];
    }
    
    uint16_t upper = total >> 16;      // Take upper half values
    uint16_t lower = (total & 0xffff); // Take lower half values
    upper+=lower;                // Add upper back to total
    return ~upper;
}

master_hdr bridge_hdr(iphdr *ip, tcphdr *t){ // Create one header from tcp/ip
    master_hdr *header = malloc(40 * sizeof(char)); // 40 byte header for tcp + ip
    header->iphdr = ip;
    header->tcphdr = t;
    return header;
}

pseudo_tcphdr *pseudo_tcp_calc(master_hdr *m){
    pseudo_tcphdr *ps = malloc(sizeof(pseudo_tcphdr));
    ps->saddr = m->iphdr->saddr;
    ps->daddr = m->iphdr->daddr;
    ps->protocol = m->iphdr->protocol;
    ps->tcphdr_len = htons(20);
}

int main(){
	//struct sockaddr_in addr;
	//addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW); // Create socket
    int id_count = 0;
    iphdr *iphdr = create_iphdr(id_count++);
    tcphdr *tcphdr = create_tcphdr();
    ip->check = checksum(iphdr,sizeof(iphdr));
    master_hdr = bridge_hdr(ip, tcphdr);
    pseudo_tcphdr *ps = pseudo_tcp_calc(master_hdr); 
    tcphdr->th_sum = checksum(ps,sizeof(pseudo_tcphdr));
    
    /*
    for (int i = 1024; i < 2070; i++){
		int fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
		if (fd < 0){
			perror("Could not open socket!\n");
			exit(1);
	    }
        	
        //addr.sin_port = htons(i);
        if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == 0){
            printf("Connected to port %d\n", i);
            close(fd);
        } else {
            close(fd);
        }
    }
    */
}
