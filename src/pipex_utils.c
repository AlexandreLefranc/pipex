/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:09:29 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/24 03:25:22 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_strtabfree(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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

void	ft_lstprint(t_cmd *lst)
{
	char	**cmd;

	while (lst != NULL)
	{
		cmd = lst->cmd;
		while (*cmd != NULL)
		{
			ft_putendl_fd(*cmd, 1);
			cmd++;
		}
		ft_putendl_fd("", 1);
		lst = lst->next;
	}
}
