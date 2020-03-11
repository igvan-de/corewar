/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_cursor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:25:33 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:12:31 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	move_cursor(t_cursor *c, t_env *env)
{
	env->datamap[c->position].cursor = 0;
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op(c, env);
	c->position = modi(c->position + (get_tdir_size(c->op_code) + 1));
	env->datamap[c->position].cursor = 1;
	c->op_code = 0;
}

void	move_cursor_encode(t_cursor *c, t_env *env, BYTE encode, BYTE op_code)
{
	unsigned char	total_arg_size;

	env->datamap[c->position].cursor = 0;
	if ((env->flag_byte & (1 << 2)) == (1 << 2))
		dump_op_encode(c, env, encode, op_code);
	total_arg_size = get_total_arg_size(op_code, encode);
	c->position = modi(c->position + total_arg_size + 2);
	env->datamap[c->position].cursor = 1;
	c->op_code = 0;
}
