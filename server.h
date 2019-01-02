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
#define MAX 128
#define MAX_CLIENTS 50                                                          
#define BUFFER_SIZE 1024
int clients[MAX_CLIENTS];
struct sockaddr_in clients_addr[MAX_CLIENTS];

void remove_fd(int fd);
void handle_error(char *msg, bool opt);
struct client_info * get_sockaddr_by_fd(int fd);

struct client_info {
	int own_fd;
	int user_fd;
	bool user_connected; /*User connected or not*/
	struct sockaddr_in user_addr; /*Other user address*/
	struct sockaddr_in own_addr; /*Own address*/
};
struct clienf_info client_info[MAX_CLIENTS];

struct message{                                                                 
    int user_address; /*Flag indicate user address present or not*/
    struct sockaddr_in addr;                                                       
};
struct message initial_msg;

#endif

