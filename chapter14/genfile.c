#include "apue.h"
#include <fcntl.h>
int main(void)
{
    char buf[1024 * 1024];
    int index;
    for (index = 0; index < 1024 * 1024; index++)
    {
        buf[index] = 'a';
    }

    FILE *fp;
    fp = fopen("/tmp/test.txt", "w");

    for (index = 0; index < 1024 * 2 + 567; index++)
    {
        fwrite(buf, sizeof(char), sizeof(buf), fp);
    }

    fclose(fp);
    return 0;
}