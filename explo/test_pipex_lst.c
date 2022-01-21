/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:59:30 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/20 14:59:32 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// clangc explo/test_pipex_lst.c -Ilibft/include -L. -lft && ./a.out a cat wc d
// clangc explo/test_pipex_lst.c -Ilibft/include -L. -lft && ./a.out infile2.txt "cat -e" "wc -l" b

typedef struct s_cmd
{
	char	**cmd;
	void	*next;
}	t_cmd;

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
	return (NULL);
}

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

void	ft_strtabprint(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	if (tab[i] == NULL)
		ft_putendl_fd("(null)", 1);
}

char	**argv_fullpath(int argc, char **argv, char *path)
{
	char	**cmds;
	int		i;

	cmds = malloc(sizeof(*cmds) * (argc - 1));
	i = 2;
	while (i < argc - 1)
	{
		cmds[i - 2] = path_search(argv[i], path);
		if (cmds[i - 2] == NULL)
		{
			ft_strfreetab(cmds);
			perror("Command unknown");
			exit(1);
		}
		i++;
	}
	cmds[i - 2] = NULL;
	return (cmds);
}

ssize_t	ft_strtablen(char **tab)
{
	size_t	i;
	size_t	count;

	if (tab == NULL)
		return (-1);
	i = 0;
	count = 0;
	while (tab[i] != NULL)
	{
		count += ft_strlen(tab[i]);
		i++;
	}
	return (count);
}

ssize_t	ft_strtabsize(char	**tab)
{
	size_t	i;

	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	*ft_strtabjoin(char **tab, char *sep)
{
	char	*joined;
	size_t	tot_size;
	size_t	i;

	if (tab == NULL || sep == NULL)
		return (NULL);
	tot_size = ft_strtablen(tab) + (ft_strtabsize(tab) - 1) * ft_strlen(sep);
	joined = ft_calloc(sizeof(*joined), tot_size + 1);
	i = 0;
	while (tab[i] != NULL)
	{
		strlcat(joined, tab[i], tot_size + 1);
		if (tab[i + 1] != NULL)
		{
			strlcat(joined, sep, tot_size + 1);
		}
		i++;
	}
	return (joined);
}

// void	_pipex(char *infile, char **cmds, char *outfile)
// {
//
// }

void	check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("Wrong usage, need at least 4 arguments");
		exit(1);
	}
	if (access(argv[1], R_OK) != 0)
	{
		perror("Cannot read infile");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**cmds;

	check_args(argc, argv);
	path = extract_path_from_env(envp);
	cmds = parse_args(argc, argv, path);
	ft_strtabprint(cmds);
	// _pipex(infile, cmds, outfile);
	return (0);
}
