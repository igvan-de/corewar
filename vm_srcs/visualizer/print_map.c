/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_map(t_env *env)
{
	int i;

	i = 0;
	clear();
	while (i < MEM_SIZE)
	{
		if (env->player_pos[i] != 0)
		{
			attron(COLOR_PAIR(env->player_pos[i]));
			printw("%02x ", 0xFF & env->map[i]);
			attroff(COLOR_PAIR(env->player_pos[i]));
		}
		else
			printw("%#02x ", env->map[i]);
		if ((i + 1) % (128 / 2) == 0)
			printw("\n");
		i++;
	}
	printw("\n");
	refresh();
}