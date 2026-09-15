#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	for (int i = 1024; i < 2070; i++){
		int fd = socket(AF_INET, SOCK_STREAM, 0);
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
