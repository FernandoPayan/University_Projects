#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    /* creates the pipe */
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    /* fork a child process */
    pid = fork();
    
    if (pid < 0) /* error occured */
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) /* parent process */
    {
        /* close the  unused end of the pipe */
        close(fd[READ_END]);

        /* write to the pipe */
        int write_val = write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        
        /* Check the value of write */
        if (write_val == -1)
        {
            printf("Write failed\n");
            return 1;
        }

        /* close the write end of the pipe */
        close(fd[WRITE_END]);
    }
    else /* child process */
    {
        /* close the  unused end of the pipe */
        close(fd[WRITE_END]);

        /* read from the pipe */
        int read_val = read(fd[READ_END], read_msg, BUFFER_SIZE);
        if (read_val == -1)
        {
            printf("Read failed\n");
            return 1;
        }
        else
            printf("read %s\n", read_msg);

        /* close the read end of the pipe */
        close(fd[READ_END]);
    }

    return 0;
}