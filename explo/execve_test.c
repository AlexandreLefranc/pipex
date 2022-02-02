/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 04:57:11 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/02 05:29:07 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char *cmd[] = {"/usr/bin/grep", "include", NULL};
	char *infile = "execve_test.c";
	//char *outfile = "out";

	int jesuisfdin = open(infile, O_RDONLY);

	dup2(jesuisfdin, 0);
	close(jesuisfdin)
	execve(cmd[0], cmd, NULL);
}
