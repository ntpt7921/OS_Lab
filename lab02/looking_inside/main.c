#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int glo_init_data = 99;
int glo_noninit_data;

void print_func()
{
    int local_data = 0;
    printf("Process ID = %d\n", getpid());
    printf("Address of the process:\n");
    printf("1. global init = %p\n", (void*) &glo_init_data);
    printf("2. global noninit = %p\n", (void*) &glo_noninit_data);
    printf("3. print func = %p\n", (void*) &print_func);
    printf("4. local = %p\n", (void*) &local_data);
}

int main()
{
    print_func();
    return EXIT_SUCCESS;
}
