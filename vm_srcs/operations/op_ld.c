/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ld.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	exec_ld(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int	arg_1;
	int	arg_2;

	arg_1 = get_arg(cursor, env, encode, 1);
	arg_2 = get_reg_num(cursor, env, encode, 2);
	cursor->registries[arg_2] = arg_1;
	set_carry(cursor, arg_1);
}

/*
**	@brief:	operation --> read and load a value into registry.
**
**	@param cursor		:	target cursor
**	@param env 			:	global environment struct
**
**	op_ld is an operation function which can be used to
**	read values and store them into the registry. The carry
**	is set depending on the stored value. values can either be
**	read from memory or from registries.
*/

void			op_ld(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_ld(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
