#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("PID: %d\n", getpid());
	printf("Parent PID: %d\n", getppid());
	printf("Group: %d\n", getpgrp());

	return 0;
}
