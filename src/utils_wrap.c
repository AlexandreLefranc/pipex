/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:43:36 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/03 17:06:53 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int fd)
{
	int	ret;

	if (fd == -1)
		return ;
	ret = close(fd);
	if (ret == -1)
		ft_perror_exit("close() failed", errno);
}

void	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret == -1)
		ft_perror_exit("dup2() failed", errno);
}
