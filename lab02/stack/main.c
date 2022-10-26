#include <stdio.h>
#include <stdlib.h>

void func(unsigned long number)
{
    unsigned long local_f = number;
    printf("%2lu -> %p\n", local_f, (void*) &local_f);
    local_f--;
    if  (local_f > 0)
    {
        func(local_f);
    }
}

int main()
{
    func(10);
    return EXIT_SUCCESS;
}
