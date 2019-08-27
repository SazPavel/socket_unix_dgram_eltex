#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define SERVER_PATH "./serv"
#define CLIENT_PATH "./cli"

int main()
{
    int sock;
    char buf[] = "HI!\n";
    char buf2[16];
    struct sockaddr_un addr, client;
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("sock");
        exit(-1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_PATH);
    client.sun_family = AF_UNIX;
    strcpy(client.sun_path, CLIENT_PATH);
    unlink(CLIENT_PATH);
    if(bind(sock, (struct sockaddr*)&client, sizeof(client)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
    recvfrom(sock, buf2, 16, 0, NULL, NULL);
    printf("%s", buf2);
    unlink(SERVER_PATH);
    close(sock);
    exit(0);
}
