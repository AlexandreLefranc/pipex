/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/29 13:12:45 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

// User-defined types


// Main functions
void	check_input(int argc, char **argv);
t_cmd	*parse_input(int argc, char **argv, char **envp);
void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst, char **envp);

// Secondaries functions

// Utilities functions


#endif
