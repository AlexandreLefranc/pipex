/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:08:39 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/09 17:14:49 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *get_path(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	ft_putendl_fd("No PATH found in environment!", 2);
	exit(1);
}

static char	*path_search(char *cmd, char *path)
{
	int		i;
	char	*full_pathname;
	char	**path_splitted;
	char	*tab_cmd[3];

	path_splitted = ft_split(path, ':');
	i = 0;
	while (path_splitted[i] != NULL)
	{
		tab_cmd[0] = path_splitted[i];
		tab_cmd[1] = cmd;
		tab_cmd[2] = NULL;
		full_pathname = ft_strtabjoin(tab_cmd, "/");
		if (access(full_pathname, X_OK) == 0)
		{
			ft_strtabfree(path_splitted);
			return (full_pathname);
		}
		ft_free_debug(full_pathname, "full_pathname");
		i++;
	}
	ft_strtabfree(path_splitted);
	return (ft_strdup(cmd));
}

static char	**get_cmd(char *fullcmd, char *path)
{
	char	**cmd;
	char	*cmd_tmp;

	cmd = ft_split(fullcmd, ' ');
	if (cmd[0] == NULL)
		return (cmd);
	if (cmd == NULL)
		ft_perror_exit("ft_split() failed", 1);
	if (ft_strchr(cmd[0], '/'))
		return (cmd);
	cmd_tmp = cmd[0];
	cmd[0] = path_search(cmd[0], path);
	ft_free_debug(cmd_tmp, "cmd_tmp");
	return (cmd);
}

static void	append_lst(t_list **lst, char *fullcmd, char *path)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc_debug(sizeof(*new_cmd), 1, "new_cmd");
	if (new_cmd == NULL)
		ft_perror_exit("malloc() failed", 1);
	new_cmd->cmd = get_cmd(fullcmd, path);
	new_cmd->fdin = -1;
	new_cmd->fdout = -1;
	new_cmd->fdin_write_end = -1;
	new_cmd->fdout_read_end = -1;
	new_cmd->pid = -1;
	ft_lstadd_back(lst, ft_lstnew(new_cmd));
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
	return (lst);
}
