/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:03:05 by alefranc          #+#    #+#             */
/*   Updated: 2022/02/14 16:06:54 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main()
{
	int fdes[2];

	for (int i = 0; i < 3; i++)
	{
		pipe(fdes);
		printf("fdes[0] = %d\n", fdes[0]);
		printf("fdes[1] = %d\n", fdes[1]);
		printf("\n");
	}
}
