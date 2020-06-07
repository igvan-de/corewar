/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sub.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			exec_sub(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int arg_3;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_reg_num(cursor, env, encode, 3);
	cursor->registries[arg_3] = arg_1 - arg_2;
	set_carry(cursor, arg_1 - arg_2);
}

/*
**	@brief:	operation: subtract two values and store the result
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_and is an operation function that can be used to
**	perform subtract operations. It receives 3 register
**	numbers and read the values stored in register 1 and 2.
**	the result of the subtraction is stored in register 3.
**	afterwards the carry is set depending on the result
**	of the operation.
*/

void			op_sub(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_sub(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
