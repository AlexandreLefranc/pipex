/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:45:37 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/02 15:37:29 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	int		fdin;
	int		fdout;

	check_input(argc, argv);
	lst = parse_input(argc, argv, envp);

	fdin = open(argv[1], O_RDONLY);
	if (fdin == -1)
		perror(argv[1]);
	fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		perror(argv[argc - 1]);

	plug_pipes(lst, fdin, fdout);

	// ft_printlst_fd(lst, 2);
	run_pipex(lst, envp);
}
