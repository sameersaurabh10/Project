#ifndef __HEADER_H
#define __HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 128
#define MAX_CONNECTION 10	/*Maximum 10 client can connect */

int create_socket();
void print_error(char *);
void flood_msg(char *msg, int fd);
void *client_handler (void *data);
void remove_fd(int fd);
void *read_handler(void *data);

int count;
int fd_array[MAX_CONNECTION];
struct client {
	struct sockaddr_in cli_addr;
	int cli_sock;
};
struct client client_addr[MAX_CONNECTION];
#endif
