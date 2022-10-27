#ifndef POINT_H
#define POINT_H

typedef struct
{
    double x;
    double y;
} Point_t;

#define MIN_XY_COORS ((double) -1)
#define MAX_XY_COORS ((double) 1)
#define CIRCLE_RADIUS ((MAX_XY_COORS - MIN_XY_COORS) / 2)

#endif
