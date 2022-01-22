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
