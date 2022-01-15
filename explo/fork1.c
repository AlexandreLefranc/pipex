#include <unistd.h>
#include <stdio.h>

// https://linuxhint.com/c_fork_system_call/

int main()
{
	pid_t	fork_status;

	printf("This only once\n");
	fork_status = fork();
	printf("This twice\n");

	if (fork_status == 0)
		printf("In fork_status == 0 condition, %d\n", fork_status);
	else if (fork_status != -1)
		printf("In fork_status != -1 condition, %d\n", fork_status);
	else
		printf("Something went wrong\n");
}
