#include <unistd.h>

int main(int ac, char **av, char **envp)
{
	(void) ac;
	//(void)envp;
	execve("/bin/ls", av, envp);
}
