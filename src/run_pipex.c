/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:31:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/01 16:22:14 by alefranc         ###   ########.fr       */
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
			dprintf(2, "dup2 %d in %d\n", content->fdin, STDIN_FILENO);
			if (content->fdin != STDIN_FILENO)
				dup2(content->fdin, STDIN_FILENO);
			if (content->fdout != STDOUT_FILENO)
				dup2(content->fdout, STDOUT_FILENO);
			// close(content->fdin);
			// close(content->fdout);
			// close(content->fdin_write_end);
			// close(content->fdout_read_end);
			dprintf(2, "execve of %s.\n", content->cmd[0]);
			exit(0);
			//execve(content->cmd[0], content->cmd, envp);
			(void)envp;
		}
		content->pid = pid;
		lst = lst->next;
	}
}

void	wait_children(t_list *lst)
{
	t_cmd	*content;
	int		status;

	while (lst != NULL)
	{
		content = lst->content;
		dprintf(2, "pid=%d\n", content->pid);
		waitpid(content->pid, &status, 0);
		lst = lst->next;
	}
}

void	run_pipex(t_list *lst, char **envp)
{
	fork_and_run_cmd(lst, envp);
	wait_children(lst);
}
