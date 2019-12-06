#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    sockaddr_in si_me, si_other;
    int s;
    assert((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))!=-1);
    
    int port=6000;

    int broadcast=1;

    setsockopt(s, SOL_SOCKET, SO_BROADCAST,  &broadcast, sizeof broadcast);

    memset(&si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = INADDR_ANY;

    assert(::bind(s, (sockaddr *)&si_me, sizeof(sockaddr))!=-1);

    while(1)
    {
        char buf[10000];
        unsigned slen=sizeof(sockaddr);
        recvfrom(s, buf, sizeof(buf)-1, 0, (sockaddr *)&si_other, &slen);

        printf("recv: %s\n", buf);
    } 
}