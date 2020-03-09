/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:04:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 11:04:59 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_sti(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char reg_num)
{
	int val;
	int arg_2;
	int	arg_3;
	int	addr;

	val = cursor->registries[reg_num - 1];
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_arg(cursor, env, encode, 3);
	addr = (arg_2 + arg_3) % IDX_MOD;
	write_bytes(val, env, cursor, addr);
}

/*
**	op_sti executes the operation sti at the current position
**	of the cursor passed as parameter. It receives a register number
**	as first argument, and writes the value stored in that register
**	to the relative address calculated as a result of:
**
**	cursor->position + (SECOND_ARGUMENT + THIRD_ARGUMENT % IDX_MOD);
**
**	if the encoding byte or the register numbers are invalid, the function
**	moves the cursor to the next operation by calling move_cursor.
*/

void			op_sti(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;
	unsigned char	reg_num;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, env->map[modi(cursor->position + 1)], env) == 0)
		return (invalid_op(cursor, env, 1));
	reg_num = env->map[modi(cursor->position + 2)];
	if (reg_num < 1 || 16 < reg_num)
		return (invalid_op(cursor, env, 2));
	exec_sti(cursor, env, encode, reg_num);
	move_cursor_encode(cursor, env, encode, op_code);
}
