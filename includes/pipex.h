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
//# include "libft.h"

// User-defined types
typedef struct s_lstcmd
{
	char	*cmd;
	void	*next;
}	t_lstcmd;

typedef struct s_files
{
	char	*infile;
	char	*outfile;
}	t_files;

// Secondaries functions
void	check_args(int ac, char **av);

// Utilities functions

#endif
