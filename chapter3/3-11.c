#include "apue.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd_val;

    if (argc != 2)
    {
        err_quit("usage: a.out <descriptor#>");
    }

    if ((fd_val = fcntl(atoi(argv[1, F_GETFL]), 0)) < 0)
    {
        err_sys("fcntl error for fd %d", atoi(argv[1]));
    }
    switch (fd_val & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only");
        break;
    case O_WRONLY:
        printf("write only");
        break;
    case O_RDWR:
        printf("read write");
        break;
    default:
        err_dump("unknow access mode");
    }

    if (fd_val & O_APPEND)
    {
        printf(", append");
    }
    if (fd_val & O_NONBLOCK)
    {
        printf(", nonblocking");
    }
    if (fd_val & O_SYNC)
    {
        printf(", synchronous writes");
    }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC)
    {
        printf(", synchronous writes");
    }
#endif

    putchar('\n');
    exit(0);
}

void set_fl(int fd, int flags)
{
    int fd_val;

    if ((fd_val = fcntl(fd, F_GETFL, 0)) < 0)
    {
    }
    fd_val |= flags;

    if (fcntl(fd, F_SETFL, fd_val) < 0)
    {
    }
}