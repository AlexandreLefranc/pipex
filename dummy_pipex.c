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

	char	*argv2[] = {"/bin/wc", "-l", NULL};

	pid_t	pid;

	int pdes[2];

	ft_strtabprint(argv1);
	printf("Infile = %s; Outfile = %si\n\n", infile, outfile);

	int fd = open(infile, O_RDONLY);
	int fd2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	pipe(pdes);
	printf("pdes0 = %d\npdes1 = %d\n\n", pdes[0], pdes[1]);

	pid = fork();
	if (pid == 0)
	{
		// Child
		dup2(fd, STDIN_FILENO);
		dup2(pdes[1], STDOUT_FILENO);
		close(fd);
		close(pdes[1]);
		close(pdes[0]);
		execve(argv1[0], argv1, NULL);
		perror("Error in execve");
	}
	else if (pid > 0)
	{
		// Parent
		close(pdes[1]);
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[0]);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		wait(&pid);
		execve(argv2[0], argv2, NULL);
	}
	else
		printf("Error :/\n");

	return (0);
}

// int run_cmd_to_fd(int fdin, char **cmd)
// {
// 	int	pid_t;
// 	int	pdes[2];
//
// 	pipe(pdes);
// 	pid_t = fork();
// 	if (pid_t == -1)
// 		exit(1);
// 	else if (pid_t == 0)
// 	{
// 		dup2(fdin, STDIN_FILENO);
// 		close(fdin);
// 		dup2(pdes[1], STDOUT_FILENO);
// 		close(pdes[0]);
// 		execve(cmd[0], cmd, NULL);
// 	}
// 	else
// 	{
// 		close(fdin);
// 		close(pdes[1]);
// 		wait(&pid);
// 		return (pdes[0]);
// 	}
// }
