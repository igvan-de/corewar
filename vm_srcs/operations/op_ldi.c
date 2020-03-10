/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ldi.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 10:01:54 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 10:01:55 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_ldi(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int	arg_3;
	int	addr;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_reg_num(cursor, env, encode, 3);
	addr = (arg_1 + arg_2) % IDX_MOD;
	cursor->registries[arg_3 - 1] = get_tdir(env, cursor->position + addr);
}

void			op_ldi(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, env->map[modi(cursor->position + 1)], env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));;
	exec_ldi(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}