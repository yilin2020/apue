#include "apue.h"

int main(void)
{
    int fd;
    if ((fd = creat("dup2.text", FILE_MODE)) < 0)
    {
        err_sys("open failed!");
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        err_sys("dup2 failed!");
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        err_sys("dup2 failed!");
    }

    printf("hello");
}