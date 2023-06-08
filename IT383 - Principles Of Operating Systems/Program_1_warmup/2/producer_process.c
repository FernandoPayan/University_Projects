#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>

int main()
{
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;
    
    /* name of the shared memory object */
    const char *name = "OS_804519952";

    /* strings written to shared memory */
    const char *message_0 = "Hello";
    const char *message_1 = "World!";

    /* shared memory file desriptor */
    int fd;

    /* pointer to shared memory object */
    char *ptr;

        /* create the shared memory object */
        fd = shm_open(name, O_CREAT | O_RDWR, 0666);

        /* Check and print the return value of shm_open*/
        if (fd == -1)
        {
            printf("The call to shm_open was not successful.\n");
            exit(-1);
        }

        /* configure the size of the shared memory object */
        int ftrun_val = ftruncate(fd, SIZE);

        /* Check and print the return value of ftruncate */
        if (ftrun_val == -1)
        {
            printf("The call to ftruncate was not successful.\n");
            exit(-1);
        }

        /* memory map the shared memory object */
        ptr = (char *)
            mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        /* Check and print the return value of mmap */
        if (ptr == MAP_FAILED)
        {
            printf("The call to mmap() was not successful.\n");
            exit(-1);
        }

        /* write to the shared memory object */
        sprintf(ptr, "%s", message_0);
        ptr += strlen(message_0);

        sprintf(ptr, "%s", message_1);
        ptr += strlen(message_1);

        return 0;
}