#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0){
		perror("Could not open socket!");
		exit(1);
	}

	struct sockaddr_in {
           sa_family_t     sin_family;     /* AF_INET */
           in_port_t       sin_port;       /* Port number */
           struct in_addr  sin_addr;       /* IPv4 address */
       };
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = htonl(INADDR_LOOPBACK);
	for (int i = 1; i < 1048; i++){
		addr.sin_port = htons(i);
		int conn = connect(fd, (struct sockaddr*)&addr, sizeof(sockaddr_in));
		if(conn < 0){
			printf("Could not connect to port %d", i);
		} else {
			printf("Found port %d", i);
		}
	}
}
