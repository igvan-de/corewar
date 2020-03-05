/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_add.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 09:57:08 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/05 09:57:08 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_add(t_cursor *cursor, t_env *env)
{
	int val1;
	int val2;
	unsigned char reg_num;

	reg_num = env->map[modi(cursor->position + 2)];
	val1 = cursor->registries[reg_num - 1];
	reg_num = env->map[modi(cursor->position + 3)];
	val2 = cursor->registries[reg_num - 1];
	reg_num = env->map[modi(cursor->position + 4)];
	cursor->registries[reg_num - 1] = val1 + val2;
	set_carry(cursor, val1 + val2);
}

void		op_add(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_add(cursor, env);
	move_cursor_encode(cursor, env, encode, op_code);
}