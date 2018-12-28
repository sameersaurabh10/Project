#include "header.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr;
	int sock_fd;
	socklen_t len;	
    char buffer[1024];
	pthread_t thread_id;
	
	serv_addr.sin_family = AF_INET;
	if (! inet_aton(argv[1], &serv_addr.sin_addr) ) {
		printf ("Unable to convert ip_addr to address family\n");
		exit (EXIT_FAILURE);
	}
	serv_addr.sin_port = atoi(argv[2]);
	
	if ((sock_fd = create_socket()) == -1) {
        printf ("Failed to create socket\n");
        exit (EXIT_FAILURE);
    }  

	len = sizeof(struct sockaddr_in);
	if (connect(sock_fd, (struct sockaddr*)&serv_addr, len)) {
		printf ("Failed to connect with server\n");
		exit (EXIT_FAILURE);
	}

	printf ("Connected successfully ...\n");
	pthread_create(&thread_id, NULL, read_handler, &sock_fd);
	pthread_detach(thread_id);

    while(1) {
        memset(buffer, 0, sizeof(buffer));
		usleep(1000);
        printf("\nclient >> ");
        if (!fgets(buffer, 1024, stdin)) {
            print_error("Failed to read from stdin");
        }
        send(sock_fd, buffer, 1024, 0); 
    }   

}//END OF FUNCTION
