#include "main.h"

int main()
{
    // create a new share memory region, enough to hold sum of score and number of rating
    // child process will inherit this region handle, and update into it
    // share_mem[0] contains rating sum, share_mem[1] contains rating count
    int shmid;
    int *share_mem;

    shmid = shmget(SHARE_MEM_KEY, sizeof(int) * 2, 0644 | IPC_CREAT);
    if (shmid < 0)
    {
        fprintf(stderr, "shmget() failed\n");
        exit(EXIT_FAILURE);
    }

    share_mem = (int*) shmat(shmid, NULL, 0);
    if (share_mem == (int*) -1)
    {
        fprintf(stderr, "shmat() failed\n");
        exit(EXIT_FAILURE);
    }

    // create semaphore
    // semaphore will be used by child
    sem_t *sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED)
    {
        fprintf(stderr, "sem_open() failed\n");
        exit(EXIT_FAILURE);
    }
    sem_init(sem, 1, 1);

    // create child
    // each child will be waited until finish, then parent can do its job
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
                pid_t w = waitpid(child[ i ], &wstatus[ i ], 0);
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
            printf("Rating sum: %d\nRating count: %d\nAverage rating of all movie: %f\n",
                share_mem[0],
                share_mem[1],
                (double) share_mem[0] / share_mem[1]
            );

            if (shmdt(share_mem) == -1)
            {
                fprintf(stderr, "shmdt() of parent failed\n");
                exit(EXIT_FAILURE);
            }

            if (shmctl(shmid, IPC_RMID, 0) == -1)
            {
                fprintf(stderr, "shmctl() of parent failed\n");
                exit(EXIT_FAILURE);
            }

            if (sem_unlink(SEMAPHORE_NAME) < 0)
            {
                fprintf(stderr, "sem_unlink() of parent failed\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Some child process has failed\n");
            exit(EXIT_FAILURE);
        }
    }
    else // is child
    {
        // open separate file for each process
        char file_name[FILE_NAME_LEN_MAX];
        sprintf(file_name, "movie-100k_%d.txt", fork_count + 1);
        FILE *rating_file = fopen(file_name, "r");
        if (rating_file == NULL)
        {
            fprintf(stderr, "Open rating file [%d] failed\n", fork_count);
            _exit(EXIT_FAILURE);
        }

        int status;
        int user_id, movie_id, rating, time_stamp;
        while (1)
        {
            status = fscanf(rating_file, "%d\t%d\t%d\t%d\n",
                            &user_id, &movie_id, &rating, &time_stamp);
            if (status != EOF)
            {
                // use semaphore do protect share_mem
                sem_wait(sem);
                share_mem[0] += rating;
                share_mem[1]++;
                sem_post(sem);
            }
            else
            {
                break;
            }
        }


        if (shmdt(share_mem) == -1)
        {
            fprintf(stderr, "shmdt() [%d] failed\n", fork_count);
            _exit(EXIT_FAILURE);
        }

        sem_close(sem);
        fclose(rating_file);
    }

    return EXIT_SUCCESS;
}
