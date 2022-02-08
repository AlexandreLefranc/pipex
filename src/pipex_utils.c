/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:09:29 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/02 07:18:29 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstadd_back2(t_cmd **alst, t_cmd *new)
{
	t_cmd	*lst;

	if (new == NULL)
		return ;
	if (alst == NULL || *alst == NULL)
	{
		*alst = new;
		return ;
	}
	lst = *alst;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

t_cmd	*ft_lstfreenext(t_cmd *cmd_lst)
{
	t_cmd	*old_cmd;

	old_cmd = cmd_lst;
	cmd_lst = cmd_lst->next;
	ft_strtabfree(old_cmd->cmd);
	free(old_cmd);
	return (cmd_lst);
}

void	ft_lstfree(t_cmd *cmd_lst)
{
	while (cmd_lst != NULL)
		cmd_lst = ft_lstfreenext(cmd_lst);
}

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

void	ft_perror_exit(char const *errmsg, int errnumber)
{
	perror(errmsg);
	exit(errnumber);
}
