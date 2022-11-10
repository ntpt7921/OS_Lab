#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

pthread_mutex_t mtx;
sem_t chopstick[N];
int chopstick_left = N;

void *philosopher(void*);
void eat(int);
void think(int);

int main(void)
{
    int i, a[N];
    pthread_t tid[N];

    pthread_mutex_init(&mtx, NULL);

    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (i = 0; i < N; i++)
    {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void*) &a[i]);
    }

    for (i = 0; i < N; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return EXIT_SUCCESS;
}

void *philosopher(void *num)
{
    int phil = *((int*) num);
    printf("Philosopher %d has entered room\n", phil);

    int chop1 = phil;
    int chop2 = (phil + 1) % N;

    while (1)
    {
        printf("Philosopher %d try to take chopsticks to eat\n", phil);
        int give_up = 0;
        sem_wait(&chopstick[chop1]);

        pthread_mutex_lock(&mtx);
        chopstick_left--;
        pthread_mutex_unlock(&mtx);

        printf("Philosopher %d takes chopstick %d up\n", phil, chop1);
        if (chopstick_left == 0)
        {
            // give up chopstick
            pthread_mutex_lock(&mtx);
            chopstick_left++;
            pthread_mutex_unlock(&mtx);

            printf("Philosopher %d see there is no more chopstick, "
            "putting chopstick %d down\n", phil, chop1);
            give_up = 1;

            sem_post(&chopstick[chop1]);
        }

        if (!give_up)
        {
            sem_wait(&chopstick[chop2]);

            pthread_mutex_lock(&mtx);
            chopstick_left--;
            pthread_mutex_unlock(&mtx);

            printf("Philosopher %d takes chopstick %d up\n", phil, chop2);

            eat(phil);
            sleep(2);

            pthread_mutex_lock(&mtx);
            chopstick_left++;
            pthread_mutex_unlock(&mtx);
            sem_post(&chopstick[chop1]);

            pthread_mutex_lock(&mtx);
            chopstick_left++;
            pthread_mutex_unlock(&mtx);
            sem_post(&chopstick[chop2]);

            printf("Philosopher %d puts chopstick %d and %d down\n", phil, chop1, chop2);
        }

        think(phil);
        sleep(1);
    }

    pthread_exit(NULL);
}

void eat(int phil)
{
    printf("Philosopher %d is eating\n", phil);
}

void think(int phil)
{
    printf("Philosopher %d is thinking\n", phil);
}
