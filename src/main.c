/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:45:37 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/21 19:05:17 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	//t_list	*lst;

	check_input(argc, argv);
	parse_input(argc, argv, envp);
	//redirect_infile_to_stdin(argv[1]);
	//redirect_outfile_to_stdout(argv[argc]);
	// plug_pipes(lst);
	// run_pipex(lst);
}
