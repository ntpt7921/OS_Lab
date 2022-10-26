#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define MIN_COORD ((double) -1)
#define MAX_COORD ((double) 1)
#define RADIUS ((MAX_COORD - MIN_COORD) / 2)

double rand_from(double min, double max)
{
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int generate_and_count_point(const int point_count_max)
{
    int point_count = 0;

    for (int i = 0; i < point_count_max; i++)
    {
        double x = rand_from(MIN_COORD, MAX_COORD);
        double y = rand_from(MIN_COORD, MAX_COORD);
        double d = sqrt(pow(x, 2) + pow(y, 2));
        //printf("%f, %f, %f\n", x, y, d);

        if (d <= RADIUS)
            point_count++;
    }

    return point_count; // equivalent to pthread_exit(point_count)
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

    const int count_point_limit = atoi(argv[1]);
    srand(time(NULL));
    const int count_point_inside = generate_and_count_point(count_point_limit);

    double ratio = (double) generate_and_count_point(count_point_limit) /
        (double) count_point_limit;

    printf("Total: %d\n", count_point_limit);
    printf("Count inside: %d\n", count_point_inside);
    printf("Pi = %f\n", ratio * 4.0);

    return EXIT_SUCCESS;
}
