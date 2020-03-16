/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_add.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 09:57:08 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:19:25 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			exec_add(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int arg_3;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_reg_num(cursor, env, encode, 3);
	cursor->registries[arg_3 - 1] = arg_1 + arg_2;
	set_carry(cursor, arg_1 + arg_2);
}

void			op_add(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_add(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
