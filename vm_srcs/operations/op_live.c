/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_live.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
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
