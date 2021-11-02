#include <netinet/in.h>
#include "apue.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <errno.h>

int main(void)
{
    struct sockaddr_in serveraddr, clientaddr;
    int socket_fd, client_fd;
    socklen_t clienaddr_len;
    char buf[BUFSIZ], client_IP[BUFSIZ];
    int n, i;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("create socket err!");
        return -1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(8888);

    if (bind(socket_fd, (struct sockaddr *)(&serveraddr), sizeof(serveraddr)) == -1)
    {
        printf("bind error");
        return -1;
    }

    if (listen(socket_fd, 10) == -1)
    {
        printf("listen error");
        return -1;
    }
    clienaddr_len = sizeof(clientaddr);
    client_fd = accept(socket_fd, (struct sockaddr *)(&clientaddr), &clienaddr_len);
    if (client_fd == -1)
    {
        printf("accept error");
        return -1;
    }

    printf("Client Addr=>%s:%d Login\n",
           inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_IP, sizeof(client_IP)),
           ntohs(clientaddr.sin_port));

    while (1)
    {
        n = read(client_fd, buf, BUFSIZ);
        for (i = 0; i < n; i++)
        {
            buf[i] = toupper(buf[i]); /* code */
        }
        write(client_fd, buf, n);
    }
    close(socket_fd);
    close(client_fd);
    return 0;
}

int readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ((nread = read(fd, ptr, nleft)) < 0)
        {
            if (errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
        }
        else if (nread == 0)
        {
            break;
        }
        nleft -= nread;
        ptr += nread;
    }
    return n - nread;
}
