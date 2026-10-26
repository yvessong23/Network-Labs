CC = gcc
CFLAGS = -g -O2 -Wextra -Wall -fdiagnostics-color=always
CBUG = -g -Werror -Wall -fdiagnostics-color=always
TARGET = ppp
SRC = port_socket_raw.c

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

setcap: $(TARGET)
	sudo setcap cap_net_raw+ep ./$(TARGET)

run: setcap
	./$(TARGET)

debug: $(SRC)
	$(CC) $(CBUG) $(SRC) -o $(TARGET)

memcheck: $(TARGET)
	-sudo setcap -r ./$(TARGET)
	sudo valgrind --track-origins=yes ./$(TARGET)

clean:
	rm -f ppp

.PHONY: setcap run memcheck clean
