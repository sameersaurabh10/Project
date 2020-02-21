#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 250



void *client_thread(void *des)
{
	char buffer[MAX];
	int cli_des = *(int *)des, size;
	
	printf("client des = %d\n", cli_des);
	if(send(cli_des,"welcome", sizeof("welcome"), 0) == -1) {
		printf("sending Welcome Failed\n");
		return 0;
	}
	while(1) {
		size = recv(cli_des, buffer, MAX, 0); 
		buffer[size] = '\0';
		printf("%s\n", buffer);
		fgets(buffer, MAX, stdin);
		send(cli_des, buffer, sizeof(buffer), 0);
	}
	
	pthread_exit(0);


}

int main(int argc, char *argv[])
{
	int sock_des, len, cli_des;
	struct sockaddr_in server, client;


	sock_des = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(40000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(struct sockaddr_in);
	if (bind(sock_des, (struct sockaddr *)&server, len) == -1) {
        perror ("Unable to bind the address to sock_des..\n") ;
        exit(1);
    }
    printf ("server is ready...\n");
		
	if(listen(sock_des, 10) == -1) {
		perror("Pending queue is full.\n");
		exit(1);
	}

	pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);


	while(1) {

		if((cli_des = accept(sock_des, (struct sockaddr *)&client, &len)) == -1) {
            perror ("Unable to connect...\n");
            exit (1);
        }

		printf ("Connected by...\n");
        printf ("Ip address : %s\n", inet_ntoa(client.sin_addr));
        printf ("Port number : %u\n", client.sin_port);
		printf ("Descriptor: %d\n", cli_des);
		printf ("client fd : %d\n", cli_des);
		if( pthread_create(&tid, &attr, client_thread, (void *)&cli_des) < 0) {
			printf("Thread creation failed\n");
			return 0;
		}
		
		
	}

	return 0;

}

