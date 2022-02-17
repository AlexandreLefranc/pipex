/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/17 16:48:20 by alefranc         ###   ########.fr       */
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
typedef struct s_cmd
{
	char	**cmd;
	int		fdin;
	int		fdout;
	int		fdin_write_end;
	int		fdout_read_end;
	pid_t	pid;
}	t_cmd;

// Main functions

// Secondaries functions

// Utilities functions

#endif
