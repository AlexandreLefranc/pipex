#include "pipex.h"

void	check_args(int ac, char **av)
{
	int i;

	if (ac < 4)
	{
		perror("Incorrect number of arguments. Expecting at least 4");
		exit(1);
	}
	if (access(av[1], R_OK))
	{
		perror("Infile doesn't exist or cannot be read");
		exit(1);
	}
	if (access(av[ac - 1], W_OK))
	{
		perror("Outfile doesn't exist or cannot be written");
		exit(1);
	}
	i = 2;
	while (i < ac - 1)
	{
		if (access(av[i], X_OK))
		{
			perror("A command cannot be found");
			exit(1);
		}
		i++;
	}
}
