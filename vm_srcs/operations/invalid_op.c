/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid_op.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 08:46:13 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/04 08:46:13 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


/*
**	get_max_bytes receives an op_code and returns the maximum
**	total size of this operation in bytes.
*/

static	unsigned char	get_max_bytes(unsigned char op_code, int type)
{
	if (op_code == 1 || op_code == 4)
		return (5);
	else if (op_code == 2 && type == 2)
		return (7);
	else if (op_code == 2 && type == 1)
		return (5);
	else if ( op_code == 11)
		return (7);
	else if (op_code == 9)
		return (3);
	return (0);
}

/*
**	invalid_op gets called when the cursor found a valid op_code
**	but its parameters were invalid. In this case, the cursor
**	is moved to the next operation. However, the cursor cannot
**	move more bytes than the max amount of bytes of the paremeters
**	if the op_code were valid.
*/

void	invalid_op(t_cursor *cursor, t_env *env, int type)
{
	unsigned char max_bytes;
	unsigned char	bytes;
	unsigned index;

	max_bytes = get_max_bytes(cursor->op_code, type);
	bytes = 1;
	index = modi(cursor->position + 1);
	while ((env->map[modi(index)] < 1 || 16 < env->map[modi(index)]) && bytes < max_bytes)
	{
		index++;
		bytes++;
	}
	if (type == 2 && cursor->op_code == 11)
	{
		bytes = 7;
		index = modi(cursor->position + 7);
	}
	else if (type == 1)
	{
		bytes = 2;
		index = modi(cursor->position + 2);
	}
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_invalid(cursor, env, bytes);
	cursor->position = modi(index);
	cursor->op_code = 0;
}
