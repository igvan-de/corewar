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

void	op_live(t_cursor	*cursor, t_env *env)
{
	short one;
	short two;
	int arg_1;

//	printf("	executing instruction op_live with cursor: %i\n", cursor->id);
	one = to_2bytes(*(cursor->position + 4), *(cursor->position + 3));
	two = to_2bytes(*(cursor->position + 2), *(cursor->position + 1));
	arg_1 = to_4bytes(one, two);
	if ((unsigned char)arg_1 == (unsigned char)cursor->registries[0])
	{
		cursor->last_live = env->cycles;
		env->player_last_alive = (unsigned char)(arg_1) * -1;
		env->live_counter++;
		printf("	live --> cursor %i reported player %hhi as alive!\n", cursor->id, env->player_last_alive);
	}
	move_cursor(cursor);
	return ;
}