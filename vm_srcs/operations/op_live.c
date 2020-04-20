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

/*
**	@brief:	send a live signal
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_live is an operation function that is used by corewar champions
**	to send live signals. The player_last_alive variable of the env
**	struct is only updated if the value in the first registry matches
**	the value provided to op_live as argument.
*/

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
