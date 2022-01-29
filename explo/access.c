/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:48:41 by alefranc          #+#    #+#             */
/*   Updated: 2022/01/29 13:03:02 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	int access_return;
	int error;
	char *file = "rdonly.txt";

	access_return = access(file, W_OK);
	error = errno;
	printf("errno = %d, errmsg = %s\n", error, strerror(error));
	printf("access return = %d\n", access_return);
}

int main()
{
	int access_return;
	int error;
	char *file = "rdonly.txt";

	access_return = access(file, W_OK);
	error = errno;
	printf("errno = %d, errmsg = %s\n", error, strerror(error));
	printf("access return = %d\n", access_return);
}
