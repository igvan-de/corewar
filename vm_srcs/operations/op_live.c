/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_live.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 15:03:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 15:03:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	op_live executes operation live at the current position of the cursor,
**	if the negated player_number stored in the first registry is equal to
**	the argument T_DIR of the live operation. Otherwise, the live operation
**	is not executed.
**
**	live is reported in the following ways:
**
**	- cursor->last_live is set to the current program cycle.
**	- env->player_last_alive is set to the actual player number.
**	- the env->live_counter for the current CYCLE_TO_DIE iteration is incremented.
*/

void	op_live(t_cursor *cursor, t_env *env)
{
	int		*ptr;

	ptr = (int *)&env->map[modi(cursor->position + 1)];
	if (*ptr == cursor->registries[0])
	{
		cursor->last_live = env->total_cycles;
		env->player_last_alive = *ptr * -1;
		env->live_counter++;
		cursor->live_counter++;
		env->player_pos[modi(cursor->position)] += 4;
	}
	move_cursor(cursor, env);
}
