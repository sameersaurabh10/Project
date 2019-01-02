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
#include <stdbool.h>
#define MAX_CLIENTS 50                                                          
#define BUFFER_SIZE 1024

void handle_error(char *msg, bool opt);
void *read_handler(void *data);

struct message{
	int option; /*1 = want to connect to a user
				 *0 = no need to connect any user*/
	struct sockaddr_in addr;
};
#endif

