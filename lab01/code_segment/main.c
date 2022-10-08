#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int timestamp = 0;
	while (1)
	{
		printf("Time: %5d\n", timestamp++);
		sleep(1);
	}
	return 0;
}
