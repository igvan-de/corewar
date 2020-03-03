/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_mem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 13:35:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/21 13:35:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	dump_mem prints the current state of the memory map
**	to stdout.
*/

void				dump_mem(t_env *env)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (env->player_pos[i] != 0)
		{
			printf("%02x ", 0xFF & env->map[i]);
			fflush(stdout);
		}
		else
		{
			printf("%#02x ", env->map[i]);
			fflush(stdout);
		}
		if ((i + 1) % (128 / 2) == 0)
			ft_putchar('\n');
		i++;
	}
	exit (0);
}
