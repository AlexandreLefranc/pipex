/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plug_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:59:12 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/02 15:15:12 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	plug_pipes(t_list *lst, int fdin, int fdout)
{
	int	pdes[2];
	t_cmd *content;

	content = lst->content;
	content->fdin = fdin;
	content->fdin_write_end = -1;
	while (lst->next != NULL)
	{
		//dprintf(2, "Calling of pipe !\n");
		pipe(pdes);
		content->fdout = pdes[WRITE_END];
		content->fdout_read_end = pdes[READ_END];
		lst = lst->next;
		content = lst->content;
		content->fdin = pdes[READ_END];
		content->fdin_write_end = pdes[WRITE_END];
	}
	content->fdout = fdout;
	content->fdout_read_end = -1;
}
