/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:10:22 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/01 16:27:36 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int run_first_command(char *infile, t_cmd *cmd_lst, char **envp)
{
	int		pdes[2];
	int		fdin;
	pid_t	pid;
	int		execve_status;

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
		execve((cmd_lst->cmd)[0], cmd_lst->cmd, envp);
		perror("execve1 failed: command not found");
		exit(127);
	}
	else if (pid > 0)
	{
		close(pdes[1]);
		close(fdin);
		waitpid(pid, &execve_status, 0);
		return (pdes[0]);
	}
	else
	{
		perror("Fork failed");
		exit(1);
	}
}

int	run_next_command(int fdtmp, t_cmd *cmd_lst, char **envp)
{
	int		pdes[2];
	pid_t	pid;
	int		execve_status;

	pipe(pdes);
	pid = fork();
	if (pid == 0)
	{
		close(pdes[0]);
		dup2(fdtmp, STDIN_FILENO);
		close(fdtmp);
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[1]);
		execve((cmd_lst->cmd)[0], cmd_lst->cmd, envp);
		perror("execve2 failed: command not found");
		ft_lstfree(cmd_lst);
		exit(127);
	}
	else if (pid > 0)
	{
		close(pdes[1]);
		close(fdtmp);
		waitpid(pid, &execve_status, 0);
		if (execve_status != 0)
		{
			ft_lstfree(cmd_lst);
			exit(execve_status / 256);
		}
		return (pdes[0]);
	}
	else
	{
		perror("Fork failed");
		exit(1);
	}
}

void write_fdtmp_to_outfile(int fdtmp, int fdout, char *outfile)
{
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

void write_infile_to_outfile(char *infile, int fdout, char *outfile)
{
	int fdin;

	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
	{
		perror(infile);
		exit(1);
	}
	write_fdtmp_to_outfile(fdin, fdout, outfile);
}

void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst, char **envp)
{
	int fdtmp;
	int fdout;

	fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_lst == NULL)
	{
		write_infile_to_outfile(infile, fdout, outfile);
		exit(1);
	}
	fdtmp = run_first_command(infile, cmd_lst, envp);
	cmd_lst = ft_lstfreenext(cmd_lst);
	while (cmd_lst != NULL)
	{
		fdtmp = run_next_command(fdtmp, cmd_lst, envp);
		cmd_lst = ft_lstfreenext(cmd_lst);
	}
	write_fdtmp_to_outfile(fdtmp, fdout, outfile);
}
