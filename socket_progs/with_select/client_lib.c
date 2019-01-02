#include "header.h"

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
