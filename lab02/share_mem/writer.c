#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SHM_KEY 0x123

int main(void)
{
    int shmid;
    char *shm;

    shmid = shmget(SHM_KEY, 1000, 0644 | IPC_CREAT);

    if (shmid < 0)
    {
        perror("Share_memory");
        return 1;
    }
    else
    {
        printf("Share_memory: %d\n", shmid);
    }

    shm = (char*) shmat(shmid, NULL, 0);

    if (shm == (char*) -1)
    {
        perror("shmat");
        exit(1);
    }

    sprintf(shm, "hello world\n");
    printf("shared_memeory_content: %s\n", shm);
    sleep(3);

    // detach from the share mem
    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        return 1;
    }

    // mark the shared segment to be destroyed
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("shmctl");
        return 1;
    }

    return 0;
}
