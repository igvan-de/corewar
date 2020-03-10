/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_st.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 08:53:40 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/06 08:53:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_st(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int addr;

	arg_1 = get_arg(cursor, env, encode, 1);
	if (get_type(encode, 2) == REG_CODE)
	{
		arg_2 = get_reg_num(cursor, env, encode, 2);
		cursor->registries[arg_2 - 1] = arg_1;
	}
	else if (get_type(encode, 2) == IND_CODE)
	{
		arg_2 = get_tind(env, cursor->position + 3);
		addr = arg_2  % IDX_MOD;
		write_bytes(arg_1, env, cursor, addr);
	}
}

void			op_st(t_cursor *cursor, t_env *env)
{
	unsigned char op_code;
	unsigned char encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_st(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}