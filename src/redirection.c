/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:52:03 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/21 16:15:29 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_infile_to_stdin(char *infile)
{
	int	fdin;

	dprintf(2, "%s\n", infile);
	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
		perror(infile);
	else
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
			ft_perror_exit("dup2 failed", 1);
		close(fdin);
	}
}

void	redirect_outfile_to_stdout(char *outfile)
{
	int	fdout;

	dprintf(2, "%s\n", outfile);
	fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (fdout == -1)
		perror(outfile);
	else
	{
		if (dup2(fdout, STDIN_FILENO) == -1)
			ft_perror_exit("dup2 failed", 1);
		close(fdout);
	}
}
