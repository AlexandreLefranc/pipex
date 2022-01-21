#include "libft.h"
#include <stdio.h>

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

int	main(void)
{
	char *tab[] = {"path", "to", "file", NULL};

	printf("%zu\n", ft_strtablen(tab));
	printf("%zu\n", ft_strtabsize(tab));
	printf("%s\n", ft_strtabjoin(tab, "///"));
}
