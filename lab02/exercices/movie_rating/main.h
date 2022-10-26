#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHARE_MEM_KEY 0x123
#define SEMAPHORE_NAME "/semname"
#define NUM_CHILD 2
#define NUM_MOVIE 1682
#define FILE_NAME_LEN_MAX 256
