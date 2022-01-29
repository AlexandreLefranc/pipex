#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void)envp;
	execve(av[1], av + 1, NULL);
	for (int i = 0; i < 127; i++)
		printf("i=%d, %s\n", i, strerror(i));
	//printf("%s\n", strerror(1));
}
