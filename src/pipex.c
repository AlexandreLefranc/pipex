#include "pipex.h"

void	ft_strtabprint(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
}


// clangc src/pipex.c src/check_input.c src/parse_input.c src/pipex_utils.c src/run_pipex.c libft.a -L. -Iincludes -Ilibft/include && ./a.out infile.txt "ls -l -a" "wc -l" outfile.txt

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd_lst;

	check_input(argc, argv);
	cmd_lst = parse_input(argc, argv, envp);
	run_pipex(argv[1], argv[argc - 1], cmd_lst);
	return (0);
}
