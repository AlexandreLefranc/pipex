/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:24:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/03/09 16:19:04 by alefranc         ###   ########.fr       */
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

# include <string.h>
# include <stdarg.h>

// Macros
# define WRITE_END 1
# define READ_END 0

# define DEBUG 1
# define DEBUG_PRINT(fmt, ...) \
	do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
							__LINE__, __func__, __VA_ARGS__); } while (0)

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
	void			*content;
	struct s_list	*next;
}	t_list;

// Main functions

// Secondaries functions
void	check_input(int argc, char **argv);
t_list	*parse_input(int argc, char **argv, char **envp);
void	redirect_infile_to_stdin(char *infile);
void	redirect_outfile_to_stdout(char *outfile);
void	plug_pipes(t_list *lst, int fdin, int fdout);
void	run_pipex(t_list *lst, char **envp);

// utils_calloc
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_calloc_debug(size_t nmemb, size_t size, char *msg);
void	ft_free_debug(void *ptr, char *msg);

// utils_io
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_perror_exit(char *msg, int error_number);
void	ft_strtabprint_fd(char **tab, int fd);
void	ft_printfd_fd(int fd_to_read, int fd);

// utils_lst
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_printlst_fd(t_list *lst, int fd);
t_list	*ft_lstfreenext(t_list *lst);
void	ft_lstfree(t_list *lst);

// utils_split
char	**ft_split(char const *s, char c);

// utils_str
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);

// utils_strtab
void	ft_strtabfree(char **tab);
size_t	ft_strtablen(char **tab);
char	*ft_strtabjoin(char **tab, char *sep);
size_t	ft_strtabsize(char **tab);
void	ft_strtabprint_fd(char **tab, int fd);

// utils_wrap
void	ft_close(int fd);
void	ft_dup2(int fd1, int fd2);

#endif
