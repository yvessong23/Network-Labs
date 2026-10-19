CC = gcc
CFLAGS = -g -02 -Wextra -Wall -fdiagnostics-color=always
TARGET = ppp
SRC = port_socket_raw.c

$(TARGET): $(SRC)
		$(CC) $(FLAGS) $(SRC) -o $(TARGET)

setcap: $(TARGET)
	sudo setcap cap_net_raw+ep ./$(TARGET)

run: setcap
	./$(TARGET)

memcheck: $(TARGET)
	-sudo setcap -r ./$(TARGET)
	sudo valgrind --track-origins=yes ./$(TARGET)

clean:
	rm -f ppp

.PHONY: setcap run memcheck clean
