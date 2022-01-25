#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void) ac;
	//(void)envp;
	execve(av[1], av, envp);
	perror("perror");
}
