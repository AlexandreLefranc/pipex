/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:31:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/03 17:06:22 by alefranc         ###   ########.fr       */
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
			ft_dup2(content->fdin, STDIN_FILENO);
			ft_close(content->fdin);
			ft_close(content->fdout_read_end);
			ft_dup2(content->fdout, STDOUT_FILENO);
			ft_close(content->fdout);
			execve(content->cmd[0], content->cmd, envp);
			ft_putstr_fd(content->cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		ft_close(content->fdin);
		ft_close(content->fdout);
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
		waitpid(content->pid, &status, 0);
		if (lst->next == NULL)
		{
			//ft_lstfree(cmd_lst);
			exit(WEXITSTATUS(status));
		}
		// wait(NULL);
		lst = lst->next;
	}
}

void	run_pipex(t_list *lst, char **envp)
{
	fork_and_run_cmd(lst, envp);
	wait_children(lst);
}
