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
	int sock_fd, cli_sock;;
	struct sockaddr_un addr;
	struct sockaddr_un  cli_addr;
	socklen_t len, cli_len;

	if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		print_error("Failed to create socket");
	}

	printf("Setting unix path..\n");
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "socket", sizeof(addr.sun_path)-1);
	len = sizeof(addr);	

	printf("Binding...\n");	
	if (bind(sock_fd, (struct sockaddr*)&addr, len) < 0) {
		print_error("Failed to bind fd with unix socket");
	}
		
	printf ("!!! Server is listening on path : %s\n", addr.sun_path);
    if (listen (sock_fd, MAX_CLIENTS)) {
        print_error("Failed mark socket as passive socket");
    }
	

	if ((cli_sock = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len)) < 0) {
		print_error("Failed to accept connection");
	}

	char *msg = "Hello from server";
	printf("Connection from client...\n");	
	if (send(cli_sock, msg, sizeof(msg), MSG_CONFIRM) < 0) {
		print_error("Failed to write to client descriptor");
	}
	msg = (char *) malloc(sizeof(char));
	int msg_size;
	if ((msg_size = recv(sock_fd, msg, 1024, 0)) < 0) {
		print_error("Failed to read from client");	
	}

	printf("Total read bytes from client : %d \n", msg_size);
	printf("Recieved message : %s \n", msg);

	return EXIT_SUCCESS;
}
