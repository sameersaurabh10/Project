#include "header.h"

int main(int argc, char *argv[])
{
	/*Variable declaration*/
	struct sockaddr_in addr, cli_addr;
	int sock_fd, cli_sock;
	socklen_t len;
	pthread_t thread_id[MAX_CONNECTION];	

	/*Validate number of input */	
	if (argc != 3 ) {
		print_error("Syntax : <./a.out> <IP address> <portNo>");
	}

	if ((sock_fd = create_socket()) == -1) {
		print_error("Failed to create socket");
	}
		
	memset (&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = atoi(argv[2]);

	/*Binding IP address and port no with fd*/
	int ret;
	if ((ret = bind(sock_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) == -1) {
		printf ("ret : %d\n", ret);
		print_error ("Unable to bind ip address with fd");
	}
		
	if (listen (sock_fd, MAX_CONNECTION) == -1) {
		print_error("Listen function failed on specified ip and port\n");
	}

	len = sizeof(struct sockaddr_in);
	count = 0; /*To count noumber of clients connected */
	while (1) {
		printf ("Listening on the ip : %s, and portNo : %d\n",inet_ntoa(addr.sin_addr), addr.sin_port);
		if ((cli_sock = accept (sock_fd, (struct sockaddr*)&cli_addr, &len)) == -1) {
			print_error ("Unable to accept the connection");
		}
		printf ("\nNew client Connected with IP addr : %s, portNo : %d\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);
		printf ("Total clients connected : %d\n", (count + 1) );
		send(cli_sock , "Hello from server..." , strlen("Hello from server") , 0 ); 

		fd_array[count] = cli_sock;
		client_addr[count].cli_sock = cli_sock;
		memcpy( &client_addr[count].cli_addr, &cli_addr, sizeof(cli_addr));
		pthread_create(&thread_id[count], NULL, client_handler, &client_addr[count]);
		pthread_detach(thread_id[count++]);

	}//END of While loop

}//END OF MAIN FUNCTION
