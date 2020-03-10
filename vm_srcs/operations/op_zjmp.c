/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_zjmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 17:29:50 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 17:29:50 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	op_zjmp changes the position of the cursor according
**	to the relative address provided as operation argument, only
**	if cursor->carry == 1. if cursor->carry == 0,
**	zjmp does not execute but instead the cursor is moved to
**	the next operation.
*/

void	op_zjmp(t_cursor *cursor, t_env *env)
{
	short	arg;
	int		rel_pos;

	if (cursor->carry == 0)
		move_cursor(cursor, env);
	else
	{
		arg = get_tind(env, modi(cursor->position + 1));
		rel_pos = arg % IDX_MOD;
		cursor->position = modi(cursor->position + rel_pos);
		cursor->op_code = 0;
	}
}
