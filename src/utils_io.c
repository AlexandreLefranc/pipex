/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:04 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/23 18:31:50 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putendl_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	write(fd, str, i);
	write(fd, "\n", 1);
}

void	ft_perror_exit(char *msg, int error_number)
{
	perror(msg);
	exit(error_number);
}
