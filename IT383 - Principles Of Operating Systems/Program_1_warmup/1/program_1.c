#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    printf("Called initial fork from line 8\n");

    if (pid == 0)
    {
        fork();
        printf("Create thread!\n");
    }
    else if (pid > 0)
    {
        fork();
        printf("Create thread!\n");
    }
}