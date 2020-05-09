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

unsigned	char	validate_jump(t_byt code, int type, t_byt bytes, t_byt e)
{
	if (type == 1 && code == 6)
		return (6);
	if (type == 1 && code == 5)
		return (6);
	if (type == 1 && code == 4)
		return (3);
	if (type == 1 && code == 8)
		return (6);
	if (type == 1 && code == 14)
		return (4);
	if (type == 1 && code == 11 && e == 0)
		return (2);
	if (type == 1 && code == 11)
		return (5);
	if (type == 1)
		return (2);
	if (code == 11 && type == 2)
		return (7);
	if (code == 2 && type == 2 && bytes > 7)
		return (7);
	if (code == 3 && type == 2)
		return (4);
	return (bytes);
}

static	void		walk_two(t_cursor *c, t_byt *bytes, unsigned *i, t_env *env)
{
	if (c->op_code == 10 && env->map[modi((*i) + 1)] == 0 &&
		env->map[modi(c->position + 1)] != 0)
	{
		while (*bytes < 4)
		{
			(*i)++;
			(*bytes)++;
		}
	}
}

static	void		walk_one(t_cursor *c, t_env *env, t_byt *bytes, unsigned *i)
{
	if (env->map[modi(*i - 1)] == -1)
	{
		while (env->map[modi(*i)] == -1 && c->op_code == 6)
		{
			(*i)++;
			(*bytes)++;
		}
	}
}

static	void		search_op(t_env *env, int max_bytes, int *bytes, int *i)
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

	env->datamap[cursor->position].cursor = 0;
	max_bytes = 25;
	bytes = 1;
	index = modi(cursor->position + 1);
	encode = env->map[modi(cursor->position + 1)];
	search_op(env, max_bytes, &bytes, &index);
	bytes = validate_jump(cursor->op_code, type, bytes, encode);
	index = modi(cursor->position + bytes);
	walk_one(cursor, env, &bytes, &index);
	if (type == 1)
		walk_two(cursor, &bytes, &index, env);
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_invalid(cursor, env, bytes);
	cursor->position = modi(index);
	env->datamap[cursor->position].cursor = 1;
	cursor->op_code = 0;
}
