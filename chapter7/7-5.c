#include "apue.h"

extern char **environ;

int main(void)
{

    for (int index = 0; environ[index] != NULL; index++)
    {
        printf("%s\n", environ[index]);
    }
    exit(0);
}