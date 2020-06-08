/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid_op.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void		handle_aff(t_env *env, t_byt *bytes, unsigned *index)
{
	while (env->map[modi(*index)] < 1 || 16 < env->map[modi(*index)])
	{
		if (*bytes == 6)
			break ;
		(*bytes)++;
		(*index)++;
	}
}

/*
**	@brief:	move cursor past invalid operation code
**
**	@param c		:	target cursor
**	@param env 		:	global environment struct
**	@param type		:	type of error
**
**	invalid_op gets called when a cursor tries to execute
**	and invalid operation code or encode byte of the instruction
**	is invalid. In that case, the cursor is moved to the next
**	operation without executing.
*/

void				invalid_op(t_cursor *cursor, t_env *env, int type)
{
	unsigned char	bytes;
	unsigned		index;
	unsigned char	encode;

	env->datamap[cursor->position].cursor = 0;
	bytes = 1;
	index = modi(cursor->position + 1);
	encode = env->map[modi(cursor->position + 1)];
	if (cursor->op_code == 16)
		handle_aff(env, &bytes, &index);
	else if (type == 1 || type == 2)
	{
		bytes = get_total_arg_size(
			env->map[modi(cursor->position)],
			encode) + 2;
		index = modi(cursor->position + bytes);
	}
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_invalid(cursor, env, bytes);
	cursor->position = modi(index);
	env->datamap[cursor->position].cursor = 1;
	cursor->op_code = 0;
}
