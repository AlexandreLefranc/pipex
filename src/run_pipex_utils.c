/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 06:24:13 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/02 06:24:14 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_first_cmd_child(int pdes[2], t_cmd *cmd_lst, int fdin, char **envp)
{
	close(pdes[0]);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(pdes[1], STDOUT_FILENO);
	close(pdes[1]);
	execve((cmd_lst->cmd)[0], cmd_lst->cmd, envp);
	perror("execve1 failed: command not found");
	ft_lstfree(cmd_lst);
	exit(127);
}

int	run_first_cmd_parent(int pdes[2], int fdin)
{
	close(pdes[1]);
	close(fdin);
	wait(NULL);
	return (pdes[0]);
}

void	run_next_cmd_child(int pdes[2], t_cmd *cmd_lst, int fdtmp, char **envp)
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

// void	run_next_cmd_parent()
// {
//
// }
