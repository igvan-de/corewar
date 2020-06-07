/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_st.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
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
		cursor->registries[arg_2] = arg_1;
	}
	else if (get_type(encode, 2) == IND_CODE)
	{
		arg_2 = get_tind(env, cursor->position + 3);
		addr = arg_2 % IDX_MOD;
		write_bytes(arg_1, env, cursor, addr);
	}
}

/*
**	@brief:	read a value and write it to memory
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_st is an operation function which can be used to read
**	a value from a target registry and write it to memory.
**	alternatively, op_st can also read values directly from memory
**	instead of registries.
*/

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
