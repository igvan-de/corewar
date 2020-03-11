/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_zjmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 17:29:50 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:22:01 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_cursor *cursor, t_env *env)
{
	short	arg;
	int		rel_pos;

	if (cursor->carry == 0)
		move_cursor(cursor, env);
	else
	{
		env->datamap[cursor->position].cursor = 0;
		arg = get_tind(env, modi(cursor->position + 1));
		rel_pos = arg % IDX_MOD;
		cursor->position = modi(cursor->position + rel_pos);
		env->datamap[cursor->position].cursor = 1;
		cursor->op_code = 0;
	}
}
