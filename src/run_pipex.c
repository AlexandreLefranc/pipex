/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:31:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/03 18:01:24 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(t_cmd *content, char **envp, t_list *lst_save)
{
	ft_dup2(content->fdin, STDIN_FILENO);
	ft_close(content->fdin);
	ft_close(content->fdout_read_end);
	ft_dup2(content->fdout, STDOUT_FILENO);
	ft_close(content->fdout);
	execve(content->cmd[0], content->cmd, envp);
	ft_putstr_fd(content->cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	ft_lstfree(lst_save);
	exit(127);
}

static void	fork_and_run_cmd(t_list *lst, char **envp)
{
	pid_t	pid;
	t_cmd	*content;
	t_list	*lst_save;

	lst_save = lst;
	while (lst != NULL)
	{
		content = lst->content;
		pid = fork();
		if (pid < 0)
			ft_perror_exit("fork() failed", 1);
		else if (pid == 0)
			child(content, envp, lst_save);
		ft_close(content->fdin);
		ft_close(content->fdout);
		content->pid = pid;
		lst = lst->next;
	}
}

static void	wait_children(t_list *lst)
{
	t_cmd	*content;
	int		status;

	while (lst != NULL)
	{
		content = lst->content;
		waitpid(content->pid, &status, 0);
		lst = ft_lstfreenext(lst);
		if (lst == NULL)
			exit(WEXITSTATUS(status));
	}
}

void	run_pipex(t_list *lst, char **envp)
{
	fork_and_run_cmd(lst, envp);
	wait_children(lst);
}
