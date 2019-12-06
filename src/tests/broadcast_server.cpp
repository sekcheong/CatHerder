
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "debug.h"

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
    
    char *request = "message from ios by c";
    ret = sendto(sock, request, strlen(request), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
    if (ret < 0) {
        d.error("Error: Could not open send broadcast.");
        close(sock);
        return 1;
    }
    
    close(sock);
}