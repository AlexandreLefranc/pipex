/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/02 06:26:29 by alefranc         ###   ########.fr       */
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
	void	*next;
}	t_cmd;

// Main functions
void	check_input(int argc, char **argv);
t_cmd	*parse_input(int argc, char **argv, char **envp);
void	run_pipex(char *infile, char *outfile, t_cmd *cmd_lst, char **envp);

// Secondaries functions
void	run_first_cmd_child(int pdes[2], t_cmd *cmd_lst, int fdin, char **envp);
int		run_first_cmd_parent(int pdes[2], int fdin);
void	run_next_cmd_child(int pdes[2], t_cmd *cmd_lst, int fdtmp, char **envp);

// Utilities functions
void	ft_lstadd_back2(t_cmd **alst, t_cmd *new);
void	ft_strtabfree(char **tab);
t_cmd	*ft_lstfreenext(t_cmd *cmd_lst);
void	ft_lstfree(t_cmd *cmd_lst);
void	ft_print_fd(int fd);
void	ft_perror_exit(char const *errmsg, int errnumber);

#endif
