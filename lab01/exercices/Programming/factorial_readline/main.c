#include "factorial.h"
#include "readline.h"
#include <stdio.h>
#include <stdlib.h>

#define STR_BUFFER 100

int main()
{
    /* read forever until interupted by ctrl+c*/
    char *str = malloc(STR_BUFFER * sizeof(char));
    while (1)
    {
        int isNum = read_line(str);
        if (isNum)
            printf("%d\n", factorial(atoi(str)));
        else
            printf("-1\n");
    }

    return 0;
}
