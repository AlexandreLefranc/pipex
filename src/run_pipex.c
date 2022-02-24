/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:31:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/24 17:46:40 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_and_run_cmd(t_list *lst, char **envp)
{
	pid_t	pid;
	t_cmd	*content;

	while (lst != NULL)
	{
		content = lst->content;
		pid = fork();
		if (pid < 0)
			ft_perror_exit("fork() failed", 1);
		else if (pid == 0)
		{
			dup2(content->fdin, STDIN_FILENO);
			dup2(content->fdout, STDOUT_FILENO);
			close(content->fdin);
			close(content->fdout);
			close(content->fdin_write_end);
			close(content->fdout_read_end);
			execve(content->cmd[0], content->cmd, envp)
		}
		content->pid = pid;
		lst = lst->next;
	}
}

void	run_pipex(t_list *lst)
{
	fork_and_run_cmd(lst);
	wait_children(lst);
}
