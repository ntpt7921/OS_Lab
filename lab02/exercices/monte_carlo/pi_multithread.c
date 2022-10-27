#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define NUM_THREAD 1
#define MIN_COORD ((double) -1)
#define MAX_COORD ((double) 1)
#define RADIUS ((MAX_COORD - MIN_COORD) / 2)

int count_point_total = 0;
int return_from_thread[NUM_THREAD] = { 0 };
int count_point_limit;
int count_point_thread_limit;

double rand_from(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void *generate_and_count_point(void *param)
{
    const int thread_number = (int) param;

    for (int i = 0; i < count_point_thread_limit; i++)
    {
        double x = rand_from(MIN_COORD, MAX_COORD);
        double y = rand_from(MIN_COORD, MAX_COORD);
        double d = sqrt(pow(x, 2) + pow(y, 2));
        //printf("%f, %f, %f\n", x, y, d);

        if (d <= RADIUS)
            return_from_thread[thread_number]++;
    }

    printf("Thread %d, count total = %d\n", thread_number, return_from_thread[thread_number]);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <integer_value>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (atoi(argv[1]) < 0)
    {
        fprintf(stderr, "%d must be >= 0", atoi(argv[1]));
        exit(EXIT_FAILURE);
    }

    count_point_limit = atoi(argv[1]);
    count_point_thread_limit = count_point_limit / NUM_THREAD;

    srand(time(NULL));

    pthread_t tid[NUM_THREAD];
    pthread_attr_t attr[NUM_THREAD];

    // create thread
    for (int i = 0; i < NUM_THREAD; i++)
    {
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i], &attr[i], generate_and_count_point, (void*) i);
        pthread_join(tid[i], NULL);
    }

    // sum all count
    for (int i = 0; i < NUM_THREAD; i++)
    {
        //printf("Return from thread %d: %d\n", i, return_from_thread[i]);
        count_point_total += return_from_thread[i];
    }

    double ratio = (double) count_point_total / (double) count_point_limit;

    printf("Total: %d\n", count_point_limit);
    printf("Count inside: %d\n", count_point_total);
    printf("Pi = %f\n", ratio * 4.0);

    return EXIT_SUCCESS;
}
