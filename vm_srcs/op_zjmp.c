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

void	op_zjmp(t_cursor *cursor)
{
	short	arg;
	int		rel_target_pos;

	if (cursor->carry == 0)
		move_cursor(cursor);
	else
	{
		arg = to_2bytes(*(cursor->position + 1), *(cursor->position + 2));
		rel_target_pos = arg % IDX_MOD;
		cursor->position += rel_target_pos;
		cursor->carry = 0;
		cursor->op_code = 0;
//		printf("	zjmp --> jumping to address %p which contains op_code: %hhi\n", cursor->position, *(cursor->position));
	}
}
