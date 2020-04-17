/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   invalid_op.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 08:46:13 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:19:07 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char validate_jump(unsigned char op_code, int type, unsigned char bytes)
{
	if (type == 1 && op_code == 6)
		return (6);
	if (type == 1 && op_code == 5)
		return (6);
	if (type == 1 && op_code == 4)
		return (3);
	if (type == 1 && op_code == 8)
		return (6);
	if (type == 1)
		return (2);
	if (op_code == 11 && type == 2)
		return (7);
	if (op_code == 2 && type == 2 && bytes > 7)
		return (7);
	if (op_code == 3 && type == 2)
		return (4);
	return (bytes);
}

static  void    walk_cursor_two(t_cursor *c, BYTE *bytes, unsigned *i, t_env *env)
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

static  void    walk_cursor_one(t_cursor *cursor, t_env *env, BYTE *bytes, unsigned *i)
{
    if (env->map[modi(*i - 1)] == -1)
	{
		while (env->map[modi(*i)] == -1 && cursor->op_code == 6)
		{
			(*i)++;
			(*bytes)++;
		}
	}
}

void		    invalid_op(t_cursor *cursor, t_env *env, int type)
{
	unsigned char	max_bytes;
	unsigned char	bytes;
	unsigned		index;

	env->datamap[cursor->position].cursor = 0;
	max_bytes = 25;
	bytes = 1;
	index = modi(cursor->position + 1);
	while ((env->map[modi(index)] < 1 || 16 < env->map[modi(index)]) &&
            bytes < max_bytes)
	{
		index++;
		bytes++;
	}
	bytes = validate_jump(cursor->op_code, type, bytes);
	index = modi(cursor->position + bytes);
	walk_cursor_one(cursor, env, &bytes, &index);
	if (type == 1)
        walk_cursor_two(cursor, &bytes, &index, env);
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_invalid(cursor, env, bytes);
	cursor->position = modi(index);
	env->datamap[cursor->position].cursor = 1;
	cursor->op_code = 0;
}
