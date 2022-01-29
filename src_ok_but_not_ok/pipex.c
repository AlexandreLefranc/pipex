/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:10:19 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/24 03:36:47 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// clangc src2/* libft.a -L. -Iinclude -Ilibft/include
// ./a.out infile.txt "ls -l -a" "wc -l" outfile.txt

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_lst;

	check_input(argc, argv);
	cmd_lst = parse_input(argc, argv, envp);
	run_pipex(argv[1], argv[argc - 1], cmd_lst, envp);
	return (0);
}
