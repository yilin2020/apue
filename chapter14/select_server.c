#include "apue.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{

    fd_set readfds, testfds;
    struct sockaddr_in server_address, client_address;
    int result;
    int server_len, client_len;
    int server_sockfd, client_sockfd;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(server_sockfd, (struct sockaddr *)(&server_address), sizeof(server_address));
    listen(server_sockfd, 5);
    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while (1)
    {
        int fd;
        char ch;
        int nread;
        testfds = readfds;
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        if (result < 1)
        {
            perror("server5");
            exit(1);
        }

        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &testfds))
            {
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)(&client_address), &client_len);
                    FD_SET(client_sockfd, &readfds);
                    printf("adding client on fd %d\n", client_sockfd);
                }
                else
                {
                    ioctl(fd, FIONREAD, &nread);
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("removing client on fd %d\n", fd);
                    }
                    else
                    {
                        read(fd, &ch, 1);
                        printf("serving client on fd %d\n", fd);
                        ch++;
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }

    return (0);
}