#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	switch (fork())
	{
		case 0:
			printf("I am the child: pid=%d\n", getpid());
			break;
		case -1:
			perror("I farted\n");
			break;

		default:
			printf("I am your father, Luke: pid=%d\n", getpid());
			break;
	}
	return 0;
}
