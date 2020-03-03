/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:25:33 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 16:25:33 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	move_cursor receives a cursor and moves the position
**	to the next operation. If the operation at the current position
**	has an encoding byte, the cursor jumps arg_size + 2 bytes,
**	otherwise it jumps arg_size + 1 byte.
**
**	IMPORTANT: does not yet support jumping back to the beginning
**	if the new position exceeds the memory map.
*/

void	move_cursor(t_cursor *cursor, t_env *env)
{
	unsigned char	encode;
	unsigned char	total_arg_size;
	int				encode_flag;

	encode_flag = 0;
	if (has_encode(cursor->op_code) == 1)
		encode_flag = 1;
	if (encode_flag == 1)
	{
		encode = env->map[modi(cursor->position + 1)];
		total_arg_size = get_total_arg_size(cursor->op_code, encode);
		cursor->position = modi(cursor->position + total_arg_size + 2);
	}
	else
		cursor->position = modi(cursor->position + (get_tdir_size(cursor->op_code) + 1));
	cursor->op_code = 0;
}

void	move_cursor_encode(t_cursor *cursor, unsigned char encode)
{
	unsigned char	total_arg_size;

	total_arg_size = get_total_arg_size(cursor->op_code, encode);
	cursor->position = modi(cursor->position + total_arg_size + 2);
	cursor->op_code = 0;
}
