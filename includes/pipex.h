/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/15 13:24:45 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

// User-defined types
typedef struct s_cmd
{
	char	**cmd;
	void	*next;
}	t_cmd;

// Main functions
void	check_input(int argc, char **argv);
t_cmd	*parse_input(int argc, char **argv, char **envp);
void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst);

// Secondaries functions

// Utilities functions
void	ft_lstadd_back2(t_cmd **alst, t_cmd *new);

#endif
