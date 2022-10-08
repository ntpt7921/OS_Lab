#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(1);
	}

	if (child_pid == 0)
	{
		printf("Hello, ");
		fflush(stdout);
	}
	else
	{
		printf("World!\n");
		fflush(stdout);
	}


	return 0;
}
