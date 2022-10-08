#include "child_stuff.h"
#include "parent_stuff.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_CHILD 2

int main()
{
    pid_t child[ NUM_CHILD ];
    int wstatus[ NUM_CHILD ];

    int fork_count = 0;
    for (; fork_count < NUM_CHILD; fork_count++)
    {
        child[ fork_count ] = fork();

        if (child[ fork_count ] == -1) // failure to fork
        {
            fprintf(stderr, "fork() [%d] failed\n", fork_count);
            exit(EXIT_FAILURE);
        }
        if (child[ fork_count ] == 0) // is child
        {
            break;
        }
        else // is parent
        {} // continue to fork more child
    }

    if (fork_count == NUM_CHILD) // is parent
    {
        int all_succeeded = 1; // is 0 if any child fails
        // wait until all child is finish, checking continuously
        do
        {
            for (int i = 0; i < NUM_CHILD; i++)
            {
                pid_t w = waitpid(child[ i ], &wstatus[ i ], WNOHANG);
                if (w == -1)
                {
                    fprintf(stderr, "waitpid() [%d] failed\n", i);
                    exit(EXIT_FAILURE);
                }

                if (WIFEXITED(wstatus[ i ]))
                {
                    if (WEXITSTATUS(wstatus[ i ]) == EXIT_FAILURE)
                    {
                        fprintf(stderr, "process [%d] failed\n", i);
                        all_succeeded = 0;
                    }
                    else
                    {
                        fprintf(stdout, "process [%d] succeeded\n", i);
                    }
                    fork_count--;
                }
            }
        } while (fork_count > 0);

        if (all_succeeded)
        {
            do_parent_stuff();
        }
        else
        {
            printf("Some child process has failed\n");
            exit(EXIT_FAILURE);
        }
    }
    else // is child
    {
        do_child_stuff();
    }

    return EXIT_SUCCESS;
}
