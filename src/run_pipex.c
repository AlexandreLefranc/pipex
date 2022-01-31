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

int run_first_command(char *infile, char **cmd, char **envp)
{
	int		pdes[2];
	int		fdin;
	pid_t	pid;

	pipe(pdes);
	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
	{
		close(pdes[1]);
		perror(infile);
		return (pdes[0]);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pdes[0]);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[1]);
		execve(cmd[0], cmd, envp);
		perror("execve failed: command not found");
		exit(1);
	}
	else if (pid > 0)
	{
		close(pdes[1]);
		close(fdin);
		wait(NULL);
		return (pdes[0]);
	}
	else
	{
		perror("Fork failed");
		exit(1);
	}
}

int	run_next_command(int fdtmp, char **cmd, char **envp)
{
	int		pdes[2];
	pid_t	pid;

	pipe(pdes);
	pid = fork();
	if (pid == 0)
	{
		close(pdes[0]);
		dup2(fdtmp, STDIN_FILENO);
		close(fdtmp);
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[1]);
		execve(cmd[0], cmd, envp);
		perror("execve failed");
		exit(1);
	}
	else if (pid > 0)
	{
		close(pdes[1]);
		close(fdtmp);
		wait(NULL);
		return (pdes[0]);
	}
	else
	{
		perror("Fork failed");
		exit(1);
	}
}

void write_fdtmp_to_outfile(int fdtmp, char *outfile)
{
	int fdout;

	fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
	{
		perror(outfile);
		exit(1);
	}
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	ft_print_fd(fdtmp);
	close(fdtmp);
}

void write_infile_to_outfile(char *infile, char *outfile)
{
	int fdin;

	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
	{
		perror(infile);
		exit(1);
	}
	write_fdtmp_to_outfile(fdin, outfile);
}

void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst, char **envp)
{
	int fdtmp;

	if (cmd_lst == NULL)
	{
		write_infile_to_outfile(infile, outfile);
		exit(1);
	}
	fdtmp = run_first_command(infile, cmd_lst->cmd, envp);
	cmd_lst = ft_lstfreenext(cmd_lst);
	while (cmd_lst != NULL)
	{
		fdtmp = run_next_command(fdtmp, cmd_lst->cmd, envp);
		cmd_lst = ft_lstfreenext(cmd_lst);
	}
	write_fdtmp_to_outfile(fdtmp, outfile);
}
