#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(void)
{
    int client_sockfd;
    int len;
    int result;
    struct sockaddr_in address;
    char ch = 'A';

    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8888);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    result = connect(client_sockfd, (struct sockaddr *)(&address), sizeof(address));
    if (result == -1)
    {
        perror("oops: client2");
        exit(1);
    }

    //第一次读写
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &ch, 1);
    printf("the first time: char from server = %c\n", ch);
    sleep(5);

    //第二次读写
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &ch, 1);
    printf("the second time: char from server = %c\n", ch);

    close(client_sockfd);

    return 0;
}