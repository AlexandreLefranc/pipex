void	run_first_cmd_child(int pdes[2], t_cmd *cmd_lst, int fdin, char **envp)
{
	close(pdes[0]);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(pdes[1], STDOUT_FILENO);
	close(pdes[1]);
	execve((cmd_lst->cmd)[0], cmd_lst->cmd, envp);
	perror("execve1 failed: command not found");
	ft_lstfree(cmd_lst);
	exit(127);
}

void	run_first_cmd_parent()
{

}

void	run_next_cmd_child()
{

}

void	run_next_cmd_parent()
{

}
