/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:08:39 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/21 19:42:23 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *get_path(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp);
		envp++;
	}
	ft_putendl_fd("No PATH found in environment!", 2);
	return (NULL);
}

static void	append_lst(t_list **lst, char *fullcmd, char *path)
{
	dprintf(2, "%s\n", fullcmd);
	dprintf(2, "%s\n", path);
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(*new_cmd) * 1);
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->fdin = -1;
	new_cmd->fdout = -1;
	new_cmd->fdin_write_end = -1;
	new_cmd->fdout_read_end = -1;
	new_cmd->pid = -1;
	//ft_lstadd_back(lst, new_node);
	(void)lst;
	(void)fullcmd;
	(void)path;
}

t_list	*parse_input(int argc, char **argv, char **envp)
{
	int		i;
	char	*path;
	t_list	*lst;

	path = get_path(envp);
	i = 2;
	lst = NULL;
	while (i < argc - 1)
	{
		append_lst(&lst, argv[i], path);
		i++;
	}
	return (NULL);
}
