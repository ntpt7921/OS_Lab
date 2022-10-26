#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
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

    printf("share_memory: %p\n", (void*) shm);
    if (shm != 0)
    {
        printf("shared_memeory_content: %s\n", shm);
    }

    sleep(3);

    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        return 1;
    }

    return 0;
}
