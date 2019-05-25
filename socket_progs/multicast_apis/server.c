#include <stdio.h>
#include <stdlib.h>
#define PORTNO

void print_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
int main()
{
	struct sockaddr_in addr; 
	int fd;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		print_error("Failed to create socket");
	}

	addr.sin_fmily = AF_INET;
	addr.sin_port = PORTNO;
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		print_error("Failed to bind ip addr");
	}

	struct in_addr if_ip;
	if_ip.s_addr = 234.1.1.10;
	if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, (const void*)&if_ip \
					sizeof(if_ip))<0) 
	{
		print_error("Failed to select Multicast IP addrss group");
	}
	struct ip_mreq group;
	group.imr_interface.s_addr = 192.168.0.165;
	group.imr_multiaddr.s_addr = 231.1.1.1;
	return 0;
}
