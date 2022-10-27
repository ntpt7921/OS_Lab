#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

int pipefd1_2[ 2 ], pipefd2_1[ 2 ];
// pipefd1_2 will be from parent to child
// pipefd2_1 will be from child to parent

const char *mess_children = "From children, with love\0";
const char *mess_parent = "From parent, with love\0";

void INIT(void)
{
    srand( time(NULL) );
    if (pipe(pipefd1_2) < 0 || pipe(pipefd2_1) < 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("pipefd1_2: [ %d %d ], pipefd2_1 [ %d %d ]\n",
           pipefd1_2[0], pipefd1_2[1], pipefd2_1[0], pipefd2_1[1]);
}

void WRITE_TO_PARENT(void)
{
    ssize_t status = write(pipefd2_1[1], mess_children, strlen(mess_children));
    if (status == -1)
    {
        perror(strerror(errno));
        _exit(EXIT_FAILURE);
    }
    printf("Child send message to parent! - size %ld\n", status);
    fflush(stdout);
}

void READ_FROM_PARENT(void)
{
    char mess_buff[50];
    ssize_t status = read(pipefd1_2[0], mess_buff, strlen(mess_parent));
    if (status == -1)
    {
        perror(strerror(errno));
        _exit(EXIT_FAILURE);
    }
    printf("Child receive message from parent! - %s\n", mess_buff);
    fflush(stdout);
}

void WRITE_TO_CHILD(void)
{
    ssize_t status = write(pipefd1_2[1], mess_parent, strlen(mess_parent));
    if (status == -1)
    {
        perror(strerror(errno));
        _exit(EXIT_FAILURE);
    }
    printf("Parent send message to child! - size %ld\n", status);
    fflush(stdout);
}

void READ_FROM_CHILD(void)
{
    char mess_buff[50];
    ssize_t status = read(pipefd2_1[0], mess_buff, strlen(mess_children));
    if (status == -1)
    {
        perror(strerror(errno));
        _exit(EXIT_FAILURE);
    }
    printf("Parent receive message from child! - %s\n", mess_buff);
    fflush(stdout);
}

int main(void)
{
    INIT();
    pid_t pid = fork();

    alarm(10); // end after 10 second

    if (pid == 0)
    {
        // is parent
        while (1)
        {
            sleep(rand() % 2 + 1);
            WRITE_TO_CHILD();
            READ_FROM_CHILD();
        }
    }
    else
    {
        // probably child
        while (1)
        {
            sleep(rand() % 2 + 1);
            READ_FROM_PARENT();
            WRITE_TO_PARENT();
        }
    }

    return 0;
}
