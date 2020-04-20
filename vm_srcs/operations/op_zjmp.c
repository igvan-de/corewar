/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_zjmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	jump to a place in memory.
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_zjmp is an operation function which can be used to
**	jump the cursor to another place in memory. The operation
**	only executes if the carry flag of the cursor is set to
**	zero, otherwise the zjmp does not execute and the cursor
**	moves to the next operation in memory.
*/

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
