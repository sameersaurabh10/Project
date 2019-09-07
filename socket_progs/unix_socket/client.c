/*
 * This is server program, which will listen on a unix socket
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/un.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 50

void print_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
	int sock_fd;
	struct sockaddr_un addr;
	socklen_t len;

	if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		print_error("Failed to create socket");
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "socket", sizeof(addr.sun_path)-1);
	len = sizeof(addr);	
	
	if (connect(sock_fd, (struct sockaddr*)&addr, len) < 0) {
		print_error("Failed to connect unix path");
	}
	char *msg = (char *) malloc(sizeof(char));
	int msg_len;

	if ((msg_len = recv(sock_fd, msg, 1024, 0 ) < 0)) {
		print_error("Failed to recieve from server");
	}

	free(msg);

	printf("Total read bytes from client : %d \n", msg_len);
	printf("Recieved message : %s \n", msg);
	msg = "Hello world from client";
	if (send(sock_fd, msg, sizeof(msg), 0) < 0 ) {
		print_error("Failed to send message to server");
	}
	

	return EXIT_SUCCESS;
}
