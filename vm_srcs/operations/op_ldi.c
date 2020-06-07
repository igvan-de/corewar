/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ldi.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			exec_ldi(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;
	int	arg_3;
	int	addr;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_arg(cursor, env, encode, 2);
	arg_3 = get_reg_num(cursor, env, encode, 3);
	addr = (arg_1 + arg_2) % IDX_MOD;
	cursor->registries[arg_3] = get_tdir(env, cursor->position + addr);
}

/*
**	@brief:	operation --> read and load a value into registry.
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_ldi is an operation function which can be used to
**	read values and store them into the registry. values can either be
**	read from memory or from registries.
**	ldi used an index with the second argument, which makes it different
**	from ld.
*/

void			op_ldi(t_cursor *cursor, t_env *env)
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
	exec_ldi(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
