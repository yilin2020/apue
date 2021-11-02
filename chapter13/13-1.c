#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *cmd)
{
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;
    int fd0, fd1, fd2, i;
    umask(0);
    if (getrlimit(RLIMIT_NOFILE, &r1) < 0)
    {
        err_quit("%s: can't get file limit", cmd);
    }

    if ((pid = fork()) < 0)
    {
        err_quit("%s: can't fork", cmd);
    }
    else if (pid != 0)
    {
        exit(0);
    }

    setsid();

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
        err_quit("%s: can't ignore SIGHUP", cmd);
    }
    if ((pid = fork()) < 0)
    {
        err_quit("%s: can't fork", cmd);
    }
    else if (pid != 0)
    {
        exit(0);
    }

    if (chdir("/") < 0)
    {
        err_quit("%s: can't change directory to '/'", cmd);
    }
    if (r1.rlim_max == RLIM_INFINITY)
    {
        r1.rlim_max = 1024;
    }
    for (i = 0; i < r1.rlim_max; i++)
    {
        /* code */
        close(i);
    }
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int main(void)
{
    daemonize("test");
}