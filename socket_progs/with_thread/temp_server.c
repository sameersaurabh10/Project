#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 250

char *err_msg[] = {
					"503 Wrong command order: say HELO first",
                    "503 Wrong command order: say CUBE or SPHERE or CONE first",
                    "503 Wrong command order: say CUBE first",
                    "503 Wrong command order: say SPHERE first",
                    "503 Wrong command order: say CONE first",
                    "500 Command unrecognized",
					"501 syntax error in parameters"
                   };

char *res_msg[] = {
					"230 CONE ready",
					"220 SPHERE ready",
					"210 CUBE ready"
					};

char *menu[] = {
                "CUBE",
                "CONE",
                "SPHERE",
				"HELO"
				};


int cone_oper(int des)
{
	char buffer[MAX];
	char *msg = NULL;
	int size, area, radius, height;
	float hgh, vol;
	int cli_des = des;
	printf("Inside Cone\n");
	send(cli_des,res_msg[0], sizeof(res_msg[0]), 0);
	size = recv(cli_des, buffer, MAX, 0);
	buffer[size] = '\0';
	msg = (char *) malloc(MAX);

 	msg = strtok(buffer, " ");
	if(!strcmp(msg, "HGH")) {

		if((msg = strtok(NULL, " ")) != NULL) {

			area = atoi(msg);
			if((msg = strtok(NULL, " ")) != NULL) {

            	radius = atoi(msg);
				hgh = ((3 * area) /(3.14 * radius * radius));
				sprintf(msg, "%f", hgh);

				send(cli_des, msg, sizeof(msg), 0);
				return 0;
				
			} else {
				
				send(cli_des, err_msg[6], sizeof(err_msg[6]), 0);
				return -1;
			}

		} else {

			send(cli_des, err_msg[6], sizeof(err_msg[6]), 0);
			return -1;

		}
	} else if (!strcmp(msg, "VOL")) {


		 if((msg = strtok(NULL, " ")) != NULL) {

            radius = atoi(msg);
            if((msg = strtok(NULL, " ")) != NULL) {

                height = atoi(msg);

            } else {

                send(cli_des, err_msg[6], sizeof(err_msg[6]), 0);
                return -1;
            }

        } else {

            send(cli_des, err_msg[6], sizeof(err_msg[6]), 0);
            return -1;

        }

	}
		
}
int sphere_oper(int des)
{
    char buffer[MAX];
	char *msg = NULL;
    int size;
    int cli_des = des;

    send(cli_des, res_msg[1], sizeof(res_msg[1]), 0);
	size = recv(cli_des, buffer, MAX, 0);
    buffer[size] = '\0';

   msg = (char *) malloc(MAX);
	msg = strtok(buffer, " ");
 	
}
int cube_oper(int des)
{
	char buffer[MAX];
	char *msg = NULL;
	int size;
    int cli_des = des;

    send(cli_des, res_msg[2], sizeof(res_msg[2]), 0);
	size = recv(cli_des, buffer, MAX, 0);
    buffer[size] = '\0';
    msg = (char *) malloc(MAX);
	msg = strtok(buffer, " ");

}


int *client_thread(void *des)
{
	char buffer[MAX];
	char temp[MAX], temp2[MAX];

	int cli_des = *((int *)des), size = 0;
	int ret_val = 0;
	char *msg = NULL;

	printf("cli_des in thrrad = %d\n", cli_des);
	
	while(1) {
		if ((size = recv(cli_des, buffer, MAX, 0)) < 0) {
			printf("ERROR : recv function failed\n");
		} 

		printf("size : %d \n", size);
		buffer[size-1] = '\0';
		strcpy(temp, buffer);


		msg = strtok(temp, " ");
		printf("message : %s\n", msg);
		printf("temp : %s\n", temp);
		if (strcmp(msg,menu[3]) != 0) {
			send(cli_des, err_msg[0], sizeof(err_msg[0]), 0);
			continue; 
		} else {
			send(cli_des, "HELO client", sizeof("HELO client"), 0);
		}
		
		while(1) {
			memset(buffer, 0, MAX);
			if ((size = recv(cli_des, buffer, MAX, 0)) < 0) {
				printf("ERROR : recv function failed\n");
			}
			printf("size : %d\n", size);
			buffer[size-1] = '\0';

			printf("Message = %s\n", buffer);
			printf("menu[1] = %s\n", menu[1]);
			printf("size menu[1] = %ld\n", strlen(menu[1]));

			if (!strcmp(buffer, menu[1])) {
				printf("Matched with CONE\n");
			}
			printf("buffer size : %ld\n", strlen(buffer));
			printf("buffer size : %ld\n", sizeof(buffer));

//WHY THIS CMP is not working
			if (!strcmp(buffer, "MENU")) {
				send(cli_des, menu, sizeof(menu), 0);
			} else if (strcmp(buffer, menu[1]) == 0) {
				if ((ret_val =cone_oper(cli_des)) == -1)
					continue;
			} else if (!strcmp(msg, "CUBE")) {
				if ((ret_val = cube_oper(cli_des)) == -1)
					continue;
			} else if (!strcmp(msg, "SPHERE")) {
				if ((ret_val = sphere_oper(cli_des)) == -1)
					continue;
			} else {

				if (!strcmp(msg, "VOL")) {
					send(cli_des, err_msg[1], sizeof(err_msg[1]), 0);
				} else if (!strcmp(msg, "AREA")) {
					send(cli_des, err_msg[2], sizeof(err_msg[2]), 0);
				} else if (!strcmp(msg, "RAD")) {
                    send(cli_des, err_msg[3], sizeof(err_msg[3]), 0);
                } else if (!strcmp(msg, "HGH")) {
                    send(cli_des, err_msg[4], sizeof(err_msg[4]), 0);
                } else {
					send(cli_des, err_msg[5], sizeof(err_msg[5]), 0);
				}

			}

		}
		
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

		if((cli_des =accept(sock_des, (struct sockaddr *)&client, &len)) == -1)  {
            perror ("Unable to connect...\n");
            exit (1);
        }

		printf ("Connected by...\n");
        printf ("Ip address : %s\n", inet_ntoa(client.sin_addr));

		if( pthread_create(&tid, &attr, client_thread, &cli_des) < 0) {
			printf("Thread creation failed\n");
			return 0;
		}
		
		
	}

	return 0;

}

