#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITEMS   1
#define THREADS     1
#define LOOPS       9 * MAX_ITEMS

int buffer[MAX_ITEMS];
size_t fill = 0;
size_t use = 0;
sem_t sem_empty;
sem_t sem_full;

void put(int value);
int get();

void *producer(void *arg)
{
    int i = 0;
    size_t tid = (size_t) arg;

    for (i = 0; i < LOOPS; i++)
    {
        sem_wait(&sem_empty);
        put(i);
        sem_post(&sem_full);

        printf("Producer %ld put data %d\n", tid, i);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int temp = 0;
    size_t tid = (size_t) arg;

    while (temp != -1)
    {
        sem_wait(&sem_full);
        temp = get();
        sem_post(&sem_empty);

        printf("Consumer %ld get data %d\n", tid, temp);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(void)
{
    size_t i;
    size_t tid[THREADS];
    pthread_t producer_list[THREADS];
    pthread_t consumer_list[THREADS];

    sem_init(&sem_full, 0, 0);
    sem_init(&sem_empty, 0, MAX_ITEMS);

    for (i = 0; i < THREADS; i++)
    {
        tid[i] = i;
        pthread_create(&producer_list[i], NULL, producer, (void*) tid[i]);
        pthread_create(&consumer_list[i], NULL, consumer, (void*) tid[i]);
    }

    for (i = 0; i < THREADS; i++)
    {
        pthread_join(producer_list[i], NULL);
        pthread_join(consumer_list[i], NULL);
    }

    sem_destroy(&sem_full);
    sem_destroy(&sem_empty);

    return EXIT_SUCCESS;
}

void put(int value)
{
    buffer[fill] = value;
    fill = (fill + 1) % MAX_ITEMS;
}

int get()
{
    int temp = buffer[use];
    use = (use + 1) % MAX_ITEMS;
    return temp;
}
