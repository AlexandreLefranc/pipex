#include "pipex.h"

void	check_input(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("Incorrect number of arguments. Expecting at least 4");
		exit(1);
	}
	if (access(argv[1], R_OK))
	{
		perror("Infile doesn't exist or cannot be read");
		exit(1);
	}
}
