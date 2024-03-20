#include <unistd.h>
#include <stdio.h>
int main ()
{
    int pid = fork();
    if(pid == 0)
    {
        printf("proces potomny pid: %d ppid: %d\n", getpid(), getppid());
        sleep(5);
        execlp("ps", "ps", "-u", "tomasz", "--forest", NULL);
        return 0;
    }
    else
    {
        waitpid(pid, NULL, 0);
        printf("proces macierzysty pid: %d ppid: %d\n", getpid(), getppid());
        return 0;
    }
}