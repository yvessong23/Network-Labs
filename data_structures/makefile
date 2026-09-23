ppp: port_socket_raw.c
		gcc -W -Wall port_socket_raw.c -o ppp
		sudo setcap cap_net_raw+ep ./ppp 
clean:
	rm -f ppp
