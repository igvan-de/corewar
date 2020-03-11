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
	int				i;
	int				addr_trig;
	unsigned int	bytes;

	i = 0;
	addr_trig = 1;
	bytes = 0;
	while (i < MEM_SIZE)
	{
		if (addr_trig == 1)
		{
			if (bytes == 0)
				printf("0x0000 : ");
			else
				printf("%#06x : ", bytes);
			bytes += 64;
			addr_trig = 0;
		}
		if (env->datamap[i].player != 0)
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
		{
			addr_trig = 1;
			ft_putchar('\n');
		}
		i++;
	}
	exit(0);
}

void				dump_pos(t_env *env)
{
	int				i;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%hhi ", env->datamap[i].player);
		fflush(stdout);
		if ((i + 1) % (128 / 2) == 0)
		{
			ft_putchar('\n');
		}
		i++;
	}
}
