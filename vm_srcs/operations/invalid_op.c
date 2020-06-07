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

/*
**	@brief:	determine the number of bytes that the cursor needs to jump.
**
**	@param op_code		:	cursor operation code
**	@param type			:	error type
**	@param bytes		:	default number of  bytes to jump
**
**	validate_jump can alter the number of bytes to jump, depending
**	on the operation code.
*/

static	void		search_op(t_env *env, t_byt max_bytes, t_byt *bytes, int *i)
{
	while ((env->map[modi(*i)] < 1 || 16 < env->map[modi(*i)]) &&
			*bytes < max_bytes)
	{
		(*i)++;
		(*bytes)++;
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
	unsigned char	max_bytes;
	unsigned char	bytes;
	unsigned		index;
	unsigned char	encode;

//	ft_printf("	encountered invalid instruction with op_code %i", cursor->op_code);
//	if (type == 1)
//		ft_printf("operation has invalid encoding byte --> cannot parse arguments\n");
//	else if (type == 2)
//		ft_printf("operation has invalid register numbers --> cannot access registers\n");

	env->datamap[cursor->position].cursor = 0;
	max_bytes = 25;
	bytes = 1;
	index = modi(cursor->position + 1);
	encode = env->map[modi(cursor->position + 1)];
	if (type == 1)
	{
		search_op(env, max_bytes, &bytes, (int *)&index);
		index = modi(cursor->position + bytes);
	}
	else
	{
		bytes = get_total_arg_size(env->map[modi(cursor->position)], encode) + 2;
		index = modi(cursor->position + bytes);
	}
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_invalid(cursor, env, bytes);
	cursor->position = modi(index);
	env->datamap[cursor->position].cursor = 1;
	cursor->op_code = 0;
}
