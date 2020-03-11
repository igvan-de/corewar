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

void		print_map(t_env *env)
{
	int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		if (env->datamap[i].player != 0)
		{
			attron(COLOR_PAIR(env->datamap[i].player));
			if (env->datamap[i].cursor == 1)
				attron(A_BOLD);
			printw("%02x ", 0xFF & env->map[i]);
			if (env->datamap[i].cursor == 1)
				attroff(A_BOLD);
			attroff(COLOR_PAIR(env->datamap[i].player));
		}
		else
			printw("%#02x ", env->map[i]);
		if (((i + 1) & ((128 / 2) - 1)) == 0)
			printw("\n");
		i++;
	}
	printw("\n");
	printw("	cycles: %u		cycle_to_die: %u	total cycles: %u	processes: %u lives: %u player last alive: %i\n", 
			env->cycles, env->cycles_to_die, env->total_cycles, env->total_cursors, env->live_counter, env->player_last_alive);
	refresh();
}
