#include "header.h"

/* Function to create socket*/
int create_socket()
{
    int fd; 
    fd = socket (AF_INET,SOCK_STREAM,0);
    if (fd < 0 ) return -1; 
    return fd; 
}

/*Function to display error on stdout*/
void print_error(char *msg)
{
	printf("ERROR !! %s\n", msg);
	exit(EXIT_FAILURE);
}

/*Function to remove fd from fd_array of terminated client*/
void remove_fd(int fd) 
{
    int i = 0, j = 0;
    while(fd_array[i] > 0) {
        if (fd_array[i] == fd) {
            j = i;
            while(fd_array[j+1] > 0) {
                fd_array[j] = fd_array[j+1];
                j++;
            }    
            if (fd_array[i] == fd_array[j])
                fd_array[i] = 0;
            break;
        }
        i++;
    }   
}

/*Client handler function */
void *client_handler (void *data)
{
    struct client *client_addr = (struct client *) data;
    int cli_sock = client_addr->cli_sock;
    struct sockaddr_in *cli_addr = &client_addr->cli_addr;
    int read_bytes;
    char buffer[1024];

    while(1) {
        if ((read_bytes = read(cli_sock, buffer, 1024)) > 0) {
            //buffer[read_bytes] = '\0';
            printf("%s (%d) >> %s\n",inet_ntoa(cli_addr->sin_addr), cli_addr->sin_port,buffer);
        } else if (read_bytes == 0 ) { 
            printf("%s (%d) got terminated\n",inet_ntoa(cli_addr->sin_addr), cli_addr->sin_port);
            remove_fd(cli_sock);
            count--;
            break;
        }
        flood_msg(buffer, cli_sock);
    }//END of reading loop in child process
	return NULL;
}


/*Function to flood messages to all the client connected to server*/
void flood_msg(char *msg, int fd)
{
    int i = 0;
    while(fd_array[i] > 0 ) {
        if (fd != fd_array[i]) {
            send(fd_array[i] , msg , strlen(msg) + 1, 0 );
        }
        i++;
    }
}


/*Function to handle messages sent from server*/
void *read_handler(void *data)
{
    int fd = *((int *)data);
    char buffer[1024];
    int read_bytes;

    while(1) {
        if ((read_bytes = recv(fd, buffer, 1024, 0)) > 0) {
            buffer[read_bytes] = '\0';
            printf("\nserver >> %s", buffer);
			printf("\nclient >> ");
            fflush(stdout);
        }   
    }   
}
