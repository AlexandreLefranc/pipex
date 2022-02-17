/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:04:22 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/17 17:07:05 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(int argc, char *argv)
{
	(void)argv;
	if (argc < 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		ft_putendl_fd("Example: ./pipex Makefile \"ls -l\" \"wc -l\" out.txt ", 2);
		exit(1);
	}
}
