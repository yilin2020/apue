#include "apue.h"

char buf[] = "123456789\n";

int main(void)
{
    int fd;
    fd = dup(STDIN_FILENO);
    printf("fd=>%d\n", fd);
    if ((write(fd, buf, 10)) != 10)
    {
        err_sys("write error");
    }
    exit(0);
}