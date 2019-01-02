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

void remove_fd(int fd);
void handle_error(char *msg, bool opt);

#endif

