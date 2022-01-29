/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:10:14 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/24 03:25:11 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*path_search(char *cmd, char *path)
{
	int		i;
	char	*full_pathname;
	char	**path_splitted;

	path_splitted = ft_split(path, ':');
	i = 0;
	while (path_splitted[i] != NULL)
	{
		full_pathname = ft_strjoin2(3, path_splitted[i], "/", cmd);
		if (access(full_pathname, X_OK) == 0)
		{
			ft_strfreetab(path_splitted);
			return (full_pathname);
		}
		free(full_pathname);
		i++;
	}
	ft_strfreetab(path_splitted);
	return (ft_strdup(cmd));
}

char	**format_cmd(char *fullcmd, char *path)
{
	char	**new_cmd;
	char	*expanded_cmd;

	new_cmd = ft_split(fullcmd, ' ');
	expanded_cmd = path_search(new_cmd[0], path);
	free(new_cmd[0]);
	new_cmd[0] = expanded_cmd;
	return (new_cmd);
}

int	append_lst(t_cmd **cmd_lst, char *fullcmd, char *path)
{
	t_cmd	*node;

	node = malloc(sizeof(*node) * 1);
	node->next = NULL;
	node->cmd = format_cmd(fullcmd, path);
	ft_lstadd_back2(cmd_lst, node);
	return (0);
}

t_cmd	*parse_input(int argc, char **argv, char **envp)
{
	int		i;
	t_cmd	*cmd_lst;
	char	*path;

	cmd_lst = NULL;
	path = extract_path_from_env(envp);
	i = 2;
	while (i < argc - 1)
	{
		append_lst(&cmd_lst, argv[i], path);
		i++;
	}
	return (cmd_lst);
}
