/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:02:02 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/03 16:35:31 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_calloc(1, sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst;

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

t_list	*ft_lstreverse(t_list *lst)
{
	t_list	*lst_current;
	t_list	*lst_next;
	t_list	*lst_tmp;

	if (lst == NULL)
		return (lst);
	lst_tmp = NULL;
	lst_current = lst;
	while (lst_current != NULL)
	{
		lst_next = lst_current->next;
		lst_current->next = lst_tmp;
		lst_tmp = lst_current;
		lst_current = lst_next;
	}
	return (lst_tmp);
}

void	ft_printlst_fd(t_list *lst, int fd)
{
	t_cmd *content;

	while (lst != NULL)
	{
		content = lst->content;
		ft_strtabprint_fd(content->cmd, fd);
		dprintf(fd, "content->fdin=%d\n", content->fdin);
		dprintf(fd, "content->fdin_write_end=%d\n", content->fdin_write_end);
		dprintf(fd, "content->fdout=%d\n", content->fdout);
		dprintf(fd, "content->fdout_read_end=%d\n", content->fdout_read_end);
		dprintf(fd, "content->pid=%d\n", content->pid);
		dprintf(fd, "\n");
		lst = lst->next;
	}
}
