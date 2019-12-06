#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "debug.h"

typedef struct message
{
    uint32_t id;
    uint32_t ip;
    uint32_t port;
} message_t;


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


int main(int argc, char **argv) {
    cat::debug d;
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock <= 0) {
        d.die("bad socket");    
    }

      // set socket options enable broadcast
    int broadcastEnable = 1;
    int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if (ret) {
        d.error("Error: Could not open set socket to broadcast mode");
        close(sock);
        return 1;
    }

     // Configure the port and ip we want to send to
    struct sockaddr_in broadcastAddr;
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "255.255.255.255", &broadcastAddr.sin_addr);
    broadcastAddr.sin_port = htons(6000);
    
    message_t msg;
    msg.ip = get_server_ip();
    msg.port = 50739;
    msg.id = 123;

    ret = sendto(sock, (void*) &msg, sizeof(msg), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
    if (ret < 0) {
        d.error("Error: Could not open send broadcast.");
        close(sock);
        return 1;
    }
    
    close(sock);
}


// int main(int argc, char **argv) {
//     cat::debug d;
//     int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
//     if (sock <= 0) {
//         d.die("bad socket");    
//     }

//       // set socket options enable broadcast
//     int broadcastEnable = 1;
//     int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
//     if (ret) {
//         d.error("Error: Could not open set socket to broadcast mode");
//         close(sock);
//         return 1;
//     }

//      // Configure the port and ip we want to send to
//     struct sockaddr_in broadcastAddr;
//     memset(&broadcastAddr, 0, sizeof(broadcastAddr));
//     broadcastAddr.sin_family = AF_INET;
//     inet_pton(AF_INET, "255.255.255.255", &broadcastAddr.sin_addr);
//     broadcastAddr.sin_port = htons(6000);
    
//     char *request = "message from ios by c";
//     ret = sendto(sock, request, strlen(request), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
//     if (ret < 0) {
//         d.error("Error: Could not open send broadcast.");
//         close(sock);
//         return 1;
//     }
    
//     close(sock);
// }