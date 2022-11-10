#include <pthread.h>
#include "stdlib.h"
#include "stdio.h"

pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;

int MAXCOUNT = 1e8;
static int count = 0;

void *f_count(void *sid)
{
    int i;
    for (i = 0; i < MAXCOUNT; i++)
    {
        pthread_mutex_lock(&mt);
        {
            count++;
        }
        pthread_mutex_unlock(&mt);
    }

    printf("Thread %s: holding %d \n", (char*) sid, count);

    return NULL;
}

int main(void)
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &f_count, "1");
    pthread_create(&thread2, NULL, &f_count, "2");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("main: holding %d\n", count);

    return 0;
}
