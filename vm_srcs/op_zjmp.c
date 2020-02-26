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

void	op_zjmp(t_cursor	*cursor)
{
	short arg;
	int	jump_distance;

	if (cursor->carry == 0)
		move_cursor(cursor);
	else
	{
		arg = to_2bytes(*(cursor->position + 1), *(cursor->position + 2));
		jump_distance = arg % IDX_MOD;
		cursor->position += jump_distance;
		cursor->carry = 0;
		cursor->op_code = 0;
		printf("	zjmp --> jumping to address %p which contains op_code: %hhi\n", cursor->position, *(cursor->position));
	}
}