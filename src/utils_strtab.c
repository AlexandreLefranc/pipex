/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:59:33 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/09 16:09:56 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_strtabfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		DEBUG_PRINT("    free tab[i]: %p\n", tab[i]);
		i++;
	}
	free(tab);
	DEBUG_PRINT("free tab: %p\n\n", tab);
}

size_t	ft_strtabsize(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

size_t	ft_strtablen(char **tab)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (tab[i] != NULL)
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len);
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
	memset(joined, '\0', (tot_size + 1));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		ft_strlcat(joined, tab[i], tot_size + 1);
		if (tab[i + 1] != NULL)
		{
			ft_strlcat(joined, sep, tot_size + 1);
		}
		i++;
	}
	return (joined);
}

void	ft_strtabprint_fd(char **tab, int fd)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		write(fd, tab[i], ft_strlen(tab[i]));
		write(fd, "\n", 1);
		i++;
	}
}
