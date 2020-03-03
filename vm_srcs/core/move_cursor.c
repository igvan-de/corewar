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

static	unsigned char	find_next_op(t_cursor *cursor, t_env *env)
{
	unsigned i;
	unsigned size;
	unsigned char byte;

	i = cursor->position + 2;
	byte = env->map[modi(i)];
	size = 0;
	while (byte < 1 || 16 < byte)
	{
		i++;
		byte = env->map[modi(i)];
		size++;
	}
	return (size);
}

/*
**	move_cursor receives a cursor and moves the position
**	to the next operation. If the operation at the current position
**	has an encoding byte, the cursor jumps arg_size + 2 bytes,
**	otherwise it jumps arg_size + 1 byte.
**
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
		if (valid_encode(cursor->op_code, encode, env) == 1)
		{
			if ((env->flag_byte & (1 << 2)) == (1 << 2))
				dump_op(cursor, env);
			total_arg_size = get_total_arg_size(cursor->op_code, encode);
			cursor->position = modi(cursor->position + total_arg_size + 2);
		}
		else
		{
			total_arg_size = find_next_op(cursor, env);
			if ((env->flag_byte & (1 << 2)) == (1 << 2))
				dump_op_size(cursor, env, total_arg_size);
			cursor->position = modi(cursor->position + total_arg_size + 2);
		}
	}
	else
	{
		if ((env->flag_byte & (1 << 2)) == (1 << 2))
			dump_op(cursor, env);
		cursor->position = modi(cursor->position + (get_tdir_size(cursor->op_code) + 1));
	}
	cursor->op_code = 0;
}

/*
**	move_cursor_encode is an alternative version of move_cursor
**	that gets called in operations that have the potential to 
**	overwrite their own encoding byte.
*/

void	move_cursor_encode(t_cursor *cursor, unsigned char encode)
{
	unsigned char	total_arg_size;

	total_arg_size = get_total_arg_size(cursor->op_code, encode);
	cursor->position = modi(cursor->position + total_arg_size + 2);
	cursor->op_code = 0;
}
