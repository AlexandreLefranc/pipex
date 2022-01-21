#include <unistd.h>
#include <stdio.h>


// gccc example_execve.c && ./a.out /bin/ls -l

int main(int argc, char *argv[], char *env[])
{
	printf("My pid is: %d\n", getpid());

	if (argc > 1)
		if (execve(argv[1], argv + 1, env) == -1)
			perror("execve yo ");

	return 0;
}
