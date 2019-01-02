#include "header.h"

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

int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr;
	int sock_fd;
	socklen_t len;	
    char buffer[1024];
	pthread_t thread_id;
	struct message initial_msg;
		

	if (argc != 4 ) {
        handle_error("Provide correct input,syntax : \
                        ./a.out <IPAddr> <portNo> <UserIP>", true);
    }
	serv_addr.sin_family = AF_INET;
	if (! inet_aton(argv[1], &serv_addr.sin_addr) ) {
		handle_error ("Unable to convert ip_addr to address family", true);
	}
	serv_addr.sin_port = atoi(argv[2]);
	
	if ((sock_fd = socket (AF_INET,SOCK_STREAM,0)) == -1) {
        handle_error ("Failed to create socket", true);
    }  

	len = sizeof(struct sockaddr_in);
	if (connect(sock_fd, (struct sockaddr*)&serv_addr, len)) {
		handle_error ("Failed to connect with server", true);
	}

	printf ("Connected successfully ...\n");
	pthread_create(&thread_id, NULL, read_handler, &sock_fd);
	pthread_detach(thread_id);

	memset(initial_msg, 0, sizeof(initial_msg));

	/*Setting user info, with whom need to connect*/	
	if (argv[3])
		initial_msg.option = 1;
		initial_msg.addr.sin_addr.s_addr = inet_addr(argv[3]);
	}
    send(sock_fd, initial_msg, sizeof(initial_msg), 0); 
    while(1) {
        memset(buffer, 0, sizeof(buffer));
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            handle_error("Failed to read from stdin", false);
        }
        send(sock_fd, buffer, BUFFER_SIZE, 0); 
    }   

}//END OF FUNCTION

