/*============================================================
 * Function will check the power supply status.				 *
 *														 	 *
 * If power supply is not there, it shut's down the system by* 
 * sending a gentle reminder(By calling shutdown)			 *
 *===========================================================*/


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#define NAME "POWER_SUPPLY_CHECK"
#define TRUE 1
#define FALSE 0

int my_syslog_init()
{
	openlog(NAME, LOG_CONS, LOG_DAEMON);
	return TRUE;
}

int my_syslog_exit()
{
	closelog();
	return TRUE;
}

void my_syslog (char *msg, int priority)
{
	syslog(priority, msg, NULL);
}
void my_closelog()
{
	my_syslog("Closing syslog...", LOG_INFO);
	closelog();
}


int main(int argc, char *argv[]) 
{
    /*Variable declaration*/    
	pid_t pid, sid;
	FILE *fp = NULL;
	char buffer[128];
	int time;
	char cmd[128];
   
	if (argc != 2) {
		my_syslog("Command line input are not correct(Read manual)", LOG_INFO);	
		exit (EXIT_FAILURE);
	}

	if ((time = atoi(atgv[1])) < 0) {
		my_syslog("Command line input are not correct(Read manual)", LOG_INFO);	
		exit (EXIT_FAILURE);

	}

	my_syslog_init();
	    
	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		my_syslog("Failed to create a child process", LOG_INFO);
		exit(EXIT_FAILURE);
	}
	/* If we got a good PID, then,we can exit the parent process. */
	if (pid > 0) {
		my_syslog("Child process created. Exiting parent process", LOG_INFO);
		exit(EXIT_SUCCESS);
	}

	/* Change the file mode mask */
	my_syslog("Unmasking...", LOG_INFO);
	umask(0);
                
               
	my_syslog("Reguesting ssid from kernel..", LOG_INFO); 
	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		/* Log the failure */
		my_syslog("Failed to get ssid from Kernel", LOG_INFO);
		exit(EXIT_FAILURE);
	}
        

        
	/* Change the current working directory */
	if ((chdir("/")) < 0) {
		my_syslog("Failed to change current working directory to root directory", LOG_INFO);
		exit(EXIT_FAILURE);
	}
        
	/* Close out the standard file descriptors */
	my_syslog ("Closing stdin, stdout and stderr descriptor", LOG_INFO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
        
	my_syslog("Starting monitor on power supply for time interval of 2 second", LOG_INFO); 
	
	while (TRUE) {
		fp = popen("cat /sys/class/power_supply/BAT1/power_now", "r");
		if (fp == NULL) {
			my_syslog("Failed to open power_now file", LOG_WARNING);
		}	
		/* Read the output a line at a time - and checks power supply is on or off. 
		 * if off calls system call shutdown the system gently*/
		while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
			if (atoi(buffer) > 0) {
				my_syslog("Power Supply stopped. Shuting down system(in 3 second)...", LOG_ERR);
				my_closelog();
				system("shutdown now");
			}
		}
		if (fp)
			pclose(fp);
		sleep(2);
	}
	exit(EXIT_SUCCESS);
}
