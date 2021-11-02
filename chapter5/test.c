#include "apue.h"

int main(void)
{
    FILE *fp;
    if ((fp = fopen("example.txt", "rw+")) == NULL)
    {
        fclose(fp);
    }
}