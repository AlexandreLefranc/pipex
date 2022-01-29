/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:10:22 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/24 03:38:05 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_fd(int fd)
{
	char	buffer[1024];
	int		r;

	r = read(fd, buffer, 1023);
	while (r != 0)
	{
		buffer[r] = '\0';
		ft_putstr_fd(buffer, 1);
		r = read(fd, buffer, 1023);
	}
}

void	child(int pdes[2], int fdin, char **cmd, char **envp)
{
	close(pdes[0]);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(pdes[1], STDOUT_FILENO);
	close(pdes[1]);
	execve(cmd[0], cmd, envp);
	exit(1);
}

int	parent(int pdes[2], int fdin, pid_t pid)
{
	int	exit_code;

	close(fdin);
	close(pdes[1]);
	waitpid(pid, &exit_code, 0);
	if (exit_code != 0)
		exit(exit_code / 256);
	return (pdes[0]);
}

int	run_cmd_to_fd(int fdin, char **cmd, char **envp)
{
	pid_t	pid;
	int		pdes[2];

	if (access(cmd[0], X_OK) != 0)
	{
		perror("Command not found");
		return (0);
	}
	pipe(pdes);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		child(pdes, fdin, cmd, envp);
	}
	else
	{
		return (parent(pdes, fdin, pid));
	}
	return (-1);
}

void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst, char **envp)
{
	int	fdin;
	int	fdout;
	int	fdtmp;

	fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	fdin = open(infile, O_RDONLY);
	if (fdin == -1 || fdout == -1)
		ft_perror_exit("Cannot open infile or outfile", 1);
	while (cmd_lst->next != NULL)
	{
		fdtmp = run_cmd_to_fd(fdin, cmd_lst->cmd, envp);
		dup2(fdtmp, fdin);
		cmd_lst = ft_lstfreenext(cmd_lst);
	}
	if (access(cmd_lst->cmd[0], X_OK) != 0)
	{
		ft_lstfreenext(cmd_lst);
		ft_perror_exit("Command not found", 127);
	}
	fdtmp = run_cmd_to_fd(fdin, cmd_lst->cmd, envp);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	ft_print_fd(fdtmp);
	close(fdtmp);
	ft_lstfreenext(cmd_lst);
}
