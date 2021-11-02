#include <netinet/in.h>
#include "apue.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_ADDR "127.0.0.1"
int main(void)
{
    int fd;
    int n;
    char buf[BUFSIZ];
    char rec[BUFSIZ];
    struct sockaddr_in server_addr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(8888);

    connect(fd, (struct sockaddr *)(&server_addr), sizeof(server_addr));

    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        n = write(fd, buf, strlen(buf));
        read(fd, rec, n);
        printf("%s", rec);
    }
    return 0;
}