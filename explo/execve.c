#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int ac, char **av, char **envp)
{
	(void) ac;
	//(void)envp;
	execve(av[1], av + 1, envp);
	printf("%s", strerror(errno));
}
