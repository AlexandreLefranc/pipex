#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	int a = 56;
	printf("%d\n", (a >> 32) % 2);
	(void)argc;
	(void)argv;
	(void)envp;
}
