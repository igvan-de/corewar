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

void	dump_mem(t_env *env)
{
	int i;

	ft_putstr("\n\n<------ MEMORY DUMP ------->\n\n\n");

	i = 1;
	while (i < MEM_SIZE)
	{
		if (env->map[i - 1] != 0)
		{
			printf(ANSI_COLOR_RED "%02x " ANSI_COLOR_RESET, 0xFF & env->map[i - 1]);
			fflush(stdout);
		}
		else
		{
			printf("%#02x ", env->map[i - 1]);
			fflush(stdout);
		}
		if (i % 63 == 0)
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}
