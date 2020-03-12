/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_live.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 15:03:40 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:44:35 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_cursor *cursor, t_env *env)
{
	int		value;

	value = get_tdir(env, modi(cursor->position + 1));
	if (value == cursor->registries[0])
		env->player_last_alive = value * -1;
	env->live_counter++;
	cursor->last_live = env->total_cycles;
	cursor->live_counter++;
	move_cursor(cursor, env);
}
