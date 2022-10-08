#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_line(char *str)
{
    /* save the start of str for later */
    char *start = str;
    int readChar = 0;

    /* reading each char into str */
    while ((readChar = getchar()) != '\n')
        *(str++) = readChar;
    *str = '\0';

    /* start going through the string to determine if it is integer */
    str = start;
    /* skip leading space */
    while (isspace(*str))
        str++;

    /* check the first non-space char */
    if (!isdigit(*str) &&
            *str != '+' &&
            *str != '-')
        return 0;
    str++;

    /* check the rest of the string, it must all be digit */
    int isAllZero = 1;
    while (*str != '\0')
    {
        if (!isdigit(*str))
            return 0;
        if (*str != '0')
            isAllZero = 0;
        str++;
    }

    if (isAllZero)
        return 1;
    else
        return (atoi(start) != 0);
}
