#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main (void)
{
    int des, len;
    struct sockaddr_in server;
	char msg[100], buffer[100];


    des = socket (AF_INET, SOCK_STREAM, 0) ;
    server.sin_family = AF_INET ;
    server.sin_port = htons(40000);//Port number
    server.sin_addr.s_addr = INADDR_ANY;

    len = sizeof(struct sockaddr_in);

    if (connect(des, (struct sockaddr*)&server, len) ==-1) {
        perror("Unble to connect\n");
        exit(0);
    }

	printf("Connection Established\n");
    while(1) {
        len = recv(des, msg, sizeof(msg), 0) ;
        msg[len] = '\0';
        printf ("%s\n", msg);

        fgets(buffer, 100, stdin);
        send(des, buffer, sizeof(buffer), 0);

    }

    return 0;
}//END of main function

