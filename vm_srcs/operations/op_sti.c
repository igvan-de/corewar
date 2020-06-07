/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_sti.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			exec_sti(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int	arg_3;
	int	addr;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_arg(cursor, env, encode, 3);
	addr = (arg_2 + arg_3) % IDX_MOD;
	write_bytes(arg_1, env, cursor, addr);
}

/*
**	@brief:	read a value and write it to memory
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_sti is an operation function which can be used to read
**	a value from a target registry and write it to memory.
**	alternatively, op_sti can also read values directly from memory
**	instead of registries.
**	op_sti uses an index as second argument which makes it different
**	from op_st.
*/

void			op_sti(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code,
		env->map[modi(cursor->position + 1)], env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_sti(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
