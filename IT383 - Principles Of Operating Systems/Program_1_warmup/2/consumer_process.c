#include <stdio.h>
#include <stdlib.h>
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

    /* shared memory file desriptor */
    int fd;

    /* pointer to shared memory object */
    char *ptr;

        /* create the shared memory object */
        fd = shm_open(name, O_RDONLY, 0666);

        /* Check and print the return value of shm_open*/
        if (fd == -1)
        {
            printf("The call to shm_open was not successful.\n");
            exit(-1);
        }

        /* memory map the shared memory object */
        ptr = (char *)
            mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

        /* Check and print the return value of mmap */
        if (ptr == MAP_FAILED)
        {
            printf("The call to mmap() was not successful.\n");
            exit(-1);
        }

        /* read from the shared memory object */
        printf("%s", (char *)ptr);

        /* remove the shared memory object */
        int unlink_val = shm_unlink(name);
        if (unlink_val == -1)
        {
            printf("The call to shm_unlink was not successful.\n");
            exit(-1);
        }

        return 0;
}