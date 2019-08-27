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
    char buf[16];
    char buf2[] = "privet\n";
    int sock;
    struct sockaddr_un server, client;
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SERVER_PATH);
    client.sun_family = AF_UNIX;
    strcpy(client.sun_path, CLIENT_PATH);
    unlink(SERVER_PATH);
    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    recvfrom(sock, buf, 16, 0, NULL, NULL);
    printf("%s", buf);
    sendto(sock, buf2, sizeof(buf2), 0, (struct sockaddr*)&client, sizeof(client));
    unlink(CLIENT_PATH);
    close(sock);
    exit(0);
}
