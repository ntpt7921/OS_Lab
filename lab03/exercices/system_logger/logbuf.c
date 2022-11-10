#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_LOG_LENGTH 10
#define MAX_BUFFER_SLOT 6
#define MAX_LOOPS 30

char logbuf[MAX_BUFFER_SLOT][MAX_LOG_LENGTH];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_is_flush = PTHREAD_COND_INITIALIZER;
int count;
void flushlog();

struct _args
{
    unsigned int interval;
};

void *wrlog(void *data)
{
    char str[MAX_LOG_LENGTH];
    int id = *(int*) data;

    usleep(20);
    sprintf(str, "%d", id);

    pthread_mutex_lock(&mtx);
    {
        // if buffer is full, wait until it is flushed
        while (count >= MAX_BUFFER_SLOT)
        {
            pthread_cond_wait(&buffer_is_flush, &mtx);
        }

        // buffer must not be full if this point is reached
        strcpy(logbuf[count], str);
        // this will increase count to MAX_BUFFER_SLOT
        // the condition count == MAX_BUFFER_SLOT determines if the buffer is full
        count = (count < MAX_BUFFER_SLOT)? (count + 1) : count;
    }
    pthread_mutex_unlock(&mtx);


//     printf("wrlog(): %d \n", id);

    return 0;
}

void flushlog()
{
    int i;
    char nullval[MAX_LOG_LENGTH];

//     printf("flushlog()\n");
    sprintf(nullval, "%d", -1);

    pthread_mutex_lock(&mtx);
    {
        for (i = 0; i < count; i++)
        {
            printf("Slot  %i: %s\n", i, logbuf[i]);
            strcpy(logbuf[i], nullval);
        }
        pthread_cond_broadcast(&buffer_is_flush);
    }
    pthread_mutex_unlock(&mtx);

    fflush(stdout);

    /*Reset buffer */
    count = 0;

    return;

}

void *timer_start(void *args)
{
    while (1)
    {
        flushlog();
        /*Waiting until the next timeout */
        usleep(((struct _args *) args)->interval);
    }
}

int main()
{
    int i;
    count = 0;
    pthread_t tid[MAX_LOOPS];
    pthread_t lgrid;
    int id[MAX_LOOPS];

    struct _args args;
    args.interval = 500e3;
    /*500 msec ~ 500 * 1000 usec */

    /*Setup periodically invoke flushlog() */
    pthread_create(&lgrid, NULL, &timer_start, (void*) &args);

    /*Asynchronous invoke task writelog */
    for (i = 0; i < MAX_LOOPS; i++)
    {
        id[i] = i;
        pthread_create(&tid[i], NULL, wrlog, (void*) &id[i]);
    }

    for (i = 0; i < MAX_LOOPS; i++)
        pthread_join(tid[i], NULL);

    sleep(5);

    return 0;
}
