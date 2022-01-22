#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"

typedef struct s_cmd
{
	char	**cmd;
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
}

void ft_print_fd(int fd)
{
	char buffer[1024];
	int r;
	int fd_dup;

	fd_dup = dup(fd);
	while ((r = read(fd_dup, buffer, 1023)) != 0)
	{
		buffer[r] = '\0';
		ft_putstr_fd(buffer, 1);
	}
	close(fd_dup);
}

int run_cmd_to_fd(int fdin, char **cmd)
{
	pid_t	pid;
	int		pdes[2];

	pipe(pdes);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		close(pdes[0]);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[1]);
		execve(cmd[0], cmd, NULL);
		ft_putendl_fd("execve failed", 1);
	}
	close(fdin);
	close(pdes[1]);
	wait(&pid);
	//printf("pdes[0] = %d\n\n", pdes[0]);
	return (pdes[0]);
}

// clangc dummy_pipex_fun.c libft.a -Ilibft/include -L. && ./a.out

int main()
{
	char	*infile = "infile.txt";
	char	*outfile = "outfile.txt";

	//char	*argv1[] = {"/bin/ls" ,"-l", NULL};
	char	*argv1[] = {"/usr/bin/sed", "s/fl/a1/g", NULL};
	char	*argv2[] = {"/usr/bin/grep", "a1", NULL};
	char	*argv3[] = {"/bin/wc", "-l", NULL};

	t_cmd	*cmd3 = malloc(sizeof(*cmd3) * 1);
	cmd3->cmd = argv3;
	cmd3->next = NULL;

	t_cmd	*cmd2 = malloc(sizeof(*cmd2) * 1);
	cmd2->cmd = argv2;
	cmd2->next = cmd3;

	t_cmd	*cmd1 = malloc(sizeof(*cmd1) * 1);
	cmd1->cmd = argv1;
	cmd1->next = cmd2;

	t_cmd	*cmd_lst = cmd1;

	pid_t	pid;

	int pdes[2];

	int fd = open(infile, O_RDONLY);
	int fd2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	int fdbis;

	pipe(pdes);

	pid = fork();

	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		// Child
		fdbis = run_cmd_to_fd(fd, cmd_lst->cmd);
		dup2(fdbis, fd);
		close(fdbis);
		cmd_lst = cmd_lst->next;

		fdbis = run_cmd_to_fd(fd, cmd_lst->cmd);
		dup2(fdbis, fd);
		close(fdbis);
		cmd_lst = cmd_lst->next;

		fdbis = run_cmd_to_fd(fd, cmd_lst->cmd);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		ft_print_fd(fdbis);
		close(fdbis);
		return (0);
	}
	else
	{
		// Parent
		wait(&pid);
	}

	// if (pid == 0)
	// {
	// 	// Child
	// 	dup2(fd, STDIN_FILENO);
	// 	dup2(pdes[1], STDOUT_FILENO);
	// 	close(fd);
	// 	close(pdes[1]);
	// 	close(pdes[0]);
	// 	execve(argv1[0], argv1, NULL);
	// 	perror("Error in execve");
	// }
	// else if (pid > 0)
	// {
	// 	// Parent
	// 	close(pdes[1]);
	// 	dup2(pdes[0], STDIN_FILENO);
	// 	close(pdes[0]);
	// 	dup2(fd2, STDOUT_FILENO);
	// 	close(fd2);
	// 	wait(&pid);
	// 	execve(argv2[0], argv2, NULL);
	// }
	// else
	// 	printf("Error :/\n");

	return (0);
}
