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

static	int	cursor_pos(t_cursor *cursor_stack, unsigned index)
{
	t_cursor *iter;

	iter = cursor_stack;
	while (iter)
	{
		if (iter->position == index)
			return (1);
		iter = iter->next;
	}
	return (0);
}

void	print_map(t_env *env)
{
	int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		if (env->player_pos[i] != 0)
		{
			if (cursor_pos(env->cursor_stack, i) == 0)
				attron(COLOR_PAIR(env->player_pos[i]));
			else 
				attron(COLOR_PAIR(9));
			printw("%02x ", 0xFF & env->map[i]);
			if (cursor_pos(env->cursor_stack, i) == 0)
				attroff(COLOR_PAIR(env->player_pos[i]));
			else
				attron(COLOR_PAIR(9)); 
			if (env->player_pos[i] > 4)
				env->player_pos[i] -= 4;
		}
		else
			printw("%#02x ", env->map[i]);
		if ((i + 1) % (128 / 2) == 0)
			printw("\n");
		i++;
	}
	printw("\n");
	printw("	cycles: %u		cycle_to_die: %u\n", env->cycles, env->cycles_to_die);
	refresh();
}
