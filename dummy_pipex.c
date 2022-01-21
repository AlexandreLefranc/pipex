#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**flags;
	void	*next;
}	t_cmd;

void	ft_strtabprint(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	if (tab[i] == NULL)
		ft_putendl_fd("(null)", 1);
}

// clangc dummy_pipex.c libft.a -Ilibft/include -L. && ./a.out

int main()
{
	char	*infile = "infile.txt";
	char	*outfile = "outfile.txt";

	//char	*argv1[] = {"/bin/ls" ,"-l", NULL};
	char	*argv1[] = {"/usr/bin/grep", "a1", NULL};

	pid_t	pid;

	ft_strtabprint(argv1);
	printf("Infile = %s; Outfile = %si\n\n", infile, outfile);

	int fd = open(infile, O_RDONLY);
	int fd2 = open(outfile, O_WRONLY);

	pid = fork();
	if (pid == 0)
	{
		printf("I'm the child\n");
		dup2(fd, STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		close(fd);
		close(fd2);
		execve(argv1[0], argv1, NULL);
	}
	else if (pid > 0)
	{
		wait(NULL);
		printf("I'm your father\n");
	}
	else
		printf("Error :/\n");

	return (0);
}
