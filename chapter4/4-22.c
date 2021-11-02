#include "apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nfifo, nchr, nslink, nsock, ntot;

int main(int argc, char **argv)
{
    int ret;
    if (argc != 2)
    {
        err_quit("Usage: ftw <starting-pathname>");
    }
    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nfifo + nchr + nslink + nsock;
    if (ntot == 0)
    {
        ntot = 1;
    }
    printf("regular files = %71d,%5.2f %%\n", nreg, nreg * 100 / ntot);
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4 /*file that we can't stat*/

static char *fullpath;
static size_t pathlen;

static int
myftw(char *pathname, Myfunc *func)
{
    fullpath = path_alloc(&pathlen);
    if (pathlen < strlen(pathlen))
    {
        if ((fullpath = realloc(fullpath, strlen(pathname) * 2)) == NULL)
        {
        }
    }
    return 0;
}

static int
dopath(Myfunc *func)
{
    int ret, n;
    struct stat statbuf;
    DIR *dp;
    struct dirent *dirp;
    if (lstat(fullpath, &statbuf) < 0)
    {
        return func(fullpath, &statbuf, FTW_NS);
    }
    if (S_ISDIR(statbuf.st_mode) == 0)
    {
        return func(fullpath, &statbuf, FTW_F);
    }
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
    {
        return ret;
    }

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = realloc(&fullpath, pathlen)) == NULL)
        {
            err_sys("realloc failed");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = '0';
    if ((dp = opendir(fullpath)) == NULL)
    {
        return func(fullpath, &statbuf, FTW_DNR);
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
            continue;

        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
        {
            break;
        }
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0)
    {
        err_ret("can't close directory %s", fullpath);
    }
    return 0;
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{

    return 0;
}