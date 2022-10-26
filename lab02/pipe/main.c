#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pipefd[2];
    int return_status;
    pid_t pid;

    char mess[20] = "Hello";
    char read_mess[20];
    return_status = pipe(pipefd);
    if (return_status == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    // assume fork() succeed
    if (pid == 0)
    {
        // child
        read(pipefd[0], read_mess, sizeof(read_mess));
        printf("child: %s\n", read_mess);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // parent
        write(pipefd[1], mess, sizeof(mess));
        exit(EXIT_SUCCESS);
    }
}
