#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_BUFFER_SIZE 30
#define INT_ARR_SIZE 50

int readline(FILE *stream, char *str)
{
    int count = 0;
    int c;
    while ((c = fgetc(stream)) != EOF)
    {
        if (c == '\n')
            break;
        *(str++) = c;
        count++;
    }
    *str = '\0';

    if (ferror(stream))
    {
        fprintf(stderr, "I/O error when reading\n");
        return -1;
    }

    return count;
}

int readNumberArray(FILE *stream, int *arr)
{
    /* hell broke loose when there is more than STR_BUFFER_SIZE char to read */
    char *str = malloc(STR_BUFFER_SIZE * sizeof(char));

    int count = 0;
    while (readline(stream, str) > 0)
        arr[count++] = atoi(str);

    free(str);
    return count;
}

int main()
{
    char *filename = "numbers.txt";
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file \"%s\"\n", filename);
        return EXIT_FAILURE;
    }

    /* hell broke loose when there is more than INT_ARR_SIZE number to read */
    int *arr = malloc(INT_ARR_SIZE * sizeof(int));
    int arrSize = readNumberArray(fp, arr);
    printf("Total count: %d\n", arrSize);

    int count = 0;
    pid_t pid = fork();
    if (pid > 0)
    {
        /* parent */
        for (int i = 0; i < arrSize; i++)
            if (arr[i] % 2 == 0)
                count++;
        wait(NULL);
        printf("Div by 2: %d\n", count);
    }
    if (pid == 0)
    {
        /* child */
        for (int i = 0; i < arrSize; i++)
            if (arr[i] % 3 == 0)
                count++;
        printf("Div by 3: %d\n", count);

    }
    else if (pid == -1)
    {
        fprintf(stderr, "Error fork() new process\n");
        return EXIT_FAILURE;
    }

    free(arr);

    return EXIT_SUCCESS;
}
