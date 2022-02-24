/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:45:37 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/24 17:46:48 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;

	check_input(argc, argv);
	lst = parse_input(argc, argv, envp);
	redirect_infile_to_stdin(argv[1]);
	redirect_outfile_to_stdout(argv[argc - 1]);
	plug_pipes(lst);

	t_cmd *content;
	while (lst != NULL)
	{
		content = lst->content;
		ft_strtabprint_fd(content->cmd, 2);
		dprintf(2, "content->fdin=%d\n", content->fdin);
		dprintf(2, "content->fdin_write_end=%d\n", content->fdin_write_end);
		dprintf(2, "content->fdout=%d\n", content->fdout);
		dprintf(2, "content->fdout_read_end=%d\n", content->fdout_read_end);
		dprintf(2, "content->pid=%d\n", content->pid);
		dprintf(2, "\n");
		lst = lst->next;
	}
	// run_pipex(lst, envp);
}
