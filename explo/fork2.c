#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// https://linuxhint.com/c_fork_system_call/

int main() {
	pid_t forkStatus;

	forkStatus = fork();

	/* Child... */
	if (forkStatus == 0)
	{
		printf("Child is running, processing.\n");
		sleep(5);
		printf("Child is done, exiting.\n");
	}
	/* Parent... */
	else if (forkStatus != -1)
	{
		printf("Parent is waiting...\n");
		wait(NULL);
		printf("Parent is exiting...\n");
	}
	else
		perror("Error while calling the fork function");
	return 0;
}
