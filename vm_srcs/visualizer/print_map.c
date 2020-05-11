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

static	void	print_vars(t_env *env)
{
	printw("	cycles: %u", env->cycles);
	printw("	cycle to die: %u", env->cycles_to_die);
	printw("	total cycles: %u", env->total_cycles);
	printw("	processes: %u", env->total_cursors);
	printw("	lives: %u", env->live_counter);
	printw("	player last alive: %i\n", env->player_last_alive);
}

static	void	print_byte(t_env *env, int i)
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
	if ((i + 1) % (128 / 2) == 0)
		printw("\n");
}

void			print_map(t_env *env)
{
	int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		print_byte(env, i);
		i++;
	}
	printw("\n");
	printw("\n");
	print_vars(env);
	refresh();
}
