#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>


uint32_t get_server_ip() {
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	// I want to get an IPv4 IP address 
	ifr.ifr_addr.sa_family = AF_INET;

	// I want IP address attached to "eth0" or  "wlan0" 
	strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);

	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);

	//printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	uint32_t addr = ntohl(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
	//printf("addr: %d.%d.%d.%d\n", (addr & 0xff000000) >> 24, (addr & 0x00ff0000) >> 16, (addr & 0x0000ff00) >> 8, (addr & 0x000000ff));
	return addr;
}


int main() {
	// int fd;
	// struct ifreq ifr;

	// fd = socket(AF_INET, SOCK_DGRAM, 0);

	// // I want to get an IPv4 IP address 
	// ifr.ifr_addr.sa_family = AF_INET;

	// // I want IP address attached to "eth0" or  "wlan0" 
	// strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);

	// ioctl(fd, SIOCGIFADDR, &ifr);

	// close(fd);

	// printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	// uint32_t addr = ntohl(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr);
	// printf("addr: %d.%d.%d.%d\n", (addr & 0xff000000) >> 24, (addr & 0x00ff0000) >> 16, (addr & 0x0000ff00) >> 8, (addr & 0x000000ff));

	return 0;
}