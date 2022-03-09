/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:21:26 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/09 16:18:26 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*s2;

	s2 = (char *)s;
	i = 0;
	while (i < n)
	{
		s2[i] = c;
		i++;
	}
	return (s);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb * size > 2147483647)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	DEBUG_PRINT("malloc(): %p\n", ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	*ft_calloc_debug(size_t nmemb, size_t size, char *msg)
{
	void	*ptr;

	if (nmemb * size > 2147483647)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	dprintf(2, "malloc %p: %s\n", ptr, msg);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_free_debug(void *ptr, char *msg)
{
	dprintf(2, "free %p: %s", ptr, msg);
	free(ptr);
}
