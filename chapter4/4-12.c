#include "apue.h"

int main(void)
{
    struct stat statbuf;
    ino_t in;
    if (stat("foo", &statbuf) < 0)
    {
        err_sys("stat err for foo");
    } 
    in = statbuf.st_ino;
    printf(in);

    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {
        err_sys("chmod err for foo");
    }

    exit(0);
}