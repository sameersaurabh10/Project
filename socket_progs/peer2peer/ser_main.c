#include "server.h"

int client_counts = 0;

int main(int argc, char *argv[])
{
	struct sockaddr_in addr, cli_addr;
	int sock_fd, cli_fd, maxfd, k = 0;
	socklen_t len;
	fd_set fds;
	char buffer[BUFFER_SIZE];
	
	
	if (argc != 3 ) {
		handle_error("Provide correct input,syntax : \
						./a.out <IPAddr> <portNo>", true);
	}

	len = sizeof(struct sockaddr);
	if ((sock_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		handle_error("Failed to create socket", true);
	}

	memset (&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = atoi(argv[2]);
	
/*	if (setsockopt(sock_fd, SO_REUSEADDR | SO_REUSEPORT, opt,&opt, sizeof(opt)) < 0) 
	{
		handle_error("setsockopt function failed", true);
	}
*/
	if (bind(sock_fd,(struct sockaddr *)&addr, len) == -1) {
		handle_error("Failed to bind ip address with fd", true);
	}

	if (listen (sock_fd, MAX_CLIENTS)) {
		handle_error("Failed mark socket as passive socket", true);
	}

	

	printf ("!!! Server is listening on IPaddr : %s, portNo : %d !!!\n", 
				inet_ntoa(addr.sin_addr), addr.sin_port);

	while (1) {

		FD_ZERO(&fds);
		FD_SET(sock_fd, &fds);
		maxfd = sock_fd;

		while (clients[k] > 0) {
			FD_SET(clients[k], &fds);

			if (maxfd < clients[k])
				maxfd = clients[k] ;
			k++;
		}
		
		/*select monitoring the file descriptors*/
		if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0) {
			handle_error("Select system call failed", true);
		}

		/* IF something happened on sock_fd means it's incoming connection*/
		if (FD_ISSET(sock_fd, &fds)) {
			if ((cli_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, 
				&len)) < 0) 
			{
				handle_error("Failed to except connection from client", false);
			}			
			printf("New client connected with IP : %s, portNo : %d\n", 
				inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);

			clients[client_counts] = cli_fd;

			char message[] = "How can I help you ?";
			int read_bytes;
			if ((read_bytes = recv(cli_fd, &initial_msg, sizeof(initial_msg), 0)) < 0 ) {
				handle_error ("Failed to read", false);	
			} else if (read_bytes == 0) {
				handle_error("Client got disconnected", false);
			}else {
				gather_client_info(&msg.addr, count);
				memcpy (client_info[i].own_addr, cli_addr, sizeof(cli_addr));
				count++;
			}
			if (send(cli_fd, message, sizeof(message), 0) < 0) {
				handle_error("Failed to send welcome message to new client", false);
			}
		}//END incoming connection handling block

		/*I/O event on any fd apart from server sock*/
		int i = 0, ret;
		memset (buffer, 0, sizeof(buffer));
		while (clients[i] > 0) {
			if (FD_ISSET(clients[i], &fds)) {
				if((ret = read (clients[i], buffer, BUFFER_SIZE)) < 0 ) {
					handle_error("Failed to read messages from clients", false);
				} else if (ret == 0) {
					FD_CLR(clients[i], &fds);
					remove_fd (clients[i]);
					handle_error("Client got disconneted", false);
				} else {
					struct client_info *temp = get_sockaddr_by_fd(clients[i]);
					int temp_fd = clients[i];
					if (!temp)
						handle_error ("No addres is present for this fd", false);
					if (temp ->	user_connected )
						temp_fd = temp -> user_fd;

					send (temp_fd, buffer, ret, 0);
					printf("%s sent to client", buffer);
				}
			}
			i++;
		}//END of while block
	}
	return 0;
}
