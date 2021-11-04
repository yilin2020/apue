#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR 1024 * 1024
int main(int argc, char **argv)
{

    FILE *fdin, *fdout;

    size_t reads = 1, readn;
    char buf[COPYINCR];

    if (argc != 3)
        err_quit("usage: %s <fromfile> <tofile>", argv[0]);

    if ((fdin = fopen(argv[1], "r")) < 0)
        err_sys("can't open %s for reading", argv[1]);

    if ((fdout = fopen(argv[2], "w+")) < 0)
        err_sys("can't create %s for writing", argv[2]);

    do
    {
        reads = fread(buf, sizeof(char), sizeof(buf), fdin);
        fwrite(buf, sizeof(char), reads, fdout);
        readn += reads;
        fseek(fdin, readn, SEEK_SET);
    } while (reads > 0);

    fclose(fdin);
    fclose(fdout);
}