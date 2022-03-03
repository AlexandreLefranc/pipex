/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:04 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/03 12:26:07 by alefranc         ###   ########.fr       */
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

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_perror_exit(char *msg, int error_number)
{
	perror(msg);
	exit(error_number);
}

void	ft_printfd_fd(int fd_to_read, int fd)
{
	int		fddup;
	char	buf[1024];
	ssize_t	ret;

	fddup = dup(fd_to_read);
	ret = read(fddup, buf, 1023);
	buf[ret] = '\0';
	while (ret != 0)
	{
		ft_putendl_fd(buf, fd);
		ret = read(fddup, buf, 1023);
		buf[ret] = '\0';
	}
	close(fddup);
}
