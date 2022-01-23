#include "pipex.h"

void ft_print_fd(int fd)
{
	char buffer[1024];
	int r;

	while ((r = read(fd, buffer, 1023)) != 0)
	{
		buffer[r] = '\0';
		ft_putstr_fd(buffer, 1);
	}
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
	}
	close(fdin);
	close(pdes[1]);
	wait(&pid);
	return (pdes[0]);
}

void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst)
{
	int	fdin;
	int	fdout;
	int	fdtmp;

	fdin = open(infile, O_RDONLY);
	fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	while (cmd_lst->next != NULL)
	{
		fdtmp = run_cmd_to_fd(fdin, cmd_lst->cmd);
		dup2(fdtmp, fdin);
		close(fdtmp);
		cmd_lst = cmd_lst->next;
		//cmd_lst = ft_lstfreenext(cmd_lst);
	}
	fdtmp = run_cmd_to_fd(fdin, cmd_lst->cmd);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	ft_print_fd(fdtmp);
	close(fdtmp);
	//ft_lstfreenext(cmd_lst);
}
