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
	short	one;
	short	two;
	int		arg_1;

	one = to_2bytes(env->map[modi(cursor->position + 4)], env->map[modi(cursor->position + 3)]);
	two = to_2bytes(env->map[modi(cursor->position + 2)], env->map[modi(cursor->position + 1)]);
	arg_1 = to_4bytes(one, two);
	if ((unsigned char)arg_1 == (unsigned char)cursor->registries[0])
	{
		cursor->last_live = env->cycles;
		env->player_last_alive = (unsigned char)(arg_1) * -1;
		env->live_counter++;
		env->player_pos[modi(cursor->position)] +=4;
//		printf("	live --> cursor %i reported player %hhi as alive!\n", cursor->id, env->player_last_alive);
	}
	move_cursor(cursor, env);
}
