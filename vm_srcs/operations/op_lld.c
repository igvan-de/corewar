/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_lld.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 10:09:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/03/10 10:09:19 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ld.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 16:18:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/26 16:18:54 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	exec_ld executes the ld operation at the current position of the cursor.
**	behavior differs based on the first argument --> look below for details.
*/

static	void	exec_lld(t_cursor *cursor, t_env *env, unsigned char encode)
{
	int arg_1;
	int arg_2;

	if (get_type(encode, 1) == T_DIR)
		arg_1 = get_arg(cursor, env, encode, 1);
	else
	{
		arg_1 = get_tind(env, cursor->position + 2);
		arg_1 = get_tdir(cursor->op_code, env, cursor->position + arg_1);
	}
	arg_2 = get_reg_num(cursor, env, encode, 2);
	cursor->registries[arg_2 - 1] = arg_1;
	set_carry(cursor, arg_1);
}

void			op_lld(t_cursor *cursor, t_env *env)
{
	unsigned char	op_code;
	unsigned char	encode;

	op_code = cursor->op_code;
	encode = env->map[modi(cursor->position + 1)];
	if (valid_encode(cursor->op_code, encode, env) == 0)
		return (invalid_op(cursor, env, 1));
	if (valid_regs(cursor, env, encode) == 0)
		return (invalid_op(cursor, env, 2));
	exec_lld(cursor, env, encode);
	move_cursor_encode(cursor, env, encode, op_code);
}
