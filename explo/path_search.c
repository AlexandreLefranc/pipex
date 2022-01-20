#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

// gccc path_search.c ../libft.a -I../libft && ./a.out

void	ft_strfreetab(char **tab)
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

char	*ft_strjoin2(int nb, ...)
{
	char	*joined;
	char	*joined_prev;
	int		i;
	va_list	args;

	if (nb == 0)
		return (NULL);
	va_start(args, nb);
	joined_prev = ft_strdup("");
	i = 0;
	while (i < nb)
	{
		joined = ft_strjoin(joined_prev, va_arg(args, char *));
		free(joined_prev);
		if (i != nb - 1)
		{
			joined_prev = ft_strdup(joined);
			free(joined);
		}
		i++;
	}
	va_end(args);
	return (joined);
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
		if ( access(full_pathname, X_OK) == 0 )
		{
			ft_freetab(path_splitted);
			return (full_pathname);
		}
		free(full_pathname);
		i++;
	}
	ft_freetab(path_splitted);
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

/* Test of path_search */
// int	main()
// {
// 	char *path = "/Users/alefranc/.local/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki";
//
// 	char *full_pathname = path_search("bob", path);
//
// 	printf("Full Pathname = %s\n", full_pathname);
// 	free(full_pathname);
//
// 	system("leaks a.out");
// }

/* Test of ft_strjoin2 */
// int	main()
// {
// 	char *joined = ft_strjoin2(4, "hello ", "Bien", " ou bien ?", "Ou encore!");
// 	printf("%s\n", joined);
// 	free(joined);
//
// 	joined = ft_strjoin2(1, "hello ");
// 	printf("%s\n", joined);
// 	free(joined);
//
// 	joined = ft_strjoin2(0);
// 	printf("%s\n", joined);
// 	free(joined);
//
// 	system("leaks a.out");
// }

// /* Test of extract_path_from_env */
int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	char *path = extract_path_from_env(envp);
	printf("%s\n", path);
}
