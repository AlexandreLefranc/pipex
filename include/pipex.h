/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/21 18:09:37 by alefranc         ###   ########.fr       */
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

// User-defined types
typedef struct s_cmd
{
	char	**cmd;
	int		fdin;
	int		fdout;
	int		fdin_write_end;
	int		fdout_read_end;
	pid_t	pid;
}	t_cmd;

typedef struct s_list
{
	struct s_cmd	*content;
	struct s_list	*next;
}	t_list;

// Main functions

// Secondaries functions
void	redirect_infile_to_stdin(char *infile);
void	redirect_outfile_to_stdout(char *outfile);

// Utilities functions
void	ft_perror_exit(char *msg, int error_number);

#endif
