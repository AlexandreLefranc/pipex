/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:09:29 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/24 00:09:36 by alefranc         ###   ########.fr       */
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

void	ft_strtabfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
