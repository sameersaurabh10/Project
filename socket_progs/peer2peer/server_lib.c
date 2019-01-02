#include "server.h"

/*Function to remove fd from fd_array of terminated client*/
void remove_fd(int fd) 
{
    int i = 0, j = 0;
    while(clients[i] > 0) {
        if (clients[i] == fd) {
            j = i;
            while(clients[j+1] > 0) {
                clients[j] = clients[j+1];
                j++;
            }    
            if (clients[i] == clients[j])
                clients[i] = 0;
            break;
        }
        i++;
    }   
}

/*Fcuntion to find sockaddr_in entry in clients_addr list*/
struct sockaddr_in *get_user (struct sockaddr_in *arg)
{
	int i = 0;
	while(clients_addr[i]) {
		if (!memcmp(clients_addr[i].sin_addr, arg.sin_addr, 
			sizeof(clients_addr[i].sin_addr)) ) 
		{
			return clients_addr[i++];
		}
	}
	return NULL;
}

void handle_error(char *msg, bool opt)                                          
{                                                                               
    if (opt) {                                                                  
        //printf("ERROR : %s\n", msg);                                          
        perror(msg);                                                            
        exit(EXIT_FAILURE);                                                     
    }                                                                           
    else {                                                                      
        perror(msg);                                                            
    }                                                                           
}


/*Function to store the client info*/
bool gather_client_info(struct sockaddr_in *addr, int instance_no,int fd)
{
	int i = instance_no;
	if (addr->user_address) {
		client_info[i].user_connected = true;
	}
	client_info[i].fd = fd;
	memcpy (client_info[i].user_addr, addr, sizeof(addr));

	return true;
}

/*Function to find client_info address in list*/
struct client_info * get_sockaddr_by_fd(int fd)
{
	int i = 0;
	while(client_info[i]) {
		if (client_info[i].own_fd == fd)
			return &client_info[i];
		i++;
	}
	return NULL;
}

void *handle_groups(void *arg)
{
	char buffer[BUFFER_SIZE];
	int fd = *((int *)arg);
	if((ret = read (fd, buffer, BUFFER_SIZE)) < 0 ) {       
		handle_error("Failed to read messages from clients", false);
	else if (ret == 0) {                                          
		FD_CLR(fd, &fds);                                   
		remove_fd (fd);                                     
		handle_error("Client got disconneted", false);              
	else {                                                        
		printf ("client >> %s\n", buffer);                          
	}

	return NULL;
}
