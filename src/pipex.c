/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:32:46 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/15 13:32:50 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	// t_lstcmd	lstcmd;
	// t_files		files;

	(void)env;
	// int i = 0;
	// while (env[i] != NULL)
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }

	check_args(ac, av);
}
